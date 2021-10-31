VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form winamp_lcd 
   Caption         =   "Winamp_lcd_safak"
   ClientHeight    =   8115
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   13485
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   162
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "winamp_lcd_3.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8115
   ScaleWidth      =   13485
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox Text4 
      Alignment       =   2  'Center
      BackColor       =   &H0000FFFF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2295
      Left            =   11040
      MultiLine       =   -1  'True
      TabIndex        =   57
      Text            =   "winamp_lcd_3.frx":164A
      Top             =   120
      Width           =   2295
   End
   Begin VB.TextBox aktargonder 
      Height          =   375
      Left            =   180
      TabIndex        =   56
      Text            =   "aktar"
      Top             =   5850
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.CommandButton temiz 
      Caption         =   "LCD clear"
      Height          =   510
      Left            =   11250
      TabIndex        =   55
      Top             =   5445
      Width           =   1095
   End
   Begin VB.CommandButton nameyaz 
      Caption         =   "LCD name"
      Height          =   690
      Left            =   10260
      TabIndex        =   54
      Top             =   6255
      Width           =   780
   End
   Begin VB.CommandButton titleyaz 
      Caption         =   "LCD title"
      Height          =   645
      Left            =   10260
      TabIndex        =   53
      Top             =   5490
      Width           =   780
   End
   Begin VB.CommandButton artistyaz 
      Caption         =   "LCD artist"
      Height          =   600
      Left            =   10260
      TabIndex        =   52
      Top             =   4815
      Width           =   780
   End
   Begin VB.TextBox song_pos 
      Alignment       =   2  'Center
      Height          =   375
      Left            =   7920
      TabIndex        =   51
      Top             =   6480
      Width           =   1050
   End
   Begin VB.TextBox songlength_orj 
      Height          =   375
      Left            =   225
      TabIndex        =   49
      Top             =   7470
      Visible         =   0   'False
      Width           =   1365
   End
   Begin VB.TextBox cur_song_position 
      Height          =   375
      Left            =   225
      TabIndex        =   48
      Top             =   6975
      Visible         =   0   'False
      Width           =   1365
   End
   Begin VB.Timer Timer2 
      Interval        =   100
      Left            =   1980
      Top             =   5310
   End
   Begin VB.TextBox winampstatus 
      Alignment       =   2  'Center
      Height          =   375
      Left            =   6120
      TabIndex        =   47
      Top             =   7020
      Width           =   1410
   End
   Begin VB.TextBox songnumber 
      Alignment       =   2  'Center
      Height          =   315
      Left            =   7920
      TabIndex        =   45
      Top             =   6030
      Width           =   1050
   End
   Begin VB.TextBox songtime 
      Alignment       =   2  'Center
      Height          =   330
      Left            =   4905
      TabIndex        =   43
      Top             =   6525
      Width           =   1140
   End
   Begin VB.TextBox Playlistlength 
      Alignment       =   2  'Center
      Height          =   360
      Left            =   4905
      TabIndex        =   41
      Top             =   6030
      Width           =   1140
   End
   Begin VB.TextBox Eqenable 
      Height          =   360
      Left            =   4905
      TabIndex        =   39
      Top             =   5580
      Width           =   4065
   End
   Begin VB.TextBox aktar 
      Height          =   465
      Left            =   225
      TabIndex        =   37
      Text            =   "gizle"
      Top             =   6300
      Visible         =   0   'False
      Width           =   1185
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Winamp READ"
      Height          =   645
      Left            =   11070
      TabIndex        =   36
      Top             =   2790
      Width           =   1860
   End
   Begin VB.CommandButton Command3 
      Caption         =   "ID3 READ"
      Height          =   645
      Left            =   11070
      TabIndex        =   35
      Top             =   3555
      Width           =   1860
   End
   Begin VB.TextBox Tsongpath 
      Height          =   375
      Left            =   4905
      TabIndex        =   34
      Text            =   "D:\mp3\Abba - Gimme! Gimme! Gimme! (A Man After Midnight).mp3"
      Top             =   5085
      Width           =   4020
   End
   Begin VB.TextBox Tsongyear 
      Height          =   360
      Left            =   4905
      TabIndex        =   32
      Text            =   "Song Year"
      Top             =   4635
      Width           =   4065
   End
   Begin VB.TextBox Tsongalbum 
      Height          =   375
      Left            =   4905
      TabIndex        =   31
      Text            =   "Song Album"
      Top             =   4140
      Width           =   4065
   End
   Begin VB.TextBox Tsongartist 
      Height          =   345
      Left            =   4905
      TabIndex        =   30
      Text            =   "Song Artist"
      Top             =   3690
      Width           =   4065
   End
   Begin VB.TextBox Tsongtitle 
      Height          =   360
      Left            =   4905
      TabIndex        =   29
      Text            =   "Song Title"
      Top             =   3240
      Width           =   4065
   End
   Begin VB.TextBox Tsongname 
      Height          =   360
      Left            =   5445
      TabIndex        =   28
      Text            =   "Song Name"
      Top             =   2835
      Width           =   5505
   End
   Begin VB.TextBox timer4_sayac 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   180
      TabIndex        =   22
      Text            =   "0"
      Top             =   5355
      Visible         =   0   'False
      Width           =   420
   End
   Begin VB.TextBox READY 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   465
      Left            =   2565
      TabIndex        =   20
      Text            =   "0"
      Top             =   4725
      Visible         =   0   'False
      Width           =   330
   End
   Begin VB.TextBox Text3 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   765
      TabIndex        =   19
      Text            =   "Text3"
      Top             =   5310
      Visible         =   0   'False
      Width           =   1050
   End
   Begin VB.CheckBox Check1 
      Caption         =   "durdur"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   765
      TabIndex        =   18
      Top             =   4635
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.TextBox Text2 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000D&
      Height          =   735
      Left            =   3240
      MultiLine       =   -1  'True
      TabIndex        =   16
      Text            =   "winamp_lcd_3.frx":1685
      Top             =   1665
      Width           =   5895
   End
   Begin VB.ComboBox datasec 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "winamp_lcd_3.frx":1691
      Left            =   480
      List            =   "winamp_lcd_3.frx":169B
      TabIndex        =   14
      Text            =   "8"
      Top             =   2880
      Width           =   615
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FFFF00&
      Caption         =   "PORT SCAN"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   315
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   225
      Width           =   1095
   End
   Begin VB.CommandButton closeport 
      BackColor       =   &H000000FF&
      Caption         =   "Close Port"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   840
      Width           =   1215
   End
   Begin VB.CommandButton openport 
      BackColor       =   &H0000FF00&
      Caption         =   "Open Port"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1680
      MaskColor       =   &H0000FF00&
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   240
      Width           =   1215
   End
   Begin VB.ComboBox PORT 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "winamp_lcd_3.frx":16A5
      Left            =   360
      List            =   "winamp_lcd_3.frx":16A7
      TabIndex        =   10
      Text            =   "1"
      Top             =   1200
      Width           =   975
   End
   Begin VB.TextBox DURUM 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   0
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   9
      Text            =   "winamp_lcd_3.frx":16A9
      Top             =   3480
      Width           =   3015
   End
   Begin VB.ComboBox Combo3 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "winamp_lcd_3.frx":16B5
      Left            =   1800
      List            =   "winamp_lcd_3.frx":16BF
      TabIndex        =   8
      Text            =   "1"
      Top             =   2880
      Width           =   615
   End
   Begin VB.ComboBox Combo2 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "winamp_lcd_3.frx":16C9
      Left            =   1680
      List            =   "winamp_lcd_3.frx":16DC
      TabIndex        =   5
      Text            =   "None"
      Top             =   2040
      Width           =   855
   End
   Begin VB.ComboBox Combo1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "winamp_lcd_3.frx":16FE
      Left            =   360
      List            =   "winamp_lcd_3.frx":1720
      TabIndex        =   4
      Text            =   "9600"
      Top             =   2040
      Width           =   975
   End
   Begin VB.Timer Timer1 
      Interval        =   10
      Left            =   2070
      Top             =   4680
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   90
      Top             =   4635
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      CommPort        =   4
      DTREnable       =   -1  'True
      InputLen        =   1
   End
   Begin VB.CommandButton Command1 
      Caption         =   "SEND DATA"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   9240
      TabIndex        =   1
      Top             =   1680
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000002&
      Height          =   615
      Left            =   3240
      MultiLine       =   -1  'True
      TabIndex        =   0
      Text            =   "winamp_lcd_3.frx":1766
      Top             =   960
      Width           =   7455
   End
   Begin VB.Label Label16 
      Caption         =   "Song Position"
      Height          =   330
      Left            =   6165
      TabIndex        =   50
      Top             =   6525
      Width           =   1635
   End
   Begin VB.Label Label15 
      Caption         =   "Winamp Status"
      Height          =   285
      Left            =   4500
      TabIndex        =   46
      Top             =   7065
      Width           =   1500
   End
   Begin VB.Label Label14 
      Caption         =   "Song Number"
      Height          =   330
      Left            =   6210
      TabIndex        =   44
      Top             =   6030
      Width           =   1590
   End
   Begin VB.Label Label13 
      Caption         =   "Song Length"
      Height          =   285
      Left            =   3330
      TabIndex        =   42
      Top             =   6525
      Width           =   1500
   End
   Begin VB.Label Label12 
      Caption         =   "Playlist Length"
      Height          =   285
      Left            =   3330
      TabIndex        =   40
      Top             =   6075
      Width           =   1455
   End
   Begin VB.Label Label11 
      Caption         =   "Equalizer ON"
      Height          =   285
      Left            =   3330
      TabIndex        =   38
      Top             =   5625
      Width           =   1410
   End
   Begin VB.Label Label10 
      Caption         =   "Song Path"
      Height          =   330
      Left            =   3375
      TabIndex        =   33
      Top             =   5130
      Width           =   1365
   End
   Begin VB.Label Label9 
      Caption         =   "Song Year"
      Height          =   285
      Left            =   3375
      TabIndex        =   27
      Top             =   4680
      Width           =   1365
   End
   Begin VB.Label Label8 
      Caption         =   "Song Album"
      Height          =   285
      Left            =   3375
      TabIndex        =   26
      Top             =   4230
      Width           =   1365
   End
   Begin VB.Label Label7 
      Caption         =   "Song Artist"
      Height          =   285
      Left            =   3375
      TabIndex        =   25
      Top             =   3780
      Width           =   1365
   End
   Begin VB.Label Label6 
      Caption         =   "Song Title"
      Height          =   285
      Left            =   3375
      TabIndex        =   24
      Top             =   3330
      Width           =   1365
   End
   Begin VB.Label Label1 
      Caption         =   "Song Artist-Name"
      Height          =   285
      Left            =   3375
      TabIndex        =   23
      Top             =   2880
      Width           =   1950
   End
   Begin VB.Label Label5 
      Caption         =   "sadece kontrol amaçlý"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   465
      Left            =   5715
      TabIndex        =   21
      Top             =   11160
      Visible         =   0   'False
      Width           =   1185
   End
   Begin VB.Label TITLE 
      Alignment       =   2  'Center
      Caption         =   "SERÝ LCD KONTROL PROGRAMI"
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   18
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3360
      TabIndex        =   17
      Top             =   240
      Width           =   7335
   End
   Begin VB.Label Label4 
      Alignment       =   2  'Center
      Caption         =   "DATA"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   480
      TabIndex        =   15
      Top             =   2520
      Width           =   735
   End
   Begin VB.Shape Shape1 
      BorderWidth     =   3
      Height          =   3255
      Left            =   120
      Shape           =   4  'Rounded Rectangle
      Top             =   120
      Width           =   2895
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "STOP"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1800
      TabIndex        =   7
      Top             =   2520
      Width           =   495
   End
   Begin VB.Label parite 
      Alignment       =   2  'Center
      Caption         =   "PARÝTE"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1680
      TabIndex        =   6
      Top             =   1680
      Width           =   855
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "BAUD"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   360
      TabIndex        =   3
      Top             =   1680
      Width           =   855
   End
   Begin VB.Label PORTLABEL 
      Alignment       =   2  'Center
      BackColor       =   &H0000FFFF&
      Caption         =   "PORT"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   495
      TabIndex        =   2
      Top             =   855
      Width           =   735
   End
