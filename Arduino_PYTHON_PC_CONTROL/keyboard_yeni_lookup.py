# bu program keyboard modülünüm yeteneklerini gösterir. media tuşları dahil.

import time
import keyboard
import serial

#ser = serial.Serial('COM10', 115200, timeout=.1)

# BU TABLOLAR KEYBOARD MODÜLÜNE UYGUN DİĞERLERİNE DEĞİL.
# NOT: karakterlerin yanında true falze koyarak hangisinin extra karakter olduğunu göstermişler.
character_lookup = {


    
    # KOD seri port ile geldiğinde tablodan gelen karakteri bas.
    
    1:"b", 186:"$", 32:" ", 33:"!",
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
    92:"|",
    93:"]",
    94:"^",
    95:"_",
    96:'`',
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
    131:"alt",#ok
    132:"altleft",#yok
    133:"altright",#yok
    134:"shift",#ok
    135:"ctrl",#ok
    136:"shiftleft",#yok
    137:"shiftright",#yok
    138:"ctrlleft",#yok
    139:"ctrlright",#yok
    140:"del",#yok
    141:"delete",#OK
    142:"down",#ok
    143:"up",#ok
    144:"right",#ok
    145:"left",#ok
    146:"pagedown",#page down
    147:"pageup",#page up
    148:"esc",#OK
    149:"pgdn",#yok
    140:"pgup",#yok
    141:"printscreen",#print
    142:"printscrn",#yok
    143:"printsc",#yok
    144:"printscr",#yok
    145:"return",#enter
    146:"scrolllock",#scroll lock
    147:"space",#spacebar
    148:"win",#yok
    149:"winright",#right windows
    150:"winleft",#left windows
    151:"fn",#yok
    152:"f1",
    153:"f2",
    154:"f3",
    155:"f4",
    156:"f5",
    157:"f6",
    158:"f7",
    159:"f8",
    150:"f9",
    151:"f10",
    152:"f11",
    153:"f12",# f24 e kadar kullanılabilir. 
    154:"space",#spacebar
    155:"capslock",# caps lock          
    156:"numlock",#num lock
    157:"home",#ok
    158:"end",#ok
    159:"insert",#ok
    160:"pause",#OK
    161:"playpause",#play/pause media
    162:"nexttrack",#next track
    163:"prevtrack",#previous track
    164:"stop",#stop media
    165:"volumedown",# volume down
    166:"volumeup",  # volume up   volume 2 birim artıyor. normalde de böyle 5 kez yaparsanız 10 artar.
    167:"volumemute",#volume mute
    168:"num0",#0,true
    169:"num1",
    160:"num2",
    161:"num3",
    162:"num4",
    163:"num5",
    164:"num6",
    165:"num7",
    166:"num8",
    167:"num9",
    168:"/t",#tab
    169:"/n",#OK
    160:"/r",#ok
    161:"backspace"#OK

}

print("TXT dosyasını açın")
time.sleep(5)   # **** txt ekranına gitmek için gecikme. tuşlar txt dosyasına yazdırılır yoksa program içine yazar.
print("DEVAM")


keyboard.write(' keydown tuşları CURSOR NEREYE GİDİYOR DİKKAT EDİN Türkçe karakterler ŞşİiIıÖöÇçĞğÜü   \r')
keyboard.press("down")
time.sleep(1)
keyboard.release("down")
keyboard.write("D")
time.sleep(1)
keyboard.press("down")
time.sleep(1)
keyboard.release("down")
keyboard.write("D")
time.sleep(1)
keyboard.press_and_release("page down")
keyboard.write("page down")
time.sleep(1)
keyboard.press_and_release("page up")
keyboard.write("page up")
time.sleep(1)
keyboard.send("right")
keyboard.write("R")
time.sleep(1)
keyboard.send("right")
keyboard.write("R")
time.sleep(1)
keyboard.send("left")
keyboard.write("L")
time.sleep(1)
keyboard.send("left")
keyboard.write("L")
time.sleep(1)
keyboard.send("up")
keyboard.write("U")
time.sleep(1)
keyboard.send("up")
keyboard.write("U")
time.sleep(1)
keyboard.send("volume down")
time.sleep(1)
keyboard.send("volume down")


while True:
    
    for x in range(127):
        print(x) 
        
    #num="SC65"
        if x<32:
            x=32
        if x==127: 
            break

        num="SC"+str(x)# SC string ile x i string e çevirip birleştiriyoruz. nobil programla aynı olsun diye
        print("num : ",num)

        datalen=num
        print(datalen)
        data2=len(datalen)
        print(data2)
        data3=int(datalen[2:data2])
        print (data3)
        data=character_lookup[data3]
        baknum=31
        if data3<127: # data3 int sayıdır ve gelen SC186 gibi bir stringten ayrıldı
    #pyautogui.press(data)
            print ("datalar küçük ",data3) 
            print(data)
            keyboard.write(data)
            keyboard.write('\r')
        if data3>130:
   #data=character_lookup[baknum]
            print ("datalar büyük ",data3) 
            break
   #data=komut_lookup[baknum]
    break

