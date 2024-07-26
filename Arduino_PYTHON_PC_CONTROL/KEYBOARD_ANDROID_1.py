import pyautogui
import time
import keyboard
import serial

# TÜM KARAKTERLER YAZILIYOR. SERİ PORT HABERLEŞMESİ KULLANILARAK ANDROİD PROGRAM İLE YAZDIRILABİLİR. 


ser = serial.Serial('COM10', 9600, timeout=.1) # bu programda seri port kontrolü yok. 

# aşağıdaki tablo sadece PYAUTOGUI kütüphanesine uygun yapılmıştır. diğer kütüphanelerde numara aynı olmayabilir.

character_lookup = {


    
    # KOD seri port ile geldiğinde tablodan gelen karakteri bas.
    #601814: 'Brown, Mary',
    #716978: 'Green, John',
    1:"volumeup", 186:"Ş", 32:" ", 33:"!",
    34:'"',
    35:"#",
    36:"$",
    37:"%",
    38:"&",
    39:"'",
    40:"(",
    41:")",
    42:"*",
    43:"+",
    44:",",
    45:"-",
    46:".",
    47:"/",
    48:"0",
    49:"1",
    50:"2",
    51:"3",
    52:"4",
    53:"5",
    54:"6",
    55:"7",
    56:"8",
    57:"9",
    58:":",
    59:";",
    60:"<",
    61:"=",
    62:">",
    63:"?",
    64:"@",
    65:"A",
    66:"B",
    67:"C",
    68:"D",
    69:"E",
    70:"F",
    71:"G",
    72:"H",
    73:"I",
    74:"J",
    75:"K",
    76:"L",
    77:"M",
    78:"N",
    79:"O",
    80:"P",
    81:"Q",
    82:"R",
    83:"S",
    84:"T",
    85:"U",
    86:"V",
    87:"W",
    88:"X",
    89:"Y",
    90:"Z",
    91:"[",
    #92:'\',# keyboard write ile yapılacak. 
    93:"]",
    #94:"^",^ keyboard write ile yapılacak. 
    95:"_",
    #96:'`',
    97:"a",
    98:"b",
    99:"c",
    100:"d",
    101:"e",
    102:"f",
    103:"g",
    104:"h",
    105:"i",
    106:"j",
    107:"k",
    108:"l",
    109:"m",
    110:"n",
    111:"o",
    112:"p",
    113:"q",
    114:"r",
    115:"s",
    116:"t",
    117:"u",
    118:"v",
    119:"w",
    120:"x",
    121:"y",
    122:"z",
    123:'{',
    124:'|',
    125:'}',
    126:'~'

}
komut_lookup = {
    1:"alt",
    2:"altleft",
    3:"altright",
    4:"shift",
    5:"ctrl",
    6:"shiftleft",
    7:"shiftright",
    8:"ctrlleft",
    9:"ctrlright",
    10:"del",
    11:"delete",
    12:"down",
    13:"up",
    14:"right",
    15:"left",
    16:"pagedown",
    17:"pageup",
    18:"esc",
    19:"pgdn",
    20:"pgup",
    21:"printscreen",
    22:"printscrn",
    23:"printsc",
    24:"printscr",
    25:"return",
    26:"scrolllock",
    27:"space",
    28:"win",
    29:"winright",
    30:"winleft",
    31:"fn",
    32:"f1",
    33:"f2",
    34:"f3",
    35:"f4",
    36:"f5",
    37:"f6",
    38:"f7",
    39:"f8",
    40:"f9",
    41:"f10",
    42:"f11",
    43:"f12",
    44:"space",
    45:"capslock",
    46:"numlock",
    47:"home",
    48:"end",
    49:"insert",
    50:"pause",
    51:"playpause",
    52:"nexttrack",
    53:"prevtrack",
    54:"stop",
    55:"volumedown",
    56:"volumeup",  # volume 2 birim artıyor. normalde de böyle 5 kez yaparsanız 10 artar.
    57:"volumemute",
    58:"num0",
    59:"num1",
    60:"num2",
    61:"num3",
    62:"num4",
    63:"num5",
    64:"num6",
    65:"num7",
    66:"num8",
    67:"num9",
    68:"/t",
    69:"/n",
    70:"/r",
    71:"backspace"

}

print(character_lookup[186])
print(character_lookup[65])

print("Before the sleep statement")
time.sleep(5)   # **** txt ekranına gitmek için gecikme notepad açmak için

print("After the sleep statement")
num="SC186"
datalen=num
print(datalen)
data2=len(datalen)
print(data2)
data3=int(datalen[2:data2])
print (data3)
print(" ayrilmiş ")
data=character_lookup[data3]
#dataal=character_lookup[601814]
#print(dataal)


#if data.find("Ş")>-1:
#    turkyazC1()

if data3<128: # data3 int sayıdır ve gelen SC186 gibi bir stringten ayrıldı
    #pyautogui.press(data)
    print(data)

if data3>127:
   #turkyazC1(data3)
   print ("datalar",data3) 
baknum=31
while True:
    baknum=baknum+1
    if baknum>127:
        baknum=32
        break
    if baknum>31 and baknum<127: # data3 int sayıdır ve gelen SC186 gibi bir stringten ayrıldı
        if baknum==92 or baknum==96 or baknum==94:
            print("numara : ",baknum,"karakter :  keyboard yaz."   )
            keyboard.write('ŞİşıĞğÜüÇçÖö  \ { | } ~ " < > @  ` # $ ^ \r \n')
        else:    
            data=character_lookup[baknum]
            pyautogui.press(data)
            keyboard.write('\r')
            print("numara : ",baknum,"karakter : ",data)
print( "2. bölüm \r")  
baknum=56 # ********** SADECE volume up MULTİMEDYA TUŞU KULLANILIYOR. 
gecbak=0
while True:
    gecbak=gecbak+1
    if gecbak>5:
        gecbak=0
        break

    if baknum>31 and baknum<127: # data3 int sayıdır ve gelen SC186 gibi bir stringten ayrıldı
        if baknum==92 or baknum==96 or baknum==94:
            print("numara : ",baknum,"karakter :  keyboard yaz."   )
            keyboard.write('ŞİşıĞğÜüÇçÖö  \ { | } ~ " < > @  ` # $ ^ \r \n')
        else:    
            data=komut_lookup[baknum]
            pyautogui.press(data)
            #keyboard.write('\r')
            print("numara : ",baknum,"karakter : ",data) 

# seri porttan karakter bekle