End
Attribute VB_Name = "winamp_lcd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim saylcd(7) As Integer
Dim startpos As Integer
Dim saybak As Integer

Private Sub artistyaz_Click()
Text2.Text = "LCDWR 1,1-" + Tsongartist.Text: Text2.Text = Left$(Text2.Text, 35)
Call Command1_Click

End Sub

Private Sub closeport_Click()
Timer1.Enabled = False
'Timer2.Enabled = False
On Error Resume Next
DURUM.BackColor = vbGreen
DURUM.Text = " PORT KAPANDI"
'MSComm1.CommPort = PORT.Text
MSComm1.PortOpen = False
PORTLABEL.BackColor = vbYellow '
'Text3.Text = Err
If Err = 8005 Then
DURUM.BackColor = vbRed
PORTLABEL.BackColor = vbRed
DURUM.Text = " Kullanýmdaki portu öncelikle kapatýn " & Err & vbCrLf
End If

If Err = 8012 Then
DURUM.BackColor = vbRed
PORTLABEL.BackColor = vbYellow
DURUM.Text = " Kapatýlan portu tekrar kapattýnýz: " & Err & " öncelikle PORT seçin sonra PORT açýn" & vbCrLf
          
End If

End Sub

Private Sub Command1_Click()
ReDim kont(54)
On Error Resume Next

