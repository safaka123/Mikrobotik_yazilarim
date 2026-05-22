import serial
import struct

ser = serial.Serial('COM9', 9600, timeout=0.1)
LOGSIZE = 20
header = b'\xAA'

# Kart tiplerini anlamlı yazılara dönüştürmek için sözlük
KART_TIPLERI = {
    0: "Normal / Tam",
    1: "Öğrenci",
    2: "Şehit Yakını",
    3: "Engelli",
    4: "Özel Durum"
}

def parse_log(data):
    try:
        time_val = int.from_bytes(data[0:4], 'little')
        uid_size = data[4]
        uid = data[5:5+uid_size]
        
        gate = data[12]                               
        kredi = int.from_bytes(data[13:17], 'little') 
        
        # 1. Arduino'dan gelen 2 byte'lık ham 'result' alanını okuyoruz
        result_raw = int.from_bytes(data[17:19], 'little')
        
        # 2. Düşülen kredi miktarını alt byte'tan ayırıyoruz
        dusulen_kredi = result_raw & 0xFF            
        
        # 3. Üst byte'taki durum paketini alıyoruz (Örn: 0x0A, 0x0B, 0x01, 0x29)
        durum_paketi_hex = (result_raw >> 8) & 0xFF     
        
        # 4. Gelen hex byte'ını doğrudan onluk (decimal) tam sayıya eşitliyoruz
        durum_sayisi = int(durum_paketi_hex) 
        
        # 5. MATEMATİKSEL AYRIŞTIRMA (Basamak kaybı/kayma riski sıfır)
        # Örn 11 (0x0B) için: 11 // 10 = 1 (Öğrenci) | 11 % 10 = 1 (Aktarma Var)
        # Örn  1 (0x01) için:  1 // 10 = 0 (Normal)  |  1 % 10 = 1 (Aktarma Var)
        # Örn 10 (0x0A) için: 10 // 10 = 1 (Öğrenci) | 10 % 10 = 0 (İlk Biniş)
        kart_tipi_kod = durum_sayisi // 10          # Onlar basamağı -> Kart Tipi
        aktarma_durumu = durum_sayisi % 10          # Birler basamağı -> Saf Aktarma Bilgisi

        kart_tipi_str = KART_TIPLERI.get(kart_tipi_kod, f"Bilinmeyen ({kart_tipi_kod})")
        uid_str = ''.join(f'{b:02X}' for b in uid)

        # Tam istediğin sade, noksansız ve net ekran düzeni
        print("------ PARSED LOG ------")
        print("Zaman       :", time_val)
        print("UID         :", uid_str)
        print("Kapı        :", gate)
        print("Kalan Bakiye:", kredi)
        print("Kart Tipi   :", kart_tipi_str)       # "Öğrenci", "Normal / Tam" vb.
        print("Aktarma     :", aktarma_durumu)       # Sadece saf aktarma durumu: 0 veya 1
        print("Sonuç       :", dusulen_kredi)       # Bu binişte düşen bakiye miktarı
        print("------------------------")

    except Exception as e:
        print("Parse hatası:", e)

def al_log():
    while True:
        b = ser.read(1)
        if b == header:
            data = ser.read(LOGSIZE)
            if len(data) == LOGSIZE:
                ser.write(b"ACK\n")
                print("LOG alındı:", data.hex())
                parse_log(data)
            else:
                print("Eksik veri, beklenilen:", LOGSIZE, "alınan:", len(data))

try:
    al_log()
except KeyboardInterrupt:
    print("Program sonlandırıldı")
finally:
    ser.close()