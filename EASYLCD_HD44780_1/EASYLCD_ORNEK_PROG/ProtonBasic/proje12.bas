        Device = 16F877
        Xtal = 4
        On_Interrupt GoTo kesme          'hardware kesmesi
        ADCON1=7    'TÜM GÝRÝÞLER DÝGÝTAL
Declare Hserial_Baud=9600 
Declare Hserial_RCSTA=$90h 
Declare Hserial_TXSTA=$24h 
Declare Hserial_SPBRG= 25
Declare Hserial_Clear   =   On




;        HSERIAL_BAUD = 9600        ' Seri iletiþim hýzý 9600 bPs
;        HSERIAL_RCSTA = %10010000  ' seriport açýk ve alýma herzaman açýk
;        HSERIAL_TXSTA=%00100000    ' GÖNDERÝM AÇIK
;        HSERIAL_CLEAR = On         ' bilgi alýndýðýnda Tampon belleði temizle   

; 		LCD_DTPIN = PORTD.4	
;		LCD_RSPIN = PORTE.0
;		LCD_ENPIN = PORTE.1
;		LCD_INTERFACE = 4	' 4-bit Interface
;		LCD_LINES = 2
;		LCD_TYPE = 0
;		LCD_COMMANDUS = 2000
;		LCD_DATAUS = 50
        Symbol PEIE = INTCON.6 ' Peripheral Interrupt Enable
        Symbol GIE = INTCON.7  ' Global Interrupt Enable
        Symbol RCIE = PIE1.5   ' USART Receive Interrupt yetki
        Symbol RCIF = PIR1.5   ' USART Receive Interrupt bayraðý
        GIE=0   'tüm kesmeler kapalý 
        PEIE=1  'Çevre birim kesmesi aktif
        RCIE=1  'Usart alým kesmesi aktif 
        GIE=1   'tüm kesmeler aktif
        Dim satir As Byte   'satir adýnda byte deðiþken
        Dim Dongu As Byte   'donu adýnda byte deðiþken 
        Dim kont As Byte 
        Dim GelenBilgi As Byte
        satir=1              
        DelayMS 100
        Dongu=0
        kont=1
basla:  
If kont=1 Then 
GoTo kontrol
 Else 
 GoTo basla
 EndIf
 
kontrol:
 kont=0:Dongu=dongu+1 :If Dongu>4 Then Dongu=1                                   'ana program baþlangýç
    ;    For Dongu=1 To 16                '
;            Print At 2,Dongu,"#"         '2 satýrýn "Dongu" sütünuna "#" yaz
        If Dongu=1 Then HSerOut ["LCDDD"]
            DelayMS 10
        If Dongu=2 Then HSerOut ["LCDWR 1,1-DENEME"]
            DelayMS 10                 '100ms bekle
        If Dongu=3 Then HSerOut ["LCDNC 3-",$0E,$10,$10,$0E,$01,$05,$1E,$04] 
            DelayMS 10
        If Dongu=4 Then HSerOut ["LCDWR 2,1-","A",3,"IK"]
            DelayMS 10       
   ;     Next                             '
   ;     For Dongu=1 To 16                '
   ;         Print At 2,Dongu," "         '2 satýrýn "Dongu" sütünuna " " yaz
   ;         DelayMS 100                  '
   ;     Next                             '
        GoTo basla                       '
hata:
    ;    Print At 1,satir,"Hata"
        Return            
kesme:                                      'kesme alt programý
        Context Save                    'kayýcýlarýn içeriðini sakla
        HSerIn 5,hata,[GelenBilgi]     'Hardware Usart Kullanarak bilgiyi al "gelenbilgi"
        If GelenBilgi="R" Then 
        kont=1 
        Else
         kont=0
        EndIf 
'deðiþkeninin içeriðine at eðer timeout olursa (1000 ms) "Hata" ya dallan
        'HSerOut [GelenBilgi]
  ;      Print At 1,1,"Gelen Deger ",Dec GelenBilgi 'gelen bilginin deðerini yazdýr                       
        RCIF = 0                        'USART Receive interrupt Flag  Temizleniyor
        Context Restore                 'tüm kyýtlý reg. tekrar yüklenip keseden çýkýlýyor            
        End                             'program sonu