Dim komut As String
READY.Text = 0
Text1.Text = ""
CHAR1 = Val("&H" + Text6.Text)
CHAR2 = Val("&H" + Text7.Text)
CHAR3 = Val("&H" + Text8.Text)
CHAR4 = Val("&H" + Text9.Text)
CHAR5 = Val("&H" + Text10.Text)
CHAR6 = Val("&H" + Text11.Text)
CHAR7 = Val("&H" + Text12.Text)
CHAR8 = Val("&H" + Text13.Text)
bak = 0
komut = Text2.Text
bak = InStr(1, komut, "-")
If bak > 0 Then komut = Left$(Text2.Text, bak)



bak = 0
bak = InStr(1, komut, "NC")
If bak > 0 Then MSComm1.Output = Text2.Text + Chr$(CHAR1) + Chr$(CHAR2) + Chr$(CHAR3) + Chr$(CHAR4) + Chr$(CHAR5) + Chr$(CHAR6) + Chr$(CHAR7) + Chr$(CHAR8):
'If bak > 0 Then sendstring = Text2.Text + CHR$(20) + CHAR1 + CHAR2 + CHAR3 + CHAR4 + CHAR5 + CHAR6 + CHAR7 + CHAR8 Else sendstring = Text2.Text
bak1 = 0
bak1 = InStr(1, komut, "EW")
If bak1 > 0 Then MSComm1.Output = Text2.Text + Chr$(CHAR1) + Chr$(CHAR2) + Chr$(CHAR3) + Chr$(CHAR4) + Chr$(CHAR5) + Chr$(CHAR6) + Chr$(CHAR7) + Chr$(CHAR8)

