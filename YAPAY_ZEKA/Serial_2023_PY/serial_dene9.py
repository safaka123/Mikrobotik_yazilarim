#import PySimpleGUI as sg 
import serial
import sys
import glob
import time
import tensorflow as tf
from tensorflow import keras
from keras.models import load_model
import numpy as np
import pandas as pd



# h5 dosyasını python 3.8 dizininden alıyor. çalışma dizini ayarlanamadı.
loaded_model = load_model("model3.h5")

son=0
data=0
hum=0
mq=0
temp=0
tvco=0
eoc2=0


#ser = None  #Global tanımlanmalı
#ser = serial.Serial(
#    port="COM1", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
#)

def serial_ports():
    if sys.platform.startswith('win'):  # windows kullanılıyorsa
        ports = ['COM%s' % (i + 1) for i in range(5)] # Hız için 256'dan 32'e düşürüldü.
      #yukarıdaki satırdaki komut i nin for döngüsüyle artarak array şeklinde yazılmasını sağlıyor. 
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

# aşağıdakiler açılabilecek portların listesini veriyor. 
    result = []
    print(ports)
    
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
        print("port")
        print(port)
        print("result  ")
        print(result)
    return result


def yapayzeka():
    global son
    print(hum, sep='\n')
    print(temp, sep='\n')
    new_data = {
    'Humidity': [hum],
    'Temperature': [temp],
    'MQ139': [mq],
    'TVOC': [tvco],
    'eCO2': [eoc2],
    }
    #Pandas DataFrame yardımıyla yukarıdaki veri modelin anlayacağı dile çevrilir
    df = pd.DataFrame(new_data)

    #Verisetinin işlem sonucu (Array içinde array olarak düşünülebilir. 0, 1 ya da 2 olmak üzere
    # yüzdelik sonuçlar elde edilir
    predictions = loaded_model.predict(df)
    print(predictions)

    #Array içinde array olarak gelen sonuçlar bir listeye dönüştürülür ve bu sayede index olarak alınabilir
    flat_list = predictions.flatten().tolist()


    #Index değişkenleri ile verilere erişilir ve okuması daha kolay olduğundan yüzdelik formatta gösterilir
    print(flat_list)
    print("%" + str(flat_list[0] * 100))
    print("%" + str(flat_list[1] * 100))
    print("%" + str(flat_list[2] * 100))
    
    if flat_list[0]*100 > 50:
        print("sonuc degeri =0")
        son=0

    if flat_list[1]*100 > 50:
        print("sonuc degeri =1")
        son=1

    if flat_list[2]*100 > 50:
        print("sonuc degeri =2")
        son=2      

def serial_baglan():
    com_deger = 'COM1'
    baud_deger = '9600'
    print("Baud Deger", '9600')
    global ser
    ser = serial.Serial(com_deger, baud_deger, timeout=0, parity=serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE , bytesize = serial.EIGHTBITS, rtscts=0)
    print("Bağlandi...", sep='\n')

serial_baglan()
while True:
    ser.write('OKU'.encode('Ascii'))
    time.sleep(10)
    data=ser.readline()
    data2=str(data).split(",")
    print(data, sep='\n')
    print(data2, sep='\n')
    #len komutu kullan if boşsa değişken işlemlerini yapmasın hata veiyor.
    if data > b'':
        hum=int(data2[1])
        temp=int(data2[2])
        mq=int(data2[3])
        tvco=int(data2[4])
        eoc2=int(data2[5])
        kont=hum+temp
        print(kont, sep='\n')
        yapayzeka()

    

        
    
    #ser.write("WRITE"+str(son).encode('Ascii')+"\n")
    STRTOPLA=str(hum)+","+str(temp)+","+str(mq)+","+str(tvco)+","+str(eoc2)+","+"...WRITE"+str(son) 
     
    ser.write('\r'.encode())
    ser.write(STRTOPLA.encode('ascii'))
    ser.write(" \r".encode())
    
    print('yazdir')
    son=5
    time.sleep(5)
    
        
