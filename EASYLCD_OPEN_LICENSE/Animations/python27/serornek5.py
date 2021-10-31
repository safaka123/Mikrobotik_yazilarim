# -*- coding: cp1254 -*-
# programın orjinali C:\Python27\sample dizininde çalışmalı.
#çünkü python ve serial library o dizinde bulunuyor.


import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
#ser = serial.Serial(
#	port='COM1',
#	baudrate=9600,
#	parity=serial.PARITY_NONE,
#	stopbits=serial.STOPBITS_ONE,
#	bytesize=serial.EIGHTBITS
#)

ser       =  serial.Serial('com2', 9600)
ser.close()
ser.open()
ser.isOpen()
time.sleep(1)

#                        GERİ BİLDİRİMLERİ ALAN BÖLÜM

def bilgial(a):
    time.sleep(1)
    say=""
    while True :
        ser.inWaiting() > 0 
        say= ser.read(5)
        print say
        print  a
        if (say=="LCD R" or say=="LCD P" or say=="LCD H") :
            break
        
#                            ANİMASYON BÖLÜMÜ

ser.write("LCDDD")
bilgial(1)

ser.write("LCDWR 1,1-ILKSATIR")
bilgial(2)

ser.write("LCDWR 2,1-IKINCI SATIR")
bilgial(3)

ser.write("LCDWR 3,1-UCUNCU SATIR")
bilgial(4)

ser.write("LCDWR 4,1-DORDUNCU SATIR")
bilgial(5)

print "den" # SHELL EKRANINA YAZDIRIYOR.


ser.close()