lcdbul = 0
lcdbul = InStr(1, komut, "WR")
If lcdbul > 0 Then
Text3.Text = Text2.Text
lcdbak = Len(Text3.Text)
akt = InStr(1, Text2.Text, "-")
lcdbak = lcdbak - akt
'Text3.Text = Right$(Text3.Text, lcdbak)
'LCDWR 1,1-DENEME123

For tt = 1 To 52   'LCDWR 4,15-12345678901234567890
kont(tt) = Asc(Mid$(Text3.Text, tt, 1))
If kont(tt) = 0 Then jump = tt: GoTo part2
If kont(tt) < 30 Then kont(tt) = kont(tt) - 20
'If kont(tt) > 30 Then kont(tt) = kont(tt) + 20
'If kont(tt) = -20 Then kont(tt) = 24
Next

part2:
Text3.Text = ""

For tt = 1 To jump - 1
'Chr$ (kont(tt))
denbak = denbak + Chr$(kont(tt))
'Text3.Text = Text3.Text + Chr$(kont(tt))
Next tt

End If

MSComm1.Output = denbak
'MSComm1.Output = Chr$((kont(1) - 20)) + Chr$((kont(2) - 20)) + Chr$((kont(3) - 20)) + Chr$((kont(4) - 20)) + Chr$((kont(5) - 20)) + Chr$((kont(6) - 20)) + Chr$((kont(7) - 20)) + Chr$((kont(8) - 20)) + Chr$((kont(9) - 20)) + Chr$((kont(10) - 20)) + Chr$((kont(11) - 20)) + Chr$((kont(12) - 20)) + Chr$((kont(13) - 20)) + Chr$((kont(14) - 20)) + Chr$((kont(15) - 20)) + Chr$((kont(16) - 20)) + Chr$((kont(17) - 20)) + Chr$((kont(18) - 20)) + Chr$((kont(19) - 20)) + Chr$((kont(20) - 20)) + Chr$((kont(21) - 20)) + Chr$((kont(22) - 20)) + Chr$((kont(23) - 20)) + Chr$((kont(24) - 20)) + Chr$((kont(25) - 20)) + Chr$((kont(26) - 20)) + Chr$((kont(27) - 20))
If bak = 0 And bak1 = 0 And lcdbul = 0 Then MSComm1.Output = Text2.Text
'Text3.Text = ""


