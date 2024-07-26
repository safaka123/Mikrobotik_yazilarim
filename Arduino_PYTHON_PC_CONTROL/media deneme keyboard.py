import keyboard
import pyautogui
import time
import serial
from pynput.keyboard import Controller, KeyCode
from pynput.keyboard import Key
import pydirectinput # daha çok directx uyumlu oyunlar için kullanılabilir. diğerleri bunda sorunlu.
keyb = Controller()
ser = serial.Serial('COM10', 9600, timeout=.1)

time.sleep(5)
#keyboard.write(str(128))
#keyboard.write("up")

#keyboard.press_and_release("A")
#keyboard.press_and_release('shift+a')
#keyb.press(KeyCode.from_vk(0xAF))# https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

#********* ÖNEMLİ= joystick kontrollerini eski oyun programlarında çalıştırmak isterseniz
# bunun son versiyonu problem yaratıyor.
# bundan dolayı oyun programlarında daha çok directx kullanan oyunlarda çalışmak için 
# bu versiyonu yüklemelisiniz. https://pypi.org/project/pydirectinput-rgx/   ****************

# pydirectinput pyautoguiden oluşturulmuş. onun bazı komutlarını kullanan çok az sayıda komutu olan bir modüldür
# en önemli tarafı directx uyumlu olması. bundan dolayı joystick kullanımı için faydalanabilirsiniz.

# bununla yapılmış bluetooth joystick programı videolarda var. 
# türkçe karakter yazılamaz. 
def volup(key):               #what to do if key pressed. takes value from handleJoyStickAsArrowKeys
    keyb.press(KeyCode.from_vk(0xAF))
    time.sleep(0.5)
    keyb.release(KeyCode.from_vk(0xAF))
    #keyb.tap(KeyCode.from_vk(0xAF))
    time.sleep(0.5)
    pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    #keyb.tap(KeyCode.from_vk(0xAF))
    #pyautogui.press(key)  #runs pydirectinput using key from (argument)
    #print('UP: ', key)       #remove '#' from print to test data stream

def voldown(key):               #what to do if key pressed. takes value from handleJoyStickAsArrowKeys
    keyb.press(KeyCode.from_vk(0xAE))
    time.sleep(0.5)
    keyb.release(KeyCode.from_vk(0xAE))
    #keyb.tap(KeyCode.from_vk(0xAF))
    time.sleep(0.5)
    pyautogui.press("volumedown")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    pyautogui.press("volumedown")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    #keyb.tap(KeyCode.from_vk(0xAF))
    #pyautogui.press(key)  #runs pydirectinput using key from (argument)
    #print('UP: ', key)       #remove '#' from print to test data stream


while True:
    data=56
    #time.sleep(3)
    num = ser.readline()
    ser.reset_input_buffer() 
    #num=num[0:2]
    print(num)
    #num="SC186"
    datalen=num
    print(datalen)
    data2=len(datalen)
    if data2>4:
       num=num[0:4] 
       datalen=num
       print(datalen)
       data2=len(datalen)

    if data2>0:
        data3=int(datalen[2:data2])
    else:
        data3=0

    
    data=0
    databak=""
    if data2>0:
        print(data2)
        print (data3)
        print ("data3  ",data3)
        if data3==56:
            databak=("volumeup")
            #databak=komut_lookup[data3]
            print(" databak : ",databak)
            volup(databak)
        if data3==55:
            databak=("volumedown")
            #databak=komut_lookup[data3]
            print(" databak : ",databak)
            voldown(databak)
    
