#
#   arduino komut gönder kısmı doğru çalışıyor. seri port kısmı da düzenlendi. 
#   Komut gönderirken AC yerine ac yazıyor. DÜZELTİLECEK
#   
#    Arduino programında seri port kısmı alt program gibi yapılabilir mi. 

import os
import serial
import threading
import time
import queue
from queue import Queue
import json
from pathlib import Path
from datetime import datetime
import requests
import sounddevice as sd
import vosk
import pygame
from gtts import gTTS
from io import BytesIO
import speech_recognition as sr
import winsound
import vlc
import yt_dlp
import base64
import pandas as pd
from google import genai
veri_lock = threading.Lock()
vosk_pause_event = threading.Event()
pygame.mixer.init()

# VOSK sesli sistem uyandırma kelimeleri buraya yazılacak. 

WAKE_WORDS = ["sistem", "yönetici","yardımcı","hizmetçi"]

# Vosk model path (download and extract vosk-model-small-tr-0.22 or similar)
# burada vosk çalışma PATH kısmını koyuyoruz. bu model dizininde türkçe model var. 

# ************   SİZDE KENDİ DİZİNİNİZİ BU ŞEKİLDE YAZIN. VOSK MODEL DİZİNİ ************

VOSK_MODEL_PATH = r"C:\Users\HP\AppData\Roaming\Python\Python310\site-packages\vosk-model-small-tr-0.3"

# Ana klasör yolu : Burada python programınızın bulunduğu yeri gösterir. dosya yolları kısmına bakın. 
main_folder = Path(__file__).parent

BLUETOOTH_COM_PORT = 'COM10'  # Bluetooth seri portunuzun adı (örneğin 'COM10')
USB_COM_PORT = 'COM1'       # USB seri portunuzun adı (örneğin 'COM11')
BAUD_RATE = 9600
veri_kuyrugu = Queue()
bt_kuyruk = Queue()
komut_kuyrugu = Queue()

ser_bluetooth = None  # Başlangıçta None olarak tanımlıyoruz
ser_usb = None

# Dosya yolları
LOG_DOSYA = main_folder / "logy.json"
CIHAZ_DOSYA = main_folder / "cihaz.json"
SENARYO_DOSYA = main_folder / "senaryolar.json"
#print("dizin ismi")
#print(main_folder)

# Global değişkenler
log_data = []
cihaz_data = []
senaryo_data = []
alarm_status=0
api_key=str("")
yzsend_flag=False
sensor_status=""
veri_kilidi = threading.Lock()
komut_flag=False
aktif_prompt=""
ACIL_MODU_AKTIF=False
yzflag=False



#=========== mikrofondan ses alma ve konuşma  fonksiyonları başlangıcı =========================

# Text to speech function using gTTS and pygame

speech_queue = Queue()

def speak_worker():   #============  bu kullanılıyor kullanım şekli vosk komut içinde görünüyor. thread olarak çalışıyor.
    while True:
        text = speech_queue.get()
        if text:
            vosk_pause_event.set()  # Vosk'u durdur

            tts = gTTS(text=text, lang='tr')
            mp3_fp = BytesIO()
            tts.write_to_fp(mp3_fp)
            mp3_fp.seek(0)

            #pygame.mixer.init()  # bu yukarıda tanımlandı gerek kalmadı. 
            pygame.mixer.music.load(mp3_fp)
            pygame.mixer.music.play()

            while pygame.mixer.music.get_busy():
                time.sleep(0.1)
            
            vosk_pause_event.clear()  # Seslendirme bitti, Vosk devam et

        time.sleep(0.2)


# UYANDIRMA KELİMESİ ALINDIĞINDA ONAYLAMAK İÇİN SESLİ BİR UYARI VERİR. 
def play_ding(frequency=1000, duration=300):
    winsound.Beep(frequency, duration)

# Google Speech Recognition (uyandırma kelimesinden sonra çalışır.)

def listen_command(timeout=10, phrase_time_limit=5):
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        recognizer.adjust_for_ambient_noise(source, duration=0.5)
        try:
            audio = recognizer.listen(source, timeout=timeout, phrase_time_limit=phrase_time_limit)
            command = recognizer.recognize_google(audio, language="tr-TR")
            return command.lower()
        except sr.UnknownValueError:
            return ""
        except sr.RequestError:
            return ""
        except sr.WaitTimeoutError:  # ← bu satırı eklemen gerekiyor
            print("Kullanıcı zamanında konuşmadı (timeout).")
            return ""  # boş string gönderiyoruz

# Vosk listener
def vosk_listener():
    global komut_flag
    global yzflag
    model = vosk.Model(VOSK_MODEL_PATH)
    q = queue.Queue()

    def callback(indata, frames, time, status):
        if status:
            print(status)
        if not vosk_pause_event.is_set():
            q.put(bytes(indata))

    with sd.RawInputStream(samplerate=16000, blocksize=8000, dtype='int16',
                           channels=1, callback=callback):
        rec = vosk.KaldiRecognizer(model, 16000)
        print("Wake word dinleniyor...")

        while True:
            if vosk_pause_event.is_set():
                #Pause durumunda Vosk dinlemesin, CPU harcamasın: sesli konuşurken uyandırma kelimesi beklemesin. mikrofon dursun.
                # bu komutun parçası kütüphanelerden sonra yazılmış olan yerdedir. 30. satır.
                time.sleep(0.1)
                continue

            data = q.get()
            if rec.AcceptWaveform(data):
                result = json.loads(rec.Result())
                text = result.get("text", "")
                if any(word in text.lower().split() for word in WAKE_WORDS): #(word in text.lower() for word in WAKE_WORDS):
                    print(f"Wake word algılandı: {text}")
                    text=""
                    play_ding()
                    command = listen_command()
                    if command:
                        print(f"Komut: {command}")
                        speech_queue.put(f"{command} komutu alındı.")
                        #komut_flag=True
                        #hazirla_ve_gonder_prompt("mic_komut", command)
                        yzflag=False
                        komutlari_ayikla_ve_yonlendir(command)
                    else:
                        speech_queue.put("Komut alınamadı, tekrar deneyin.")
                    print("Wake word dinleniyor...")

#===========  mikrofondan ses alma ve konuşma fonksiyonları sonu ============================

#((((((((((((((((               MP3 ve youtube çalışma fonksiyonları                 ))))))))))))))))