If Err = 8018 Then
         DURUM.Text = DURUM.Text & "Port açýk deðil. Bilgi gönderemezsiniz" & Err & vbCrLf
         DURUM.BackColor = vbRed
         Error.Clear
End If
End Sub

Private Sub Command2_Click()
DURUM.Text = "PORTLAR TARANIYOR" & vbCrLf & "Com-1 , Com-20 arasý "
DURUM.BackColor = vbYellow

Pause 0.05


On Error Resume Next

   For i = 1 To 20
         DURUM.Text = DURUM.Text & "port " & i & " taranýyor" & Err & vbCrLf
'         Text3.Text = Err
         MSComm1.CommPort = i
         MSComm1.PortOpen = True
      If Err = 8005 Then
         MSComm1.PortOpen = False
         PORTLABEL.BackColor = vbYellow
         DURUM.Text = DURUM.Text & "port " & i & " kullanýmda" & Err & vbCrLf
         DURUM.BackColor = vbRed
         Error.Clear
         
         'list1.AddItem "Port " & i & InUseMsg
         'PortInUse% = PortInUse% + 1
      End If
           If Err = 8002 Then
      DURUM.Text = DURUM.Text & "port " & i & " yok" & Err & vbCrLf
       MSComm1.PortOpen = False
'         Text3.Text = Err
      Error.Clear
      
      'list1.AddItem "Port " & i & NoExistMsg
      End If
      
            
      If Err = 8012 Then
      
      DURUM.BackColor = vbGreen: DURUM.Text = DURUM.Text & "port " & i & "hatalý" & vbCrLf 'list1.AddItem "Port " & i & FailedMsg
            MSComm1.PortOpen = False
            PORTLABEL.BackColor = vbYellow
'         Text3.Text = Err
         Error.Clear
         'Label2.Caption = OpenedPorts% + PortInUse% & TotalPort$
      End If
      
      If MSComm1.PortOpen = True Then
            PORT.AddItem i
          DURUM.Text = DURUM.Text & "port " & i & " hazýr" & vbCrLf
           MSComm1.PortOpen = False
'         Text3.Text = Err
         'list1.AddItem "Port " & i & OpenedMsg
         'OpenedPorts% = OpenedPorts% + 1
      End If
            
 
   ' Stop
    Next
PORT.ListIndex = 0
Text2.Text = PORT.Text
End Sub


Private Sub Command3_Click()
aktar.Text = MP3read_GetTagInfo_ID3v2(Tsongpath.Text, songTitle$, songArtist$, songAlbum$, songYear$, songComment$, 1, 1, songComposer$, songOriginalArtist$, songCopyright$, songURL$, songEncodedBy$)
Tsongartist.Text = songArtist$
Tsongyear.Text = songYear$      ' track number gibi olanlarý str$ ile string yap aktar. bas dosyasýnda.
Tsongtitle.Text = songTitle$
Tsongalbum.Text = songAlbum$

End Sub

Private Sub Command4_Click()
Tsongname.Text = getWinampWindowText

