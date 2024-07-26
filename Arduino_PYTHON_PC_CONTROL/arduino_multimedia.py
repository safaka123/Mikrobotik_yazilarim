# Bu program ARDUINO dan gelen TUŞ basımları için örnek program öedia kontrol için. 
# PYNPUT ve PYAUTOGUI ile gösterilmektedir. 

import pyautogui
import time
import serial
from pynput.keyboard import Controller, KeyCode
from pynput.keyboard import Key

keyb = Controller()
ser = serial.Serial('COM10', 9600, timeout=.1)#Arduino kart COM port veya bluetooth com port değiştir. 

print(" BEKLEME zamanı 5s ")

time.sleep(5)

def volup(keyx): # keyx değişken tanımlamasına göre çalışmasını sağlamak içindir. bu programda kullanılmıyor.              
    keyb.press(KeyCode.from_vk(0xAF))
    time.sleep(0.5)
    keyb.release(KeyCode.from_vk(0xAF))
    #keyb.tap(KeyCode.from_vk(0xAF))
    time.sleep(0.5)
    pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    pyautogui.press("volumeup")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)

def voldown(keyx):              
    keyb.press(KeyCode.from_vk(0xAE))
    time.sleep(0.5)
    keyb.release(KeyCode.from_vk(0xAE))
    #keyb.tap(KeyCode.from_vk(0xAF))# press release komutu yerine tap kullanılabilir. 
    time.sleep(0.5)
    pyautogui.press("volumedown")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)
    pyautogui.press("volumedown")# her volume up 2 birim hareket eder. 
    time.sleep(0.1)



while True:
    data=56
    num = ser.readline()
    ser.reset_input_buffer() 
    print(num)
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
            print(" databak : ",databak)
            volup(databak)
        if data3==55:
            databak=("volumedown")
            print(" databak : ",databak)
            voldown(databak)
    