main_folder = Path(__file__).parent
player = None
youtube_playing = False
is_playing_mp3 = False
mp3_playlist = []
filtered_playlist = []
current_index = 0


def api_oku():  # api_key.txt dosyasından google YZ api anahtarınızı okur. 
        with open(main_folder / "api_key.txt", "r") as f:
            api = f.read()
        return api

api_key= api_oku()

def load_links_from_json(path=main_folder / "link.json"):# bu dosya youtube canlı kanalların linklerini tutar. senaryoya göre isimlendirilir.
    try:
        with open(path, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        print(f"link.json okunamadı: {e}")
        return []

youtube_senaryolar = load_links_from_json()

def load_mp3_playlist(json_path=main_folder / "playlist.json"):# bu dosya mp3 listenizin isimlerini ve özelliklerini kapsar
    try:
        with open(json_path, "r", encoding="utf-8") as f:
            raw_playlist = json.load(f)
        playlist = []
        for item in raw_playlist:
            track = {
                "path": main_folder / "mp3" / item["filename"],
                "title": item.get("title", ""),
                "artist": item.get("artist", ""),
                "tags": [tag.lower() for tag in item.get("tags", [])]
            }
            if track["path"].exists():
                playlist.append(track)
            else:
                print(f"⚠️ Dosya bulunamadı: {track['path']}")
        return playlist
    except Exception as e:
        print(f"playlist.json okunamadı: {e}")
        return []

mp3_playlist = load_mp3_playlist()
filtered_playlist = mp3_playlist.copy()

def play_current_track():
    global player, current_index, is_playing_mp3, filtered_playlist
    if not filtered_playlist:
        print("⚠️ Filtrelenmiş liste boş.")
        return

    if current_index >= len(filtered_playlist):
        current_index = 0

    track = filtered_playlist[current_index]
    file_path = track["path"]

    print(f"🎵 Çalınıyor: {track['title']} - {track['artist']}")

    instance = vlc.Instance()
    player = instance.media_player_new()
    media = instance.media_new(str(file_path))
    player.set_media(media)
    player.audio_set_volume(50)
    player.play()
    is_playing_mp3 = True

    monitor_thread = threading.Thread(target=monitor)
    monitor_thread.start()

def monitor():
    global player, is_playing_mp3
    while is_playing_mp3:
        state = player.get_state()
        if state == vlc.State.Ended:
            print("🎵 Şarkı bitti. Sıradaki uygun şarkı kontrol ediliyor...")
            next_track()
            break
        time.sleep(1)


def next_track():
    global current_index, is_playing_mp3

    # Şu anki index'ten sonrasına bak
    next_index = current_index + 1
    if next_index >= len(filtered_playlist):
        print("🚫 Etikete uyan başka şarkı kalmadı. Çalma durduruldu.")
        stop_mp3()
        return

    # Varsa sıradaki şarkıya geç
    current_index = next_index
    stop_mp3()
    play_current_track()

def previous_track():
    global current_index

    prev_index = current_index - 1
    if prev_index < 0:
        print("🚫 Geriye gidilecek şarkı kalmadı.")
        return

    current_index = prev_index
    stop_mp3()
    play_current_track()


def stop_mp3():
    global player, is_playing_mp3
    if player:
        player.stop()
        player.release()
        player = None
    is_playing_mp3 = False
    print("🎵 MP3 çalma durduruldu.")

def filter_by_tags(keywords):
    global filtered_playlist, mp3_playlist, current_index
    lower_keywords = [k.lower() for k in keywords]
    filtered_playlist = [track for track in mp3_playlist if all(k in track["tags"] for k in lower_keywords)]
    if filtered_playlist:
        print(f"🔍 Etiketlere göre filtrelendi: {lower_keywords}")
        current_index = 0
        play_current_track()
    else:
        print(f"❌ Etiketlere uygun şarkı bulunamadı: {lower_keywords}")

def play_youtube_audio(url):
    global player, youtube_playing
    ydl_opts = {
        'format': 'bestaudio/best',
        'quiet': True,
        'no_warnings': True,
        'default_search': 'ytsearch',
        'extract_flat': 'in_playlist'
    }

    try:
        with yt_dlp.YoutubeDL(ydl_opts) as ydl:
            info = ydl.extract_info(url, download=False)
            if 'url' not in info:
                print("⚠️ YouTube bağlantısından ses URL'si alınamadı.")
                youtube_playing = False
                return
            audio_url = info['url']
    except Exception as e:
        print(f"❌ YouTube hatası: {e}")
        youtube_playing = False
        return

    instance = vlc.Instance()
    player = instance.media_player_new()
    media = instance.media_new(audio_url)
    player.set_media(media)
    player.play()
    youtube_playing = True
    print(f"📺 YouTube URL çalıyor: {url}")

    while True:
        if player is None:
            break
        state = player.get_state()
        if state in [vlc.State.Ended, vlc.State.Error, vlc.State.Stopped]:
            break
        time.sleep(1)

    youtube_playing = False
    print("✅ YouTube çalma bitti.")

def stop_youtube():
    global player, youtube_playing
    if player and youtube_playing:
        player.stop()
        youtube_playing = False
        print("YouTube çalma durduruldu.")

def stop_all():
    stop_mp3()
    stop_youtube()
    print("Tüm çalma durduruldu.")



def handle_voice_command(command):
    cmd = command.lower()
    if "müzik" in cmd and "çal" in cmd:
        stop_all()
        play_current_track()
    elif "bir sonraki" in cmd or "sonraki" in cmd:
        stop_all()
        next_track()
    elif "önceki" in cmd:
        stop_all()
        previous_track()
    elif "durdur" in cmd or "dur dur" in cmd:
        stop_all()
    
    elif any(word in cmd for word in ["çal", "müzik", "oynat", "başlat"]):
        if "etiket" in cmd or "hareketli" in cmd or "nostaljik" in cmd or "soft" in cmd or "türkçe" in cmd:
            stop_all()
            tags = [word.strip() for word in cmd.split() if word.strip() in [tag for track in mp3_playlist for tag in track["tags"]]]
            if tags:
                filter_by_tags(tags)
            else:
                print("❌ Uygun etiket bulunamadı.")
    elif "ses" in cmd and ("arttır" in cmd or "yükselt" in cmd or "aç" in cmd):
        if player:
            vol = player.audio_get_volume()
            player.audio_set_volume(min(100, vol + 20))
            print(f"Ses artırıldı: {vol + 20}")
    elif "ses" in cmd and ("azalt" in cmd or "kıs" in cmd):
        if player:
            vol = player.audio_get_volume()
            player.audio_set_volume(max(0, vol - 20))
            print(f"Ses azaltıldı: {vol - 20}")
    else:
        matched = False
        for senaryo in youtube_senaryolar:
            if any(komut.lower() in cmd for komut in senaryo["komutlar"]):
                print(f"🎯 Eşleşen: {senaryo['id']} - {senaryo['standart_cevap']}")
                #speech_queue.put(f"{senaryo['id']} - {senaryo['standart_cevap']}")
                speech_queue.put(senaryo['standart_cevap'])
                stop_all()
                thread = threading.Thread(target=play_youtube_audio, args=(senaryo["olaylar"],))
                thread.start()
                matched = True
                break
        if not matched:
            print(f"❌ Tanımlanamayan komut: {command}")




#(((((((((((((((((((((((         MP3 ve youtube çalışma fonksiyonları SONU              )))))))))))))))))))))))


def load_json_file(filepath):
    #print(" filepath ")
    #print(filepath)
    #print("    ")
    with open(filepath, 'r', encoding='utf-8') as file:
        return json.load(file)

def initialize_data():
    global log_data, cihaz_data, senaryo_data
    log_json = load_json_file(LOG_DOSYA)
    log_data = log_json['sensorler'] # log.json dosyasında sensörler etiketiyle başladığı için bu şekilde yazıldı. 
    #log_data = load_json_file(LOG_DOSYA)
    cihaz_json = load_json_file(CIHAZ_DOSYA)
    cihaz_data = cihaz_json['cihazlar']
    senaryo_json=load_json_file(SENARYO_DOSYA)
    senaryo_data = senaryo_json['senaryolar']

def periyodik_kayit(): # TÜM JSON DOSYALARI RAM ÜZERİNDE ÇALIŞIR. 10DK DA BİR İSE DİSK ÜZERİNDEKİ DOSYALAR GÜNCELLENİR. 
    while True:
        time.sleep(3600)  # 10 dakika
        with veri_kilidi:
            try:
                with open( LOG_DOSYA , "w", encoding="utf-8") as f1:
                    json.dump({"sensorler": log_data}, f1, indent=2, ensure_ascii=False)
                with open( CIHAZ_DOSYA , "w", encoding="utf-8") as f2:
                    json.dump({"cihazlar": cihaz_data}, f2, indent=2, ensure_ascii=False)
                print(">> [KAYIT] logy.json ve cihaz.json dosyalarına yazıldı.")
            except Exception as e:
                print("Kayıt hatası:", e)


def update_log_with_arduino_data(Uarduino_data_str):# Arduinodan sensör bilgisi geldiğinde ve değişiklik varsa güncellenir yoksa aynı kalır.
    global log_data
    global alarm_status
    global yzsend_flag
    yzsend_flag=False
    global arduino_data_str

    arduino_values = Uarduino_data_str.strip().split(',')
    updated = False
    arduino_data_str=""
    for idx, value in enumerate(arduino_values):
        if idx < len(log_data):
            if log_data[idx]['Value'] != value:
                log_data[idx]['Value'] = value
                updated = True
        else:
            # Yeni veri eklenirse
            log_data.append({'Value': value})
            yzsend_flag=True
            updated = True
    if updated:
        print("sensör bilgisi güncellendi_1")
        #arduino_data_str=""
    else:
        print("sensör bilgisi aynı")
        #arduino_data_str=""
    
    if alarm_status==1:
        updated = True
        alarm_status=0
    return updated

def update_cihaz_with_arduino_data(cihaz_json_verisi):# arduinodan gelen cihaz verileri burada güncellenir. 
    global cihaz_data
    global alarm_status
    global yzsend_flag
    yzsend_flag=False
    arduino_values = cihaz_json_verisi.strip().split(',')
    updated = False

    for idx, value in enumerate(arduino_values):
        if idx < len(cihaz_data):
            if cihaz_data[idx]['Value'] != value:
                cihaz_data[idx]['Value'] = value
                updated = True
        else:
            # Yeni veri eklenirse
            cihaz_data.append({'Value': value})
            yzsend_flag=True
            updated = True
    if alarm_status==1:
        updated = True
        
        alarm_status=0
    return updated

def evaluate_sensor_status():
    global log_data
    global sensor_status
    aktif_sensorler = []

    for sensor in log_data:  # sonradan eklenen sensörleri de kontrol eder. 
            if 'Sensor' in sensor:
                if sensor['Value'] != '0':
                    aktif_sensorler.append(sensor['Sensor'])

    if aktif_sensorler:
        sensor_status = ", ".join(aktif_sensorler) + " sensör(ler)i aktif!"
    else:
        sensor_status = "Tüm sensörler normal."
    return sensor_status

def prepare_prompt():
    global log_data
    global sensor_name
    sensor_name=""
    sensor_status = evaluate_sensor_status()
    temp_values = [entry['Value'] for entry in log_data[14:22]]  # Örnek: sıcaklık verileri og_data 14:22 demek 22 sıralı listeden 14. sıradan başla
    prompt = f"Sensör Durumu: {sensor_status}\n "#Sıcaklık Değerleri: {', '.join(temp_values)
    print("prompt bilgisi")
    print(prompt)
    return prompt

# *********************  seri okuma başlangıcı *************************************

# ===================  bluetooth seri okuma ========================
def baslat_bluetooth_oku_thread(ser_port, port_adi, bt_kuyruk):
    if ser_port is not None and ser_port.is_open:
        thread = threading.Thread(target=bluetooth_oku, args=(ser_port, port_adi, bt_kuyruk))
        thread.daemon = True
        thread.start()
        print(f"{port_adi} Bluetooth okuma thread'i başlatıldı.")
    else:
        print(f"{port_adi} Bluetooth okuma thread'i başlatılamadı.")

def bluetooth_oku(ser_port, port_adi, bt_kuyruk):
    try:
        if ser_port is not None and ser_port.is_open:
            print(f"{port_adi} (Bluetooth) okuma thread'i başladı.")
            while True:
                if ser_port.in_waiting > 0:
                    line = ser_port.readline().decode('utf-8').rstrip()
                    bt_kuyruk.put((port_adi, line))
                time.sleep(0.01)
        else:
            print(f"{port_adi} Bluetooth portu açık değil.")
    except serial.SerialException as e:
        print(f"Bluetooth seri port hatası ({port_adi}): {e}")
    finally:
        if ser_port is not None and ser_port.is_open:
            ser_port.close()
            print(f"Bluetooth port ({port_adi}) kapatıldı.")
# ===================  bluetooth seri okuma  sonu ========================

# ===================  USB seri okuma ========================

def read_line_with_timeout(ser, expected_text=None, timeout=5.0):
    """
    Seri porttan satır okur. Belirli bir süre içinde expected_text varsa döner, yoksa None döner.
    """
    start_time = time.time()
    while time.time() - start_time < timeout:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if expected_text:
                if expected_text in line:
                    return line
            else:
                return line
        time.sleep(0.01)  # CPU'yu yormamak için kısa bekleme
    return None  # Zaman aşımı



def baslat_arduino_usb_oku_thread(ser_port, port_adi, veri_kuyrugu, komut_kuyrugu):
    if ser_port is not None and ser_port.is_open:
        thread = threading.Thread(target=arduino_usb_oku, args=(ser_port, port_adi, veri_kuyrugu, komut_kuyrugu))
        thread.daemon = True
        thread.start()
        print(f"{port_adi} Arduino USB okuma thread'i başlatıldı.")
    else:
        print(f"{port_adi} Arduino USB okuma thread'i başlatılamadı.")

def arduino_usb_oku(ser_port, port_adi, veri_kuyrugu, komut_kuyrugu):
    buffer = ""  # kendi buffer'ımız
    try:
        if ser_port is not None and ser_port.is_open:
            print(f"{port_adi} (Arduino USB) okuma thread'i başladı.")
            while True:
                # 1️⃣ Seriden gelen baytları oku ve buffer’a ekle
                if ser_port.in_waiting > 0:
                    data = ser_port.read(ser_port.in_waiting).decode(errors='ignore')
                    buffer += data

                    # 2️⃣ Tam satır(lar) varsa ayır ve kuyruğa ekle
                    while '\n' in buffer:
                        line, buffer = buffer.split('\n', 1)
                        line = line.strip()
                        if line:
                            veri_kuyrugu.put((port_adi, line))

                # 3️⃣ Komut gönderme kısmı aynen kalabilir
                if veri_kuyrugu.empty() and not komut_kuyrugu.empty():
                    komut = komut_kuyrugu.get()
                    ser_port.write(b"REQ_WRITE\n")

                    yanit = read_line_with_timeout(ser_port, expected_text="READY", timeout=8.0)
                    if yanit == "READY":
                        ser_port.write(f"DATA:{komut}\n".encode())

                        ack = read_line_with_timeout(ser_port, expected_text="ACK", timeout=8.0)
                        if ack == "ACK":
                            print(f"Arduino komutu aldı: {komut}")
                        else:
                            print(f"ACK alınamadı. Komut başarısız: {komut}")
                    else:
                        print("Arduino 'READY' yanıtı vermedi. Komut gönderilemedi.")

                time.sleep(0.01)
        else:
            print(f"{port_adi} (Arduino USB) portu açık değil.")
    except serial.SerialException as e:
        print(f"USB port hatası ({port_adi}): {e}")
    finally:
        if ser_port is not None and ser_port.is_open:
            ser_port.close()
            print(f"USB port ({port_adi}) kapatıldı.")


def decode_b64_message(mesaj: bytes | str) -> str | None:
    
    # Bluetooth’tan gelen Base64 kodlu baytları UTF-8 metne çevirir.
    # Hata olursa None döner.
    # seri port türkçe karakter gönderemediği için bluetooth verileri
    # base64 kodlamasına çevrilir. UTF-8 kodlar yani türkçe karakterler bu şekilde seri port üzerinden gönderilir.
    # bu fonksiyon ise base64 ile gelen kodu normal karakterlere çevirir. 
    
    if isinstance(mesaj, str):
        mesaj = mesaj.encode("utf-8")

    # Satır sonu, boşluk, “\r\n” gibi fazlalıkları temizle
    mesaj = mesaj.strip()

    try:
        decoded = base64.b64decode(mesaj, validate=True)
        return decoded.decode("utf-8")
    except Exception as exc:
        print(f"[BT-DECODE] Base64 çözülemedi: {exc}")


# *********************  seri okuma sonu *************************************

def bilgi_sensorlerini_ekle(log_data):# YZ ye gönderilirken sadece sıcaklık sensör bilgisini sensör bilgilerinden ayırır. 
                                        # bunu logy.json dosyasındaki sensor ve sensor1 ayrımına göre yapar. 
    """
    Sadece 'Sensor1' anahtarına sahip (örneğin sıcaklık vb.) bilgileri alır ve
    string olarak döner.
    """
    bilgi_satirlari = []

    for sensor in log_data:
        if 'Sensor1' in sensor:
            bilgi_adi = sensor['Sensor1']
            deger = sensor['Value']
            bilgi_satirlari.append(f"{bilgi_adi}: {deger}")

    if bilgi_satirlari:
        return "Bilgi Amaçlı Sensör Değerleri:\n" + "\n".join(bilgi_satirlari)
    else:
        return ""  # Eklenebilecek bilgi yoksa boş döner

def get_normal_prompt(zaman, kaynak, alarm_durumu, komut_metni, sensor_status, log_data, cihaz_data, senaryo_data):
    # YZ ye 2 prompt yollanır. ev sistemi için bu prompt yollanır bir de acil durumlar için ayrı prompt vardır. 
    # YZ bu prompt ile kendini ev sistem asistanı olarak görür. prompt hakkında detaylı bilgi:  https://www.mikrobotik.com/wp2/
    return [
        "Ev otomasyonu alanında bana yardımcı olan bir ev asistanısın. Sana gönderdiğim komut ne ise karşılığında bilgileri ve senaryoları kullanarak bir cevap vermelisin.",
        "Cevabın, ilgili senaryonun 'emirler' kısmındaki komutlardan biri olmalı. Emirleri seçerken, 'Evdeki bazı cihazların devreye alınması' bölümündeki verdiğim koşulları ve tarihi dikkate al.",
        "Komut cevabı tek satır ve 100 karakteri geçmemeli. NOT kısmı ayrı bir satıra 'NOT:' etiketiyle başlasın. NOT kısmı 100 karakter sınırına tabi değildir.",
        #"Cevabın 100 karakteri geçmemeli.",
        "ev sistemime bağlı bir müzik sistemi ve youtube sistemi var.",
        f"Tarih: {zaman}",
        f"Komut Kaynağı: {kaynak}",
        f"Alarm Durumu: {alarm_durumu}",
        f"Kullanıcı Komutu: {komut_metni}",
        f"SENSÖR DURUMLARI: {sensor_status}",
        bilgi_sensorlerini_ekle(log_data),
        "Cihazlar:\n" + "\n".join(map(str, cihaz_data)),
        "Senaryo:\n" + "\n".join(map(str, senaryo_data)),
        "Evdeki bazı cihazların devreye alınması:",
        "kombi: aralık, ocak, şubat, mart aylarında devrede; diğer aylarda tamamen kapalı.",
        "klima: kombinin kapalı olduğu durumlarda kış veya yaz ayı olması durumuna göre sıcak ya da soğuk olarak devreye girer.",
        "Eğer kış ayı ise ve ortam sıcaklığı 25 dereceden düşükse, klima 25 dereceye ısıtacak şekilde devreye alınır.",
        "Eğer yaz ayı ise ve ortam sıcaklığı 25 dereceden yüksekse, klima 25 dereceye soğutacak şekilde devreye alınır.",
        "Eğer ortam sıcaklığı zaten 25 derece ise veya yukarıdaki koşullar sağlanmıyorsa, klima kapalı kalır.",
        "Doğalgaz devrede ise komut içerisinde bir belirtici yoksa, klima çalıştırılmayacak.",
        "Ayların durumuna göre ısıtma olacaksa öncelik doğalgazın devreye alınması. Ek ısıtma istenirse klima da devreye alınabilir.",
        "Örnek: Mayıs ayında 'oturma odasındayım' komutu gelirse kombi açılmaz.",
        "Eğer bir senaryoyu tetikliyorsan, senaryonun standart_cevap kısmını yanıtının sonuna NOT: etiketiyle ekle. ",
        "Bir senaryo tetikleniyorsa, sadece komutla ilgili cihazlara ait emirleri döndür. Diğer senaryo cihazlarını ekleme. Örnek: 'mutfaktayım' komutunda yalnızca mutfak ışıkları veya cihazlarıyla ilgili komutlar verilir.",
        "şayet senaryolar komut ile uymuyorsa kendin komuta göre cevap verebilirsin. "
    ]

def get_acil_prompt(): # bu prompt ise acil durumlarda YZ ye gönderilecek prompt tur. prompt hakkında detaylı bilgi: https://www.mikrobotik.com/wp2/
    return [
        "Evde yalnız ve hasta bir kişi var.",
        "Sakinleştirici, anlayışlı cümlelerle konuş.",
        "Bilgi verme, sadece destek ol.",
        "Sesli konuşmalarla moral ver, güven aşıla.",
        "Konuşmalar kısa ve nazik olmalı.",
    ]

def hazirla_ve_gonder_prompt(kaynak, komut_metni):  # YZ ye bilgileri gönderir ve gelen cevabı alır. 

    global api_key
    global alarm_status
    global yzsend_flag
    global sensor_status
    global komut_flag
    alarm_durumu = "Normal"
    global  ACIL_MODU_AKTIF
    global yzflag

    yzflag=False


    if kaynak == "AL_komut":
        alarm_durumu = "Alarm tetiklendi!"
        komut_metni = "Alarm tetiklendi"
    zaman = datetime.now().strftime("%d-%m-%Y %H:%M:%S")
    #speech_queue.put(f"{komut_metni} komutu alındı") #speech_queue.put(f"{command} komutu alındı.")

    if ACIL_MODU_AKTIF:
        aktif_prompt = get_acil_prompt()
    else:
        aktif_prompt = get_normal_prompt(
        zaman=zaman,
        kaynak=kaynak,
        alarm_durumu=alarm_durumu,
        komut_metni=komut_metni,  # veya kullanici_komutu
        sensor_status=sensor_status,
        log_data=log_data,
        cihaz_data=cihaz_data,
        senaryo_data=senaryo_data
    )
    tam_prompt = "\n\n".join(aktif_prompt) 

    print(">>> YZ'ye gönderilecek prompt:")
    print(tam_prompt)
    print(">>> YZ'ye gönderilecek mi? ")
    print(yzsend_flag)
    print(">>>ALARM DURUMU ")
    print(alarm_status)

    if alarm_status==1 and yzsend_flag==True:
        yzflag=True
        send_alarm_email_get(sensor_status) # ALARM ve ACİL durumlarda PHP ile hazırlanmış mail gönderme bölümüne gider. 
        response=gemini_istegi_gonder(tam_prompt) #YZ api isteği yollayan fonksiyonu çağırır. 
        
        print("\n \r")
        print(response.text)
        komut_metni=""
        komutlari_ayikla_ve_yonlendir(response.text)
    if komut_flag==True:
        # API ile iletişim
        komut_flag=False
        yzflag=True
        response=gemini_istegi_gonder(tam_prompt) #YZ api isteği yollayan fonksiyonu çağırır. 
        
        if response is not None:
            print("\n\r")
            print(response.text)
            komutlari_ayikla_ve_yonlendir(response.text)
            print(" YZ'den yanıt GELDİ")
        else:
            print("❌ YZ'den yanıt alınamadı. Lütfen tekrar deneyin.")
            # Eğer istersen burada bir sesli uyarı da koyabilirsin:
            # speech_queue.put("Yanıt alınamadı. Lütfen tekrar deneyin.")


def gemini_istegi_gonder(tam_prompt, max_retry=5, bekleme_suresi=10):# YZ apisine bilgi gönderip cevap almak için kullanılır. 
                                                                        # siz kendi api anahtarınızı bedava olarak google dan alın. 
    global api_key
    
    client = genai.Client(api_key=api_key)            
    
    for deneme in range(1, max_retry + 1):
        try:
            response = client.models.generate_content(
                model="gemini-2.0-flash", contents=tam_prompt,
            )
            return response
        except Exception as e:
            if hasattr(e, "code") and e.code == 503:
                print(f"[UYARI] Sunucu meşgul (503). {deneme}. deneme. {bekleme_suresi}sn bekleniyor...")
                time.sleep(bekleme_suresi)
            else:
                print("[HATA] Diğer bir hata oluştu:", e)
                break
    return None



# ==========================    YZ komut ayıklama modülü    =====================


def ardu_komutlari_ayikla_ve_donustur(yz_cevap):
    global cihaz_data
    cihazlar = cihaz_data
    arduino_komutlari = []
    print("🔍 yz_cevap tipi:", type(yz_cevap))

    print("🔍 yz_cevap içeriği:", yz_cevap)
    #print("✅ komut_listesi:", komut_listesi)

    # 💡 Liste geldiyse virgülle birleştirip string yap
    if isinstance(yz_cevap, list):
        yz_cevap = ", ".join(yz_cevap)

    # 💡 Şimdi kesinlikle string olarak işliyoruz
    if isinstance(yz_cevap, str):
        komut_listesi = [komut.strip().rstrip('.').lower() for komut in yz_cevap.split(",")]
    else:
        print("UYARI: yz_cevap tipi geçersiz:", type(yz_cevap))
        return []

    for komut in komut_listesi:
        print(f"> İşlenen komut: {komut}")
        for cihaz in cihazlar:
            cihaz_adi = cihaz["cihaz isim"].lower()
            cihaz_status = cihaz["Status"].lower()

            if cihaz_status in komut:
                if "aç" in komut or "aktif" in komut:
                    deger = cihaz["open"]
                elif "kapat" in komut or "pasif" in komut:
                    deger = cihaz["close"]
                else:
                    continue

                komut_str = f"{cihaz_adi}={deger}"
                arduino_komutlari.append(komut_str)

            elif "cihazları kapat" in komut or "tüm cihazları kapat" in komut:
                deger = cihaz["close"]
                komut_str = f"{cihaz_adi}={deger}"
                arduino_komutlari.append(komut_str)

    return arduino_komutlari




def arduinoya_gonder(emirler):
    temiz_emir=emirler
    arduino_komut_str = ",".join(temiz_emir)
    print("ardu komutlar. ")
    print(temiz_emir)
    print(arduino_komut_str)
    while not komut_kuyrugu.empty():
        try:
            komut_kuyrugu.get_nowait()
        except queue.Empty:
            break
    komut_kuyrugu.put(arduino_komut_str)
    return



def get_muzik_tetikleyiciler():# bu YZ komutlarını ayırırken müzik modundaki etiketleri ayrıştırarak gönderir. 
    for senaryo in senaryo_data:
        if senaryo["id"] == "muzik_modu":
            emirler = senaryo.get("emirler", "")
            return [e.strip() for e in emirler.split(",") if e.strip()]
    return []

def acil_durum_yonetimi(kisi_mesaji):
    global ACIL_MODU_AKTIF

    speech_queue.put("Acil durum bildirimi gönderildi. Lütfen sakin olun. Çok acil bir durumdaysanız 112’yi aramanız önerilir.")
    send_alarm_email_get(" Evde yardım isteyen biri var.")

    ACIL_MODU_AKTIF = True  # Geri dönüş kontrolü için flag
    print("💬 Destek moduna geçildi.")



def komutlari_ayikla_ve_yonlendir(yz_cevabi):
    global senaryo_data, cihaz_data
    global alarm_status
    global ACIL_MODU_AKTIF
    global komut_flag
    global yzflag



    temiz_cevap = yz_cevabi.rstrip('.')#.lower()
    print("YZ cevap: ", yz_cevabi)
    print("")
    if "NOT:" in yz_cevabi:
        temiz_cevap, not_mesaji = yz_cevabi.split("NOT:", 1)
        temiz_cevap = temiz_cevap.strip()
        not_mesaji = not_mesaji.strip()
        print("temiz_cevap: ", temiz_cevap)
        print("Not mesajı: ", not_mesaji)
        print("")
        if not_mesaji:
            speech_queue.put(not_mesaji)
        else:
            speech_queue.put(temiz_cevap)
    parcalar = [p.strip() for p in temiz_cevap.split(",") if p.strip()]
    print("temiz_cevap: ", temiz_cevap)



    playlist_tagleri = set(tag for track in mp3_playlist for tag in track.get("tags", []))
    muzik_tetikleyiciler = get_muzik_tetikleyiciler()
    #print("🎵 Müzik tetikleyiciler:", muzik_tetikleyiciler)

    cihaz_emirleri = []
    komut_islendi = False

    if temiz_cevap == "ALARM DURUMU":
        guvenlik_modunu_baslat()
        return
    
    acil_kelimeler = ["acil", "imdat", "yardım edin", "fenalaştım", "ambulans", "nefes alamıyorum"]

    if temiz_cevap and any(k in temiz_cevap.lower() for k in acil_kelimeler):
        print("🚨 Acil durum algılandı!")
        acil_durum_yonetimi(temiz_cevap)
        komut_islendi = True
        komut_flag = True
        hazirla_ve_gonder_prompt("mic_komut", temiz_cevap)
        return

    izinli_senaryo_idleri = ["muzik_modu"]
    for parca in parcalar:
        # 🛑 Özel komut: cihazları kapat
        if parca == "cihazları kapat":
            for cihaz in cihaz_data:
                status = cihaz.get("Status", "")
                if status:
                    cihaz_emirleri.append(f"{status} kapat")
            komut_islendi = True
            continue

        # 🎵 Müzik işle
        if any(kelime in parca for kelime in muzik_tetikleyiciler) or any(tag in parca for tag in playlist_tagleri):
            print(f"🎵 Müzik komutu algılandı: {parca}")
            handle_voice_command(parca)
            komut_islendi = True
            continue

        # 📟 Senaryo eşleşmesi
        for senaryo in senaryo_data:
            for komut in senaryo.get("komutlar", []):
                if komut in parca:
                    if senaryo["id"] not in izinli_senaryo_idleri:
                        print("⚠️ Senaryo eşleşti ama izinli değil:", senaryo["id"])
                        continue  # Bu senaryoyu atla ve diğerlerine bak
                    emirler = senaryo.get("emirler", "")
                    cevap = senaryo.get("standart_cevap", "")
                    print("✅ Senaryo tetiklendi:", senaryo["id"])
                    komutlar = [e.strip() for e in emirler.split(",") if e.strip()]
                    cihaz_emirleri.extend(komutlar)
                    speech_queue.put(cevap)
                    komut_islendi = True
                    break

        # 💡 Manuel cihaz kontrolü
        cihaz_parca_islendi = False
        for cihaz in cihaz_data:
            status = cihaz.get("Status", "")
            if normalize(status) in normalize(parca):
                if "aç" in parca:
                    cihaz_emirleri.append(f"{status} aç")
                    cihaz_parca_islendi = True
                elif "kapat" in parca:
                    cihaz_emirleri.append(f"{status} kapat")
                    cihaz_parca_islendi = True

        if cihaz_parca_islendi:
            komut_islendi = True

    if cihaz_emirleri:
        print(f"➡️ Arduino'ya gönderilecek: {cihaz_emirleri}")
    
        tum_ardu_komutlar = []
        for emir in cihaz_emirleri:
            komutlar = ardu_komutlari_ayikla_ve_donustur(emir)
            if komutlar:  # Eğer Arduino komutu varsa
                tum_ardu_komutlar.extend(komutlar)
        arduinoya_gonder(tum_ardu_komutlar)

    
    kapatma_kelimeleri = ["iyiyim", "geçti", "sorun kalmadı", "teşekkür ederim"]

    if ACIL_MODU_AKTIF and temiz_cevap and any(k in temiz_cevap.lower() for k in kapatma_kelimeleri):
        ACIL_MODU_AKTIF = False
        speech_queue.put("Geçmiş olsun. Ev kontrol sistemine geri dönülüyor.")
        print("✔️ Destek modu kapatıldı, normal moda dönüldü.")
        komut_islendi = True
        komut_flag = True
        hazirla_ve_gonder_prompt("mic_komut", temiz_cevap)
        return


    if not komut_islendi and yzflag==False:
        print(f"🗣 YZ cevabı sadece bilgi amaçlı: {yz_cevabi}")
        print("📤 Komut senaryo veya cihazla eşleşmedi, YZ'ye yönlendiriliyor...")
        komut_flag = True
        hazirla_ve_gonder_prompt("mic_komut", temiz_cevap)
        #speech_queue.put(yz_cevabi)
    
    
    
    

def normalize(text):  # Bazı kelimelerde türkçe karakter varsa karşılaştırmada sorun oluyor. bundan dolayı karşılaştırmadan önce
                        # geçici olarak türkçe karakterleri ingilizceye çeviriyoruz. 
    return (
        text.lower()
        .replace("ı", "i")
        .replace("ş", "s")
        .replace("ç", "c")
        .replace("ğ", "g")
        .replace("ö", "o")
        .replace("ü", "u")
    )


def guvenlik_modunu_baslat():  # ALARM geldiği zaman ki bunu ARDUINO ALARM yazarak başlatıyor. YZ ye gidip geldikten sonra güvenlik moduna geçiyor. 
    global alarm_status, komut_kuyrugu, speech_queue

    print(">> Güvenlik modu başlatıldı!")

    # Arduino'ya verileri durdur komutu gönder
    #komut_kuyrugu.put("stop")  # Arduino sensör verilerini geçici durdursun

    # Güvenlik moduna geçtiğimizi bildir
    #komut_kuyrugu.put("guvenlik_modu")

    # Alarm başladığında
    ser_usb.write("guvenlik_modu\n".encode())

    # Sesli alarm mesajları
    alarm_mesajlari = [
        "Dikkat! Ortamda gaz tespit edildi.",
        "Lütfen hiçbir elektrikli cihazı çalıştırmayın.",
        "Pencereleri yavaşça açın.",
        "Gaz kaynağının olduğu bölgeye girmeyin.",
        "112 veya 187 Doğalgaz Acil Hattını arayın."
    ]

    # Mesajları sıraya koy
    for mesaj in alarm_mesajlari:
        speech_queue.put(mesaj)

    # Kuyruk boşalana kadar bekle (yani sesli mesajlar bitene kadar)
    while not speech_queue.empty():
        time.sleep(0.1)

    time.sleep(30)
    # Sesli mesajlar bittiğinde Arduino’dan veri alımı devam etsin
    ser_usb.write("resume\n".encode())
    #komut_kuyrugu.put("resume")      # Arduino kaldığı yerden devam etsin
    #komut_kuyrugu.put("sensor_read") # Güncel verileri tekrar yollasın

    # Alarm durumu aktif
    alarm_status = 1

# =========================    YZ komut ayıklama sonu   ========================

import requests

# PHP mail gönderme buraya PHP dosyanızın hangi sunucuda bulunduğunu yazın. 
PHP_SCRIPT_URL = 'https://www.mikrobotik.com/deneme/phpmailgonder/sendmail.php'

def send_alarm_email_get(alarm_message):   # E-mail GET ya da POST metodu ile gönderilir ben GET tercih ettim. HASSAS veriler varsa aşağıdaki POST modunu da kullanabilirsiniz.
    """
    HTTP GET metodu ile PHP mail scriptini çağırır ve alarm parametresini gönderir.
    Parametreler URL'de görünür.
    """
    params = {'alarm': alarm_message}
    try:
        print(f"GET isteği gönderiliyor: {PHP_SCRIPT_URL} ile parametreler: {params}")
        response = requests.get(PHP_SCRIPT_URL, params=params)

        # Sunucudan gelen yanıtı kontrol et
        response.raise_for_status()  # HTTP hataları (4xx veya 5xx) için hata fırlatır

        print("E-posta gönderim isteği başarılı!")
        print("Sunucu Yanıtı:", response.text)

    except requests.exceptions.HTTPError as http_err:
        print(f"HTTP hatası oluştu: {http_err} (Durum Kodu: {response.status_code})")
        print("Yanıt Metni:", response.text) # Hata durumunda sunucu yanıtını göster
    except requests.exceptions.ConnectionError as conn_err:
        print(f"Bağlantı hatası oluştu: {conn_err}")
    except requests.exceptions.Timeout as timeout_err:
        print(f"Zaman aşımı hatası oluştu: {timeout_err}")
    except requests.exceptions.RequestException as req_err:
        print(f"Beklenmedik bir hata oluştu: {req_err}")

def send_alarm_email_post(alarm_message): # email gönderme post metodu. 
    """
    HTTP POST metodu ile PHP mail scriptini çağırır ve alarm parametresini gönderir.
    Parametreler URL'de görünmez, isteğin gövdesinde gönderilir.
    """
    data = {'alarm': alarm_message}
    try:
        print(f"POST isteği gönderiliyor: {PHP_SCRIPT_URL} ile veri: {data}")
        response = requests.post(PHP_SCRIPT_URL, data=data)

        # Sunucudan gelen yanıtı kontrol et
        response.raise_for_status()  # HTTP hataları (4xx veya 5xx) için hata fırlatır

        print("E-posta gönderim isteği başarılı!")
        print("Sunucu Yanıtı:", response.text)

    except requests.exceptions.HTTPError as http_err:
        print(f"HTTP hatası oluştu: {http_err} (Durum Kodu: {response.status_code})")
        print("Yanıt Metni:", response.text)
    except requests.exceptions.ConnectionError as conn_err:
        print(f"Bağlantı hatası oluştu: {conn_err}")
    except requests.exceptions.Timeout as timeout_err:
        print(f"Zaman aşımı hatası oluştu: {timeout_err}")
    except requests.exceptions.RequestException as req_err:
        print(f"Beklenmedik bir hata oluştu: {req_err}")


def main_loop():  # burası ana döngü. bütün ilk işlemler burada karşılanır. threading başlatmalar burada olur. 
    global ser_bluetooth
    global ser_usb
    global alarm_status
    global sensor_status
    global yzsend_flag
    global komut_flag
    global arduino_data_str

    try:
        ser_bluetooth = serial.Serial(BLUETOOTH_COM_PORT, BAUD_RATE, timeout=0.1)
        print(f"Bluetooth portu {BLUETOOTH_COM_PORT} başarıyla açıldı.")
    except serial.SerialException as e:
        print(f"Bluetooth seri portu açılamadı: {e}")

    try:
        ser_usb = serial.Serial(USB_COM_PORT, BAUD_RATE, timeout=0.1)
        print(f"USB portu {USB_COM_PORT} başarıyla açıldı.")
    except serial.SerialException as e:
        print(f"USB seri portu açılamadı: {e}")
 
    # mikrofondan ses alma thread başlat
    listener_thread = threading.Thread(target=vosk_listener, daemon=True)
    listener_thread.start()

    # speak kısmı thread olarak çalışıyor. komutları ve geri bildirimleri seslendiriyor. 
    speak_thread = threading.Thread(target=speak_worker, daemon=True)
    speak_thread.start()

    # Seri okuma thread'lerini başlat
    baslat_arduino_usb_oku_thread(ser_usb, "USB", veri_kuyrugu, komut_kuyrugu)
    baslat_bluetooth_oku_thread(ser_bluetooth, "Bluetooth", bt_kuyruk)
    #baslat_seri_okuma_thread(ser_bluetooth, "Bluetooth", veri_kuyrugu)
    #baslat_seri_okuma_thread(ser_usb, "USB", veri_kuyrugu)

    # periyodik kayıt kısmı threading başlatma. 
    kayit_thread = threading.Thread(target=periyodik_kayit, daemon=True)
    kayit_thread.start()

    print("Ana program çalışıyor...")
    initialize_data()
    arduino_data_str = ""
    prompt = ""
    while True:
        # Gelen verileri işle
        # USB kuyruğunu kontrol et
        while not veri_kuyrugu.empty():
            
            port_adi, mesaj = veri_kuyrugu.get()
            print(f"[{port_adi}] Gelen mesaj: {mesaj}")

            if port_adi == "USB" and mesaj.startswith("cihaz"):
                cihaz_json_verisi = mesaj[len("cihaz:"):]  # sadece veri kısmı
                print(">> CİHAZ BİLGİ GÜNCELLEME MESAJI ALGILANDI")
                update_cihaz_with_arduino_data(cihaz_json_verisi)  # bu fonksiyonu sen yazacaksın
                continue  # bu mesaj işlendi, döngüye geri dön

            elif port_adi == "USB" and mesaj.startswith("ALARM"):
                print("*** USB ALARMI ALGILANDI! ***")
                mesaj = mesaj[len("ALARM,"):]
                arduino_data_str = mesaj
                alarm_status = 1
                if alarm_status == 1:
                    alarm_bilgisi = prepare_prompt()  # Bu sadece alarm sensörlerini özetliyor
                    hazirla_ve_gonder_prompt("AL_komut", alarm_bilgisi)
                print("Alarm mesajı işlendi:", arduino_data_str)
            
            elif port_adi == "USB" and mesaj.startswith("DiKKAT"):
                print("*** USB UYARI ALGILANDI! ***")
                speech_queue.put(f"İKAZ KAPIDA HAREKET VAR.")
                mesaj = mesaj[len("DiKKAT,"):]
                arduino_data_str = mesaj
                print("İKAZ ALARM:", arduino_data_str)
                update_log_with_arduino_data(arduino_data_str)
                arduino_data_str=""
                continue

            elif port_adi == "Bluetooth":
                # Bluetooth'tan gelen diğer komutları işle
                print(f"[{port_adi}] Gelen mesaj2: {mesaj}")
                decoded_veri = decode_b64_message(mesaj)
                if decoded_veri is not None:
                    print(f"Bluetooth'tan gelen komut: {decoded_veri}")
                    komut_flag=True
                    hazirla_ve_gonder_prompt("BL_komut", decoded_veri)
                else:
                    print("Veri çözümlenemedi.")
                pass

            else:
                # Normal veri
                arduino_data_str = mesaj

        # Bluetooth kuyruğunu kontrol et
        while not bt_kuyruk.empty():
            port_adi, mesaj = bt_kuyruk.get()
            print(f"[{port_adi}] Gelen mesaj (Bluetooth): {mesaj}")

            decoded_veri = decode_b64_message(mesaj)
            if decoded_veri is not None:
                print(f"Bluetooth'tan gelen komut: {decoded_veri}")
                komut_flag=True
                hazirla_ve_gonder_prompt("BL_komut", decoded_veri)
            else:
                print("Bluetooth verisi çözümlenemedi.")
            pass



        time.sleep(0.1) # Kuyruk kontrolü için kısa bir bekleme

        # *******  ALTTAKİ 3 SATIR AÇILIRSA YAZILI KOMUT VERİLİR. SESLİ VERİLMESİNE GEREK KALMAZ.*********
        #voice_input = input("Sesli komut girin: ")
        #if not voice_input=="":
        #    komutlari_ayikla_ve_yonlendir(voice_input)
        
        
        if arduino_data_str:
            if update_log_with_arduino_data(arduino_data_str):
                prompt = prepare_prompt()
                print(prompt)
                arduino_data_str=""
                if not sensor_status == "Tüm sensörler normal.":
                    alarm_status=1
                    yzsend_flag=True
                    hazirla_ve_gonder_prompt("AL_komut", prompt)




        #import time
        time.sleep(5)

if __name__ == "__main__":
    main_loop()