If GetEQEnabled = 1 Then Eqenable.Text = "EQU. ON" Else Eqenable.Text = "EQU. OFF"
Playlistlength.Text = GetPlayListLength
songtimer = GetSongLength: songsan = songtimer Mod 60: songdak = (songtimer - songsan) / 60:
If Len(songsan) < 2 Then songtime = LTrim$(Str$(songdak)) + " : 0" + LTrim$(Str$(songsan)) Else songtime = LTrim$(Str$(songdak)) + " : " + LTrim$(Str$(songsan))

songnumber.Text = GetPlayListPosition + 1
songlength_orj.Text = GetSongLength:


FindWinamp
GetMp3Info
Tsongpath = MP3Info.MPEGInfo

End Sub



Private Sub Form_Load()
Timer1.Enabled = False
'Combo1.ListIndex = 5
'Combo2.ListIndex = 0
'Combo3.ListIndex = 0
datasec.ListIndex = 0


'If MSComm1.PortOpen = True Then 'port açýkmý kontrol et
'MSComm1.PortOpen = False 'açýk ise kapat
'End If
'MSComm1.CommPort = 4 '1 numaralý com port kullanýlacak
'MSComm1.Settings = "9600,N,8,1" '2400baud party biti yok 8data biti 1stop biti olarak data yollanacak
'MSComm1.PortOpen = True 'portu aç
'Form1.Caption = "HAS_ARTVÝNLÝ -- PROGRAM 2400 BAUD ÝLE VE 8N1 FORMATINDA ÇALIÞIR" 'formun baþlýðýný deðiþtir


'Text1.Enabled = False 'text kutusunun yazýlabilirliðini kapat
'Text1.Text = "" 'text kutusunun içini boþalt
'Command1.Caption = "DATA YOLLA" 'butonun adýný data yolla olarak deðiþ
'Label1.Caption = "GELEN DATA"
'Timer1.Interval = 10 'timer in interval deðeri 10ms de bir gelen datayý alacak
'Timer2.Interval = 2000 ' timer2 nin interval deðeri 2sn de bir text kutusunu silmesi için
'Text32.Text = Chr$(220)
baktime = 0
' Dim aktar As String




startpos = 1
Timer2.Enabled = True


End Sub



Private Sub nameyaz_Click()
Text2.Text = "LCDWR 2,1-" + Tsongname
lensay = Len(Text2.Text) - 10
aktargonder.Text = Text2.Text
'GoTo bakdene
For tt = 1 To lensay - 15
Text2.Text = "LCDWR 1,1-" + Mid$(Tsongname, tt, 16) + " "
bekle:
If READY.Text = "0" Then Call Timer1_Timer: GoTo bekle
'While READY.Text = 0
'Wend
Pause 1
Call Command1_Click
Call Timer1_Timer

Next tt
'bakdene:
For tt = lensay - 15 To 1 Step -1
Text2.Text = "LCDWR 1,1-" + Mid$(Tsongname, tt, 16) + " "
bekle2:
If READY.Text = "0" Then Call Timer1_Timer: GoTo bekle2
'While READY.Text = 0
'Wend
Pause 1
Call Command1_Click
Call Timer1_Timer

Next tt



'Text: Text2.Text = Left$(Text2.Text, 35)
'Call Command1_Click
End Sub

Private Sub openport_Click()

If PORT.Text = "No" Then
DURUM.Text = " Port Numarasý Boþ Olamaz "
         DURUM.BackColor = vbRed
         GoTo son
End If
Pause 0.05
On Error Resume Next
MSComm1.CommPort = PORT.Text
'Text2.Text = Combo2.ListIndex
If Combo2.Text = "None" Then parite = "N"
If Combo2.Text = "Odd" Then parite = "O"
If Combo2.Text = "Even" Then parite = "E"
If Combo2.Text = "Mark" Then parite = "M"
If Combo2.Text = "Space" Then parite = "S"

setting = Combo1.Text & "," & parite & "," & datasec.Text & "," & Combo3.Text
MSComm1.Settings = setting

