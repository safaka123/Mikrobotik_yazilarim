# bu program tüm kullanılan modüllerin örneklerini birlikte gösterir. 
# DİKKAT program çalıştıktan sonra 5s sonra bir txt dosyası açık olmalı ki oraya yazsın.
# yapmazsanız TÜM KARAKTERLERİ PROGRAM İÇİNE YAZAR TEMİZLEMEK ZORUNDA KALIRSINIZ. 


import pyautogui
import time
import keyboard
import pydirectinput # daha çok directx uyumlu oyunlar için kullanılabilir. diğerleri bunda sorunlu.
import serial
from pynput.keyboard import Controller, KeyCode, Key

ser = serial.Serial('COM10', 115200, timeout=.1)


keyb = Controller() # pynput için isim tanımlaması

print("TXT dosyasını AÇIN.")
time.sleep(5)   # **** txt ekranına gitmek için gecikme. tuşlar txt dosyasına yazdırılır yoksa program içine yazar.
print("DEVAM")

# pynput yazılanlar************************* Doküman: https://pynput.readthedocs.io/en/latest/keyboard.html
# bu modülün hem tuş basma hem de basılan tuşu görebilme yeteneği var. dokümana bakınız.https://pynput.readthedocs.io/en/latest/
keyb.type('PYNPUT START \r')
keyb.press("D")
print('PRESSED: D')# tuş basılı kalır
keyb.release("D")
print('RELEASED: D')# tuş bırakılır
keyb.type('\r')
keyb.tap("E") # press ve release birlikte olur. tuşa basılır ve bırakılır. 
keyb.type('\r')
keyb.type("pynput hello  ŞsÖoÜuİiÇcĞg") # bir dize yazılır. türkçe karakter denemesiyle
keyb.type('\r')
keyb.press("Ş")
keyb.release("Ş")
keyb.type('\r')
time.sleep(3)
print (" media key kontrol")
print(" volume up")
keyb.type('MEDIA tuşları : VOLUME UP \r')
time.sleep(3)
keyb.tap(KeyCode.from_vk(0xAF))# https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
time.sleep(0.5)
keyb.tap(KeyCode.from_vk(0xAF))# volume up
time.sleep(0.5)
keyb.tap(KeyCode.from_vk(0xAF))
time.sleep(3)
keyb.type('MEDIA tuşları : VOLUME DOWN \r')
keyb.tap(KeyCode.from_vk(0xAE))# volume down
time.sleep(0.3)
keyb.tap(KeyCode.from_vk(0xAE))# volume down
time.sleep(0.3)
keyb.tap(KeyCode.from_vk(0xAE))# volume down
time.sleep(3)
keyb.type('MEDIA tuşları : VOLUME MUTE \r')
keyb.tap(KeyCode.from_vk(0xAD))# volume MUTE
time.sleep(3)
keyb.type('\r\n')
keyb.type('PYNPUT klavye kodlarını kullanır. capslock durumuna bakar. keycode sadece press ile kullanılır. \r\n')
with keyb.pressed(Key.shift):# shift ya da ctrl gibi yazılmak istenirse bu şekilde yazılacak. 
	keyb.tap('a')
	keyb.tap(KeyCode.from_vk(0xBA))# klavye tarama kodunu kullanır shift ile kullanıldığından büyük harf Ş yazar
keyb.type('\r\n') 
with keyb.pressed(Key.alt_gr):# shift ya da ctrl gibi yazılmak istenirse bu şekilde yazılacak. 
	keyb.tap('q')
time.sleep(3)
keyb.tap(KeyCode.from_vk(0xBA)) # klavye tarama kodlarını kullanır. küçük harf yazar.capslock basılı değilse
time.sleep(3)
keyb.type('\r\n')

print(" pynput bitti ")
keyb.type('PYNPUT FINISH \r\n')
keyb.type('\r\n')
#-------------------------------------------
time.sleep(5)

#pyautgui yazılanlar ************** doküman: https://pypi.org/project/PyAutoGUI/
pyautogui.typewrite( "PYAUTOGUI START ")
pyautogui.write('\n')
pyautogui.keyDown("R") # tuşa basar
print(" tuş basıldı")
time.sleep(0.1)
pyautogui.keyUp("R") # tuşu bırakır
print(" tuş bırakıldı")
time.sleep(0.1)
pyautogui.press("T")  # tuşa basar ve bırakır
pyautogui.write('\n')

pyautogui.typewrite("ALT+0+2+2+2 keypad ile turkce Ş harfi yaziliyor")
time.sleep(0.1)
pyautogui.write('\n')
pyautogui.keyDown("alt")# bu kodlama sadece key pad ile yapılabilir. bundan dolayı num0 kullan
time.sleep(0.1)
pyautogui.press("num0")
time.sleep(0.1)
pyautogui.press("num2")
time.sleep(0.1)
pyautogui.press("num2")
time.sleep(0.1)
pyautogui.press("num2")
time.sleep(0.1)
pyautogui.keyUp("alt")# bu kodlama da bittiğinde hata sesi çıkabilir hata değildir. bu komutta bunu yapıyor
time.sleep(0.1)       # bu ses sadece windowsta çıkıyor olabilir linux de olmayabilir.
pyautogui.write('\n')
print(" media tusları örnek")
pyautogui.typewrite( "MEDIA TUSLARI  VOLUME UP   VOLUME DOWN VOLUME MUTE", interval=0.1)
pyautogui.write('\n')
pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
time.sleep(3)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(0.1)
pyautogui.press("volumedown")# her volume down 2 birim hareket eder. 
time.sleep(3)
pyautogui.press("volumemute")# sesi keser 
time.sleep(0.1)

