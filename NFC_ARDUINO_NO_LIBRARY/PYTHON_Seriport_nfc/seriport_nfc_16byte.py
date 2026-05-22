import serial
import struct

ser = serial.Serial('COM9', 9600, timeout=0.1)
LOGSIZE = 16
header = b'\xAA'

def parse_log(data):
    try:
        time_val = int.from_bytes(data[0:4], 'little')
        uid_size = data[4]
        uid = data[5:5+uid_size]
        gate = data[12]
        kredi = int.from_bytes(data[13:15], 'little')
        result = data[15]

        uid_str = ''.join(f'{b:02X}' for b in uid)

        print("------ PARSED LOG ------")
        print("Zaman   :", time_val)
        print("UID     :", uid_str)
        print("Kapı    :", gate)
        print("Kredi   :", kredi)
        print("Sonuç   :", result)
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