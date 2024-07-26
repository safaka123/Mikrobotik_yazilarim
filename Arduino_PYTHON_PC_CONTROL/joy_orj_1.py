# bu program PYDIRECTINPUT kullanıyor. Bu modül otunlarda kullanılan DIRECTX uyumludur. JOYSTICK kullanımı
#********* ÖNEMLİ= joystick kontrollerini eski oyun programlarında çalıştırmak isterseniz
# bunun son versiyonu problem yaratıyor.
# bundan dolayı oyun programlarında daha çok directx kullanan oyunlarda çalışmak için 
# bu versiyonu yüklemelisiniz. https://pypi.org/project/pydirectinput-rgx/   ****************

# bu program bluetooth remote control programını kullanır. 
import serial
import time
import pydirectinput

ser = serial.Serial('COM10', 9600, timeout=.1)     #serial input from arduino. change COM port to wherever your arduino is connected

pydirectinput.PAUSE = 0

keysDown = {}   #list of currently pressed keys


def keyDown(key):               #what to do if key pressed. takes value from handleJoyStickAsArrowKeys
    keysDown[key] = True        #adds key to KeysDown list
    pydirectinput.keyDown(key)  #runs pydirectinput using key from (argument)
    print('Down: ', key)       #remove '#' from print to test data stream


def keyUp(key):                     #what to do if key released. takes value from handleJoyStickAsArrowKeys
    if key in keysDown:
        del (keysDown[key])         #remove key from KeysDown
        pydirectinput.keyUp(key)    #runs pydirectinput using key from (argument)
        print('Up: ', key)         #remove '#' from print to test data stream


def handleJoyStickAsArrowKeys(x, y, z):     #note that the x and y directions are swapped due to the way I orient my thumbstick
    #time.sleep(0.5) ******************* ******************************* GECİKME İÇİN BUNU DEVREYE AL. 
    if x == 0:          #0 is up on joystick
        keyDown('up')   #add up key to keyDown (argument)
        keyUp('down')   #add down key to keyUp (argument), as you can't press up and down together
    elif x == 2:        #2 is down on joystick
        keyDown('down')
        keyUp('up')
    else:               #1 is neutral on joystick
        keyUp('up')
        keyUp('down')

    if y == 2:          #2 is right on joystick
        keyDown('right')
        keyUp('left')
    elif y == 0:        #0 is left on joystick
        keyDown('left')
        keyUp('right')
    else:               #1 is neutral on joystick
        keyUp('left')
        keyUp('right')

    if z == 1:          #z argument is JSButton in this case. 1 is button pressed
        keyDown('i')    #key to be pressed with Joystick button. Change to any key
    else:
        keyUp('i')      #0 is button not pressed


while True:
    
    data = ser.read()
    ser.reset_input_buffer() 
    print(data)
    #dx=0
    #dy=0
    bak=0
    if data==b'F':
        dx=0
        dy=1
        #dx=int(a)
        bak=1

    if data==b'B':
        dx=2
        dy=1
        #dx=int(b)
        bak=1
        
    if data==b'L':
        dy=0
        
        #dy=int(c)
        bak=1

    if data==b'R':
        dy=2
        #dy=int(d)
        bak=1

    if data==b'G':
        dx=0
        dy=0
        bak=1
    
    if data==b'I':
        dx=0
        dy=2
        bak=1
    if data==b'H':
        dx=2
        dy=0
        bak=1
    if data==b'J':
        dx=2
        dy=2
        bak=1
        
    if bak!=1:
        dx=1
        dy=1


    JSButton=0
   
    print(dx, dy, JSButton)            #remove '#' from print to test data stream
    handleJoyStickAsArrowKeys(dx, dy, JSButton)     #run body of code using dx, dy and JSButton as inputs