pyautogui.typewrite( "PYAUTOGUI FINISH ", interval=0.25)
pyautogui.write('DeNeME caps lock durumuna bakmiyor \n') 
pyautogui.write('\n')
print("pyautogui klavye icin gerekli bilgi dokumanlarında var.") # https://pyautogui.readthedocs.io/en/latest/

#------------------------------------------------------
keyboard.write('KEYBOARD modülü başladı \r')
#KEYBOARD modülü ile yazılanlar ************** doküman: https://pypi.org/project/keyboard/
# hem tuşlara basar hem de basılan tuşu bildirir. ayrıntı dokümanlarda  https://github.com/boppreh/keyboard
keyboard.press_and_release('shift+s, space, shift+a')
keyboard.write('\r')
print( " shift+s , space, shift+a tuşu oluşturuldu")
keyboard.write(' keydown tuşları CURSOR NEREYE GİDİYOR DİKKAT EDİN \r')
keyboard.write('\r')
keyboard.send("up")
keyboard.send("up")
time.sleep(3)
keyboard.send("right")
keyboard.send("right")
time.sleep(3)
keyboard.send("left")
keyboard.send("left")
time.sleep(3)
keyboard.send("down")
keyboard.send("down")
time.sleep(3)
keyboard.write(' KEYBOARD modülü SEND komutunda capslock durumuna bakar. \r')
keyboard.send("shift+W")# basıp bırakır  CAPS LOCK durumuna bakar. 
keyboard.send("shift+A")
keyboard.write('\r')
keyboard.write(' KEYBOARD modülü SEND komutunda capslock olmadığında ("D") yazarsanız çalışmaz.("d") yazarsanız çalışır \r')
keyboard.write('\r')
keyboard.send("D") # capslock ON ise çalışır. 
keyboard.send("d")
keyboard.write('\r')
time.sleep(3)
keyboard.write('\r')
keyboard.press('b')# tuşa basar
keyboard.release("b")# tuşu bırakır
keyboard.write('\r')
keyboard.send("w")
keyboard.send("a")
keyboard.write('\r')
keyboard.write(' KEYBOARD modülü türkçe karakterleri yazabiliyor. \r')
time.sleep(3)
keyboard.write('\r')
keyboard.write('ŞİşıĞğÜüÇçÖö  \ { | } ~ " < > @  ` # $ ^ \r \n') # dizi olarak yazıldı. Türkçe OK. CAPS LOCK durumuna bakmıyor
keyboard.write(' KEYBOARD modülü caps lock durumuna SEND komutunda bakar. basılmamışsa kücük harf yazar. \r')
keyboard.press_and_release("A") # klavyede capslock basılmadıysa a yazar basıldıysa A yazar. 
keyboard.press_and_release('shift+a') # büyük harf A verir. 
keyboard.write('\r')
keyboard.write(' KEYBOARD modülü altgr+q ile @ işareti yaptı \r')
keyboard.send("altgr+q")
keyboard.write(' KEYBOARD modülü dokümanı kayıt etti \r')
keyboard.send("ctrl+s")


# media tuşlarına hakim görünmüyor. sorunlar var gibi. 
# tuş vuruşlarını da görebilir. ayrıntı dokümanlarda
#---------------------------------------------------------------
keyboard.write(' KEYBOARD modülü bitti \r')


# PYDIRECTINPUT modülü kullanımı. doküman: https://pypi.org/project/PyDirectInput/

pydirectinput.typewrite('PYDIRECTINPUT START \n')
pydirectinput.typewrite('\n')
#********* ÖNEMLİ= joystick kontrollerini eski oyun programlarında çalıştırmak isterseniz
# bunun son versiyonu problem yaratıyor.
# bundan dolayı oyun programlarında daha çok directx kullanan oyunlarda çalışmak için 
# bu versiyonu yüklemelisiniz. https://pypi.org/project/pydirectinput-rgx/   ****************
pydirectinput.PAUSE = 0
print("pydirectinput basladi")
pydirectinput.keyDown('F')# tuş basma
time.sleep(0.2)
pydirectinput.keyUp('F')# tuş bırakma
pydirectinput.typewrite('\n')
pydirectinput.press("P")
pydirectinput.typewrite('\n')
pydirectinput.write("$ Ş DENEme") # capslock ON durumunda olmadığı için DENE kısmını da küçük harf yazıyor
pydirectinput.typewrite('\n')
pydirectinput.typewrite("hello turkce karakter yazilamadi şŞiIıİüÜÖöÇç") # bu satırın nasıl yazıldığına dikkat edin. ı harfi i harfi yerine yazıldı. türkçe karakter yazılamıyor.
pydirectinput.typewrite('\n')
pydirectinput.typewrite('PYDIRECTINPUT FINISH \n')