MSComm1.PortOpen = True
If Err = 8005 Then
         MSComm1.PortOpen = False
         DURUM.Text = " Port Kullanýmda Öncelikle yeni port seçip PORT açýn. " & " Sizin için tüm Portlarý kapattýk " & vbCrLf
         DURUM.BackColor = vbRed
         
      '   Text3.Text = Err
         PORTLABEL.BackColor = vbYellow
         Error.Clear
         
         'list1.AddItem "Port " & i & InUseMsg
         'PortInUse% = PortInUse% + 1
      End If
           If Err = 8002 Then
           MSComm1.PortOpen = False
           PORTLABEL.BackColor = vbYellow
      DURUM.Text = "port " & PORT.Text & " yok" & Err & vbCrLf
  
  '       Text3.Text = Err
      Error.Clear
      
      'list1.AddItem "Port " & i & NoExistMsg
      End If
      
            
      If Err = 8012 Then
      
      DURUM.BackColor = vbGreen: DURUM.Text = " Kapatýlan portu tekrar kapattýnýz: " & Err & " öncelikle PORT seçin sonra PORT açýn" & vbCrLf
            
            MSComm1.PortOpen = False
            PORTLABEL.BackColor = vbYellow
        
    '     Text3.Text = Err
         
         Error.Clear
         
      End If
      If MSComm1.PortOpen = True Then
          DURUM.BackColor = vbGreen
          DURUM.Text = "PORT:  " & PORT.Text & " AÇILDI   " & vbCrLf
          PORTLABEL.BackColor = vbGreen
          Timer1.Enabled = True
            'Timer2.Enabled = True
          
      End If
son:

End Sub



Private Sub temiz_Click()
Text2.Text = "LCDDD"
Call Command1_Click
End Sub

Private Sub Timer1_Timer()
gelen = MSComm1.Input 'pic tarafýndan yollanan datayý texte almak için
If gelen = "" Then GoTo atla
If gelen = 13 Then Text1.Text = Text1.Text & vbCrLf: GoTo atla
If gelen = 10 Then Text1.Text = Text1.Text & vbCrLf: GoTo atla


Text1.Text = Text1.Text & gelen
'If Text1.Text = "LCD R" Then READY.Text = 1 ':text1.Text=""
bak = 0: bak = InStr(1, Text1.Text, "R")
If bak > 0 Then READY.Text = 1: READY.Refresh
If Text1.Text = "LCD P" Then READY.Text = 2 ':text1.Text=""
If Text1.Text = "LCD H" Then READY.Text = 3 ':text1.Text=""
READY.Refresh

atla:
End Sub


Private Sub Pause(ByVal Delay As Single)   'Pause Sub Cred: 'Mark' a1vbcode.com
    'Dim X As Currency
    
    X = Timer: Text3.Text = Timer ' Add a delay to the current time
'    Do While X > Timer  ' and waits for the current time
'        Text3.Text = Timer
'        DoEvents                       ' to catch up.
'    Loop                               ' Pause & Delay can be any name, but
If Check1.Value = 1 Then GoTo atla

bekle:
If Check1.Value = 1 Then GoTo atla
  If Timer - X > Delay Then Text3.Text = Timer + X: Text2.Refresh Else Text3.Text = Timer - X: Text3.Refresh: GoTo bekle
'  Text4.Text = Timer
atla:
End Sub

Private Sub Timer2_Timer()
If startpos = 1 Then startpos = 2: Call Command4_Click: Call Command4_Click: Call Command3_Click

If IsPlaying = 0 Then winampstatus.Text = "STOP"                  ' text15 3 aþamalý kontrol
If IsPlaying = 1 Then winampstatus.Text = "PLAY"
If IsPlaying = 3 Then winampstatus.Text = "PAUSE"
cur_song_position.Text = GetCurrentSongPosition
If Val(cur_song_position.Text) > 0 And Val(songlength_orj.Text) > 0 Then song_pos.Text = "% " + LTrim$(Str$(Int(((Val(cur_song_position.Text) / 1000) / Val(songlength_orj.Text)) * 100))) '+ "  /  100"
If winampstatus.Text = "PLAY" And Val(cur_song_position.Text) < 50 Then Call Command4_Click: Call Command3_Click







End Sub

Private Sub titleyaz_Click()
Text2.Text = "LCDWR 2,1-" + Tsongtitle.Text: Text2.Text = Left$(Text2.Text, 35)
Call Command1_Click
End Sub
