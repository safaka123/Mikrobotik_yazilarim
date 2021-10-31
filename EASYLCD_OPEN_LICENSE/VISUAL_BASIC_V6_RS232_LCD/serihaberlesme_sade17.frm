VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form SERIAL_LCD_CONTROL 
   Caption         =   "SERIAL_LCD_CONTROL"
   ClientHeight    =   11115
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   18420
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   162
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "serihaberlesme_sade17.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   11115
   ScaleWidth      =   18420
   StartUpPosition =   2  'CenterScreen
   Begin VB.OptionButton Option3 
      Caption         =   "Option3"
      Height          =   240
      Left            =   3420
      TabIndex        =   113
      Top             =   6030
      Width           =   195
   End
   Begin VB.OptionButton Option2 
      Caption         =   "Option2"
      Height          =   240
      Left            =   2835
      TabIndex        =   112
      Top             =   6030
      Width           =   195
   End
   Begin VB.OptionButton Option1 
      Caption         =   "Option1"
      Height          =   240
      Left            =   2160
      TabIndex        =   111
      Top             =   6030
      Value           =   -1  'True
      Width           =   240
   End
   Begin VB.TextBox Text19 
      Height          =   420
      Left            =   0
      TabIndex        =   110
      Top             =   10575
      Visible         =   0   'False
      Width           =   1140
   End
   Begin VB.CommandButton Command9 
      Caption         =   "CONVERT ADD"
      Height          =   645
      Left            =   540
      TabIndex        =   109
      Top             =   5985
      Width           =   1050
   End
   Begin VB.TextBox Text18 
      Height          =   375
      Left            =   495
      TabIndex        =   107
      ToolTipText     =   "CHARACTER OR NUMBER"
      Top             =   5490
      Width           =   3435
   End
   Begin VB.PictureBox Picture42 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2220
      Left            =   13950
      Picture         =   "serihaberlesme_sade17.frx":164A
      ScaleHeight     =   2160
      ScaleWidth      =   4095
      TabIndex        =   105
      Top             =   4320
      Width           =   4155
   End
   Begin VB.ListBox List2 
      BackColor       =   &H0000FFFF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2940
      Left            =   10800
      OLEDropMode     =   1  'Manual
      TabIndex        =   104
      ToolTipText     =   "Double Click =  write the command, to send box."
      Top             =   6705
      Width           =   7350
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
      Left            =   1800
      TabIndex        =   103
      Text            =   "0"
      Top             =   11025
      Visible         =   0   'False
      Width           =   420
   End
   Begin VB.Timer Timer4 
      Interval        =   1500
      Left            =   1125
      Top             =   10980
   End
   Begin VB.CommandButton EPROMRECORD 
      Caption         =   "All EXT. CHAR EEPROM Record"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   600
      Left            =   3330
      TabIndex        =   102
      ToolTipText     =   "ALL NEW CHAR. SEND TO MODULE"
      Top             =   4140
      Width           =   1680
   End
   Begin VB.TextBox Text17 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   690
      Left            =   14355
      MultiLine       =   -1  'True
      TabIndex        =   101
      Top             =   2700
      Width           =   2580
   End
   Begin VB.CommandButton Command8 
      BackColor       =   &H0000FF00&
      Caption         =   "LCD OTHER"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   510
      Left            =   14895
      Style           =   1  'Graphical
      TabIndex        =   99
      Top             =   2115
      Width           =   1635
   End
   Begin VB.CommandButton Command6 
      BackColor       =   &H00FFFF00&
      Caption         =   "LCD 4 X 16"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      Left            =   14895
      Style           =   1  'Graphical
      TabIndex        =   98
      Top             =   1485
      Width           =   1635
   End
   Begin VB.Timer Timer2 
      Interval        =   1000
      Left            =   4770
      Top             =   10395
   End
   Begin VB.CommandButton ANIMATION 
      BackColor       =   &H000000FF&
      Caption         =   "ANIMATION"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   690
      Left            =   11970
      Style           =   1  'Graphical
      TabIndex        =   97
      Top             =   3510
      Width           =   1410
   End
   Begin VB.TextBox Text16 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   465
      Left            =   6030
      MaxLength       =   1
      TabIndex        =   95
      Text            =   "0"
      Top             =   2565
      Width           =   510
   End
   Begin VB.CommandButton Command7 
      Caption         =   "INSERT EXTRA CHARACTER"
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
      Left            =   3915
      TabIndex        =   94
      ToolTipText     =   "The value below 32 places symbols instead of ascii characters"
      Top             =   2565
      Width           =   1860
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
      Left            =   4365
      TabIndex        =   92
      Text            =   "0"
      Top             =   10575
      Visible         =   0   'False
      Width           =   330
   End
   Begin VB.TextBox Text15 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   11295
      TabIndex        =   91
      Text            =   "DATE"
      Top             =   945
      Width           =   2490
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
      Height          =   555
      Left            =   3195
      TabIndex        =   90
      Text            =   "Text3"
      Top             =   10665
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
      Left            =   6120
      TabIndex        =   89
      Top             =   9810
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.CommandButton Command5 
      Caption         =   "NEW CHAR. ADD"
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
      Left            =   8010
      TabIndex        =   87
      ToolTipText     =   "Add new character char.txt file after character build."
      Top             =   8775
      Width           =   1815
   End
   Begin VB.CommandButton Command4 
      Caption         =   "CHARACTER BUILD"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   645
      Left            =   8100
      TabIndex        =   84
      Top             =   6660
      Width           =   1815
   End
   Begin VB.TextBox Text14 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   465
      Left            =   7785
      TabIndex        =   83
      Top             =   6120
      Width           =   2490
   End
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   4140
      ItemData        =   "serihaberlesme_sade17.frx":33AF
      Left            =   5130
      List            =   "serihaberlesme_sade17.frx":33B1
      TabIndex        =   82
      Top             =   5625
      Width           =   2400
   End
   Begin VB.TextBox Text33 
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
      Height          =   375
      Left            =   5130
      TabIndex        =   81
      Top             =   4455
      Width           =   5685
   End
   Begin VB.CommandButton Command3 
      Caption         =   "ALL CLEAR"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      Left            =   720
      TabIndex        =   80
      Top             =   6930
      Width           =   915
   End
   Begin VB.PictureBox Picture41 
      AutoRedraw      =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FontTransparent =   0   'False
      Height          =   1695
      Left            =   3285
      ScaleHeight     =   1635
      ScaleWidth      =   1095
      TabIndex        =   79
      Top             =   8055
      Width           =   1155
   End
   Begin VB.PictureBox Picture40 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   70
      Top             =   9990
      Width           =   285
   End
   Begin VB.PictureBox Picture39 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   69
      Top             =   9990
      Width           =   285
   End
   Begin VB.PictureBox Picture38 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   68
      Top             =   9990
      Width           =   285
   End
   Begin VB.PictureBox Picture37 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   67
      Top             =   9990
      Width           =   285
   End
   Begin VB.PictureBox Picture36 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   66
      Top             =   9990
      Width           =   285
   End
   Begin VB.PictureBox Picture35 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   65
      Top             =   9675
      Width           =   285
   End
   Begin VB.PictureBox Picture34 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   64
      Top             =   9675
      Width           =   285
   End
   Begin VB.PictureBox Picture33 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   63
      Top             =   9675
      Width           =   285
   End
   Begin VB.PictureBox Picture32 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   62
      Top             =   9675
      Width           =   285
   End
   Begin VB.PictureBox Picture31 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   61
      Top             =   9675
      Width           =   285
   End
   Begin VB.PictureBox Picture30 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   60
      Top             =   9360
      Width           =   285
   End
   Begin VB.PictureBox Picture29 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   59
      Top             =   9360
      Width           =   285
   End
   Begin VB.PictureBox Picture28 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   58
      Top             =   9360
      Width           =   285
   End
   Begin VB.PictureBox Picture27 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   57
      Top             =   9360
      Width           =   285
   End
   Begin VB.PictureBox Picture26 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   56
      Top             =   9360
      Width           =   285
   End
   Begin VB.PictureBox Picture25 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   55
      Top             =   9045
      Width           =   285
   End
   Begin VB.PictureBox Picture24 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   54
      Top             =   9045
      Width           =   285
   End
   Begin VB.PictureBox Picture23 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   53
      Top             =   9045
      Width           =   285
   End
   Begin VB.PictureBox Picture22 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   52
      Top             =   9045
      Width           =   285
   End
   Begin VB.PictureBox Picture21 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   51
      Top             =   9045
      Width           =   285
   End
   Begin VB.PictureBox Picture20 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   50
      Top             =   8730
      Width           =   285
   End
   Begin VB.PictureBox Picture19 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   49
      Top             =   8730
      Width           =   285
   End
   Begin VB.PictureBox Picture18 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   48
      Top             =   8730
      Width           =   285
   End
   Begin VB.PictureBox Picture17 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   47
      Top             =   8730
      Width           =   285
   End
   Begin VB.PictureBox Picture16 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   46
      Top             =   8730
      Width           =   285
   End
   Begin VB.PictureBox Picture15 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   45
      Top             =   8415
      Width           =   285
   End
   Begin VB.PictureBox Picture14 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   44
      Top             =   8415
      Width           =   285
   End
   Begin VB.PictureBox Picture13 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   43
      Top             =   8415
      Width           =   285
   End
   Begin VB.PictureBox Picture12 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   42
      Top             =   8415
      Width           =   285
   End
   Begin VB.PictureBox Picture11 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   41
      Top             =   8415
      Width           =   285
   End
   Begin VB.PictureBox Picture10 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   40
      Top             =   8100
      Width           =   285
   End
   Begin VB.PictureBox Picture9 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   39
      Top             =   8100
      Width           =   285
   End
   Begin VB.PictureBox Picture8 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   38
      Top             =   8100
      Width           =   285
   End
   Begin VB.PictureBox Picture7 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   37
      Top             =   8100
      Width           =   285
   End
   Begin VB.PictureBox Picture6 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   36
      Top             =   8100
      Width           =   285
   End
   Begin VB.PictureBox Picture5 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2115
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   35
      Top             =   7785
      Width           =   285
   End
   Begin VB.PictureBox Picture4 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1800
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   34
      Top             =   7785
      Width           =   285
   End
   Begin VB.PictureBox Picture3 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1485
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   33
      Top             =   7785
      Width           =   285
   End
   Begin VB.PictureBox Picture2 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   1170
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   32
      Top             =   7785
      Width           =   285
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H0080FFFF&
      FillColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   855
      ScaleHeight     =   255
      ScaleWidth      =   255
      TabIndex        =   31
      Top             =   7785
      Width           =   285
   End
   Begin VB.TextBox Text32 
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
      Height          =   375
      Left            =   5130
      TabIndex        =   30
      Top             =   3960
      Width           =   5700
   End
   Begin VB.Timer Timer3 
      Interval        =   1000
      Left            =   6810
      Top             =   10455
   End
   Begin VB.CommandButton TIMESEND 
      BackColor       =   &H000000FF&
      Caption         =   "TIME_SEND"
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   11970
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   2520
      Width           =   1335
   End
   Begin VB.TextBox Text13 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   10170
      TabIndex        =   27
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text12 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   9435
      TabIndex        =   26
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text11 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   8715
      TabIndex        =   25
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text10 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   7995
      TabIndex        =   24
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text9 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   7275
      TabIndex        =   23
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text8 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   6570
      TabIndex        =   22
      Text            =   "0"
      Top             =   3375
      Width           =   615
   End
   Begin VB.TextBox Text7 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   5835
      TabIndex        =   21
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text6 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   5115
      TabIndex        =   20
      Text            =   "0"
      Top             =   3405
      Width           =   615
   End
   Begin VB.TextBox Text5 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   11280
      TabIndex        =   18
      Text            =   "TIME"
      Top             =   1455
      Width           =   2535
   End
   Begin VB.TextBox Text4 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   162
         Weight          =   900
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   11565
      TabIndex        =   17
      Text            =   "TIME STOP"
      Top             =   2055
      Width           =   2055
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
      Text            =   "serihaberlesme_sade17.frx":33B3
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
      ItemData        =   "serihaberlesme_sade17.frx":33BF
      Left            =   480
      List            =   "serihaberlesme_sade17.frx":33C9
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
      ItemData        =   "serihaberlesme_sade17.frx":33D3
      Left            =   360
      List            =   "serihaberlesme_sade17.frx":33D5
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
      Text            =   "serihaberlesme_sade17.frx":33D7
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
      ItemData        =   "serihaberlesme_sade17.frx":33E3
      Left            =   1800
      List            =   "serihaberlesme_sade17.frx":33ED
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
      ItemData        =   "serihaberlesme_sade17.frx":33F7
      Left            =   1680
      List            =   "serihaberlesme_sade17.frx":340A
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
      ItemData        =   "serihaberlesme_sade17.frx":342C
      Left            =   360
      List            =   "serihaberlesme_sade17.frx":344E
      TabIndex        =   4
      Text            =   "9600"
      Top             =   2040
      Width           =   975
   End
   Begin VB.Timer Timer1 
      Interval        =   10
      Left            =   6210
      Top             =   10455
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   5490
      Top             =   10335
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
      Text            =   "serihaberlesme_sade17.frx":3494
      Top             =   960
      Width           =   7455
   End
   Begin VB.Shape Shape3 
      BorderWidth     =   2
      FillColor       =   &H00C0FFFF&
      Height          =   2085
      Left            =   90
      Shape           =   4  'Rounded Rectangle
      Top             =   4815
      Width           =   4200
   End
   Begin VB.Label Label23 
      Caption         =   "BIN"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   3375
      TabIndex        =   116
      Top             =   6435
      Width           =   420
   End
   Begin VB.Label Label22 
      Caption         =   "DEC"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   2700
      TabIndex        =   115
      Top             =   6435
      Width           =   465
   End
   Begin VB.Label Label21 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   1980
      TabIndex        =   114
      Top             =   6435
      Width           =   555
   End
   Begin VB.Label Label20 
      Alignment       =   2  'Center
      Caption         =   "CHARACTER CONVERT"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   540
      TabIndex        =   108
      Top             =   5130
      Width           =   3345
   End
   Begin VB.Label Label19 
      Alignment       =   2  'Center
      BackColor       =   &H0000FF00&
      Caption         =   "COMMANDS"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   10800
      TabIndex        =   106
      Top             =   6345
      Width           =   2310
   End
   Begin VB.Label Label18 
      Alignment       =   2  'Center
      BackColor       =   &H0000FFFF&
      Caption         =   "LCD SELECT"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   14760
      TabIndex        =   100
      Top             =   990
      Width           =   1905
   End
   Begin VB.Label Label17 
      Alignment       =   2  'Center
      Caption         =   "EXTRA CHARACTERS <==NUMBER ( 0-7 )"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   510
      Left            =   6660
      TabIndex        =   96
      ToolTipText     =   "Please insert 0-7 numbers for the new char.on lcd"
      Top             =   2565
      Width           =   3030
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
      TabIndex        =   93
      Top             =   11160
      Visible         =   0   'False
      Width           =   1185
   End
   Begin VB.Label Label1 
      Caption         =   "New Character Create then Press Button  for the add character to character file."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   690
      Left            =   7920
      TabIndex        =   88
      Top             =   7965
      Width           =   2040
   End
   Begin VB.Label Label16 
      Alignment       =   2  'Center
      Caption         =   "SELECTED CHARACTER CODE (DECIMAL)"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   7830
      TabIndex        =   86
      Top             =   5715
      Width           =   2490
   End
   Begin VB.Label Label15 
      Alignment       =   2  'Center
      Caption         =   "CREATED CHARACTER CODES  FOR EEPROM 00 TO 23 BETWEEN"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   600
      Left            =   5175
      TabIndex        =   85
      Top             =   4995
      Width           =   5595
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      Height          =   705
      Left            =   2565
      OLEDropMode     =   1  'Manual
      Stretch         =   -1  'True
      Top             =   10665
      Visible         =   0   'False
      Width           =   525
   End
   Begin VB.Label Label10 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   78
      Top             =   8730
      Width           =   285
   End
   Begin VB.Label Label14 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   77
      Top             =   9990
      Width           =   285
   End
   Begin VB.Label Label13 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   76
      Top             =   9675
      Width           =   285
   End
   Begin VB.Label Label12 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   75
      Top             =   9360
      Width           =   285
   End
   Begin VB.Label Label11 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   74
      Top             =   9045
      Width           =   285
   End
   Begin VB.Label Label9 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   73
      Top             =   8415
      Width           =   285
   End
   Begin VB.Label Label8 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   72
      Top             =   8100
      Width           =   285
   End
   Begin VB.Label Label7 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H0000FF00&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   285
      Left            =   2610
      TabIndex        =   71
      Top             =   7785
      Width           =   285
   End
   Begin VB.Label Label6 
      Alignment       =   2  'Center
      Caption         =   "HEX VALUE for EEPROM and NEW CHARACTER"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   162
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   3195
      TabIndex        =   29
      Top             =   3285
      Width           =   1815
   End
   Begin VB.Label TITLE 
      Alignment       =   2  'Center
      Caption         =   "EASYLCD CONTROL PROGRAM"
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
      TabIndex        =   19
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
      Caption         =   "PARITY"
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
   Begin VB.Shape Shape2 
      BackStyle       =   1  'Opaque
      BorderColor     =   &H80000001&
      BorderWidth     =   2
      FillColor       =   &H00C0C000&
      FillStyle       =   0  'Solid
      Height          =   2790
      Left            =   720
      Top             =   7650
      Width           =   1815
   End
End
Attribute VB_Name = "SERIAL_LCD_CONTROL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim saylcd(7) As Integer
Dim sayani As Integer
Dim saybak As Integer





Private Sub ANIMATION_Click()
If ANIMATION.BackColor = &HFF00& Then ANIMATION.BackColor = &HFF&: Timer2.Enabled = False: GoTo atla
If ANIMATION.BackColor = &HFF& Then ANIMATION.BackColor = &HFF00&: Text2.Text = "LCDDD": Call Command1_Click: Timer2.Enabled = True
sayani = 0




atla:

End Sub



Private Sub closeport_Click()
Timer1.Enabled = False
'Timer2.Enabled = False
On Error Resume Next
DURUM.BackColor = vbGreen
DURUM.Text = " PORT CLOSED"
'MSComm1.CommPort = PORT.Text
MSComm1.PortOpen = False
PORTLABEL.BackColor = vbYellow '
'Text3.Text = Err
If Err = 8005 Then
DURUM.BackColor = vbRed
PORTLABEL.BackColor = vbRed
DURUM.Text = " Please close port" & Err & vbCrLf
End If

If Err = 8012 Then
DURUM.BackColor = vbRed
PORTLABEL.BackColor = vbYellow
DURUM.Text = " Port already closed, " & Err & " Please select Port and open it." & vbCrLf
          
End If

End Sub





Private Sub Command1_Click()
ReDim kont(54)
On Error Resume Next

'************************************************************
'    hserout ["LCDWR 2,1-","HEX ",hex2 65," DEC ",dec2 65,"(A)"]
'****************************************************************




Dim komut As String

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
         DURUM.Text = DURUM.Text & "PORT IS CLOSED." & Err & vbCrLf
         DURUM.BackColor = vbRed
         Error.Clear
End If
End Sub

Private Sub Command2_Click()
DURUM.Text = "PORT SCANNING" & vbCrLf & "Com-1 , Com-20 between"
DURUM.BackColor = vbYellow

Pause 0.05


On Error Resume Next

   For i = 1 To 20
         DURUM.Text = DURUM.Text & "PORT" & i & " Scanning" & Err & vbCrLf
'         Text3.Text = Err
         MSComm1.CommPort = i
         MSComm1.PortOpen = True
      If Err = 8005 Then
         MSComm1.PortOpen = False
         PORTLABEL.BackColor = vbYellow
         DURUM.Text = DURUM.Text & "PORT " & i & " in Use" & Err & vbCrLf
         DURUM.BackColor = vbRed
         Error.Clear
         
         'list1.AddItem "Port " & i & InUseMsg
         'PortInUse% = PortInUse% + 1
      End If
           If Err = 8002 Then
      DURUM.Text = DURUM.Text & "PORT" & i & " No Exist" & Err & vbCrLf
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
          DURUM.Text = DURUM.Text & "Port" & i & " Opened" & vbCrLf
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
Dim dene As Control
A = 50: B = 50: C = 250: D = 250
dongu:
For tt = 1 To 40
If tt = 1 Then B = 50:   D = 250
If tt = 6 Then B = 250: D = 450
If tt = 11 Then B = 450: D = 650
If tt = 16 Then B = 650: D = 850
If tt = 21 Then B = 850: D = 1050
If tt = 26 Then B = 1050: D = 1250
If tt = 31 Then B = 1250: D = 1450
If tt = 36 Then B = 1450: D = 1650


Picture41.FillStyle = vbSolid
Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Next tt

A = A + 200: C = C + 200
If A > 850 Then Else GoTo dongu
For tt = 0 To 7
saylcd(tt) = 0
Next tt
Label7.Caption = 0
Label8.Caption = 0
Label9.Caption = 0
Label10.Caption = 0
Label11.Caption = 0
Label12.Caption = 0
Label13.Caption = 0
Label14.Caption = 0

Picture1.BackColor = &H80FFFF
Picture2.BackColor = &H80FFFF
Picture3.BackColor = &H80FFFF
Picture4.BackColor = &H80FFFF
Picture5.BackColor = &H80FFFF
Picture6.BackColor = &H80FFFF
Picture7.BackColor = &H80FFFF
Picture8.BackColor = &H80FFFF
Picture9.BackColor = &H80FFFF
Picture10.BackColor = &H80FFFF
Picture11.BackColor = &H80FFFF
Picture12.BackColor = &H80FFFF
Picture13.BackColor = &H80FFFF
Picture14.BackColor = &H80FFFF
Picture15.BackColor = &H80FFFF
Picture16.BackColor = &H80FFFF
Picture17.BackColor = &H80FFFF
Picture18.BackColor = &H80FFFF
Picture19.BackColor = &H80FFFF
Picture20.BackColor = &H80FFFF
Picture21.BackColor = &H80FFFF
Picture22.BackColor = &H80FFFF
Picture23.BackColor = &H80FFFF
Picture24.BackColor = &H80FFFF
Picture25.BackColor = &H80FFFF
Picture26.BackColor = &H80FFFF
Picture27.BackColor = &H80FFFF
Picture28.BackColor = &H80FFFF
Picture29.BackColor = &H80FFFF
Picture30.BackColor = &H80FFFF
Picture31.BackColor = &H80FFFF
Picture32.BackColor = &H80FFFF
Picture33.BackColor = &H80FFFF
Picture34.BackColor = &H80FFFF
Picture35.BackColor = &H80FFFF
Picture36.BackColor = &H80FFFF
Picture37.BackColor = &H80FFFF
Picture38.BackColor = &H80FFFF
Picture39.BackColor = &H80FFFF
Picture40.BackColor = &H80FFFF


End Sub

Private Sub Command4_Click()
Dim dec, bin As Integer
Dim out As String
If Text14.Text = "" Then MsgBox ("PLEASE SELECT CHARACTER"): GoTo son
If Text14.Text = "END" Then MsgBox ("PLEASE SELECT CHARACTER"): GoTo son
aktar = Text14.Text: aktlen = Len(aktar):
aktar2 = Mid$(aktar, 3, (aktlen - 2)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label7.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label8.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label9.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label10.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label11.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label12.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
virbak = InStr(1, aktar2, ","): virbak2 = virbak - 1: Label13.Caption = Val(Mid$(aktar2, 1, virbak2)): aktlen = Len(aktar2): aktar2 = Right$(aktar, (aktlen - virbak)): Text14.Text = aktar2
 Label14.Caption = Val(Text14.Text): Text14.Text = ""
 
For tt = 1 To 8
 If tt = 1 Then dec = Val(Label7.Caption)
  If tt = 2 Then dec = Val(Label8.Caption)
   If tt = 3 Then dec = Val(Label9.Caption)
    If tt = 4 Then dec = Val(Label10.Caption)
     If tt = 5 Then dec = Val(Label11.Caption)
      If tt = 6 Then dec = Val(Label12.Caption)
       If tt = 7 Then dec = Val(Label13.Caption)
        If tt = 8 Then dec = Val(Label14.Caption)
 out = ""
 While dec > 0
bin = Fix(dec) Mod 2
dec = Fix(dec) / 2
out = bin & out
Wend
Text14.Text = out: aktlen = Len(Text14.Text)
If aktlen < 5 Then len2 = 5 - aktlen: Text14.Text = String$(len2, "0") + Text14.Text
If aktlen > 5 Then Text14.Text = Right$(Text14.Text, 5)
len1 = Mid$(Text14.Text, 1, 1): len2 = Mid$(Text14.Text, 2, 1): len3 = Mid$(Text14.Text, 3, 1): len4 = Mid$(Text14.Text, 4, 1): len5 = Mid$(Text14.Text, 5, 1)
If tt = 1 Then
            saylcd(0) = 0
            If len1 = 1 Then Call Picture1_Click
            If len2 = 1 Then Call Picture2_Click
            If len3 = 1 Then Call Picture3_Click
            If len4 = 1 Then Call Picture4_Click
            If len5 = 1 Then Call Picture5_Click
           
End If
If tt = 2 Then
            saylcd(1) = 0
            If len1 = 1 Then Call Picture6_Click
            If len2 = 1 Then Call Picture7_Click
            If len3 = 1 Then Call Picture8_Click
            If len4 = 1 Then Call Picture9_Click
            If len5 = 1 Then Call Picture10_Click
            
End If
If tt = 3 Then
            saylcd(2) = 0
            If len1 = 1 Then Call Picture11_Click
            If len2 = 1 Then Call Picture12_Click
            If len3 = 1 Then Call Picture13_Click
            If len4 = 1 Then Call Picture14_Click
            If len5 = 1 Then Call Picture15_Click
            
End If
If tt = 4 Then
            saylcd(3) = 0
            If len1 = 1 Then Call Picture16_Click
            If len2 = 1 Then Call Picture17_Click
            If len3 = 1 Then Call Picture18_Click
            If len4 = 1 Then Call Picture19_Click
            If len5 = 1 Then Call Picture20_Click
            
End If
If tt = 5 Then
            saylcd(4) = 0
            If len1 = 1 Then Call Picture21_Click
            If len2 = 1 Then Call Picture22_Click
            If len3 = 1 Then Call Picture23_Click
            If len4 = 1 Then Call Picture24_Click
            If len5 = 1 Then Call Picture25_Click
End If
If tt = 6 Then
            saylcd(5) = 0
            If len1 = 1 Then Call Picture26_Click
            If len2 = 1 Then Call Picture27_Click
            If len3 = 1 Then Call Picture28_Click
            If len4 = 1 Then Call Picture29_Click
            If len5 = 1 Then Call Picture30_Click
End If
If tt = 7 Then
            saylcd(6) = 0
            If len1 = 1 Then Call Picture31_Click
            If len2 = 1 Then Call Picture32_Click
            If len3 = 1 Then Call Picture33_Click
            If len4 = 1 Then Call Picture34_Click
            If len5 = 1 Then Call Picture35_Click
End If
If tt = 8 Then
            saylcd(7) = 0
            If len1 = 1 Then Call Picture36_Click
            If len2 = 1 Then Call Picture37_Click
            If len3 = 1 Then Call Picture38_Click
            If len4 = 1 Then Call Picture39_Click
            If len5 = 1 Then Call Picture40_Click
End If



Next tt

Text14.Text = ""
son:
End Sub



Private Sub Command5_Click()
If Label7.Caption = 0 And Label8.Caption = 0 And Label9.Caption = 0 And Label10.Caption = 0 And Label11.Caption = 0 And Label12.Caption = 0 And Label13.Caption = 0 And Label14.Caption = 0 Then MsgBox ("PLEASE CREATE CHARACTER"): GoTo son1
CHARX = "X:"
aktar = CHARX + Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption

Open "char.txt" For Output As #1
For tt = 0 To 24
If List1.List(tt) = "END" And tt < 24 Then Print #1, aktar: Print #1, "END": GoTo atla
If List1.List(tt) = "END" And tt = 24 Then Print #1, "END": GoTo atla
'Print #1, aktar
Print #1, List1.List(tt):
Next tt
atla:
Close #1
'List1.AddItem aktar
Open "char.txt" For Input As #1
For tt = 0 To 24
If EOF(1) Then GoTo sonn
Line Input #1, aktar
'List1.AddItem List1.List(tt) =
List1.List(tt) = aktar
Next tt

sonn:
Close #1:


son1:
End Sub





Private Sub Command6_Click()
If MSComm1.PortOpen = True Then MSComm1.Output = "LCDLS 0"
Text17.Text = " RESTART THE LCD " + " LCD TYPE 4 X 16": Text17.BackColor = &HFF&
End Sub

Private Sub Command7_Click()
BUL = (Asc(Text16.Text) - 48) + 20
Text2.Text = Text2.Text + Chr$(BUL)
End Sub

Private Sub Command8_Click()
If MSComm1.PortOpen = True Then MSComm1.Output = "LCDLS 1"
Text17.Text = " LCD NEED POWER OFF " + " LCD TYPE OTHER": Text17.BackColor = &HFF&

End Sub




Private Sub Command9_Click()
If Option1.Value = True Then Text2.Text = Text2.Text + Hex$(Val(Text18.Text))
If Option2.Value = True Then Text2.Text = Text2.Text + LTrim$(Str$(Asc(Text18.Text)))
If Option3.Value = True Then
  Call DecToBin(Val(Text18.Text))

Text2.Text = Text2.Text + Text19.Text

End If
' buraya gönderilmek istenen DEC HEX ve BIN sayýlarýný ekle

'Text2.Text = Text2.Text + Val(Text18.Text)

End Sub

Public Function DecToBin(DeciValue As Long, Optional NoOfBits As Integer = 8) _
As String
'********************************************************************************
'* Name : DecToBin
'* Date : 2003
'* Author : Alex Etchells
'*********************************************************************************
  Dim i As Integer
  'make sure there are enough bits to contain the number
  Do While DeciValue > (2 ^ NoOfBits) - 1
    NoOfBits = NoOfBits + 8
  Loop
  DecToBin = vbNullString
  'build the string
  For i = 0 To (NoOfBits - 1)
      DecToBin = CStr((DeciValue And 2 ^ i) / 2 ^ i) & DecToBin
  Next i
  Text19.Text = DecToBin
End Function




Private Sub EPROMRECORD_Click()
Timer4.Enabled = True
saybak = 0




End Sub

Private Sub Form_Load()
Timer1.Enabled = False
Timer2.Enabled = False
Timer3.Enabled = False
Timer4.Enabled = False
Combo1.ListIndex = 5
Combo2.ListIndex = 0
Combo3.ListIndex = 0
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
' ****************    karakter dosyasýný oku ve listbox yaz. ****************************************

List1.Clear

Open "char.txt" For Input As #1
For tt = 0 To 24
If EOF(1) Then GoTo sonn
Line Input #1, aktar
List1.AddItem aktar

Next tt

sonn:
Close #1:

Open "command.txt" For Input As #1
For tt = 0 To 100
If EOF(1) Then GoTo sonn2
Line Input #1, aktar
List2.AddItem aktar

Next tt

sonn2:
Close #1:




End Sub

Private Sub Image1_Click()
Image1.Picture = Picture41.Image
End Sub










Private Sub Label7_Change()
Text6.Text = Hex$(Label7.Caption): Text33.Text = ""
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
'Text32.Text = LTrim(Str$(CLng("&H" & Text6.Text))) + "," ' + LTrim(Str$(CLng("&H" & Text7.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text8.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text9.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text10.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text11.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text12.Text))) + "," ' +LTrim(Str$(CLng("&H" & Text13.Text)))

End Sub



Private Sub Label8_Change()
Text7.Text = Hex$(Label8.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub
Private Sub Label9_Change()
Text8.Text = Hex$(Label9.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub
Private Sub Label10_Change()
Text9.Text = Hex$(Label10.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub

Private Sub Label11_Change()
Text10.Text = Hex$(Label11.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub
Private Sub Label12_Change()
Text11.Text = Hex$(Label12.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub
Private Sub Label13_Change()
Text12.Text = Hex$(Label13.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub
Private Sub Label14_Change()
Text13.Text = Hex$(Label14.Caption)
Text33.Text = "0x" + Hex$(Label7.Caption) + "," + "0x" + Hex$(Label8.Caption) + "," + "0x" + Hex$(Label9.Caption) + "," + "0x" + Hex$(Label10.Caption) + "," + "0x" + Hex$(Label11.Caption) + "," + "0x" + Hex$(Label12.Caption) + "," + "0x" + Hex$(Label13.Caption) + "," + "0x" + Hex$(Label14.Caption)
Text32.Text = Label7.Caption + "," + Label8.Caption + "," + Label9.Caption + "," + Label10.Caption + "," + Label11.Caption + "," + Label12.Caption + "," + Label13.Caption + "," + Label14.Caption
End Sub



Private Sub List1_Click()
Text14.Text = List1.List(List1.ListIndex)
'ListBox1.List (i)
Call Command3_Click
End Sub




Private Sub List2_Click()
'ekle = List2.List(List2.ListIndex)
'bak = 0: bak = InStr(1, ekle, Chr$(9))
'If bak > 0 And bak > 3 Then Text2.Text = Trim$(Left$(ekle, bak - 1))
End Sub

Private Sub List2_DblClick()
ekle = List2.List(List2.ListIndex)
bak = 0: bak = InStr(1, ekle, Chr$(9))
If bak > 0 And bak > 3 Then Text2.Text = Trim$(Left$(ekle, bak - 1))
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
Text2.Text = Combo2.ListIndex
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
         DURUM.Text = " Port already OPEN, " & " We've shut down all ports for you" & vbCrLf
       '  Port already closed, " & Err & " Please select Port and open it.
         DURUM.BackColor = vbRed
         
      '   Text3.Text = Err
         PORTLABEL.BackColor = vbYellow
         Error.Clear
         Timer1.Enabled = False
         GoTo son
         'list1.AddItem "Port " & i & InUseMsg
         'PortInUse% = PortInUse% + 1
      End If
      
   

      
      
      
           If Err = 8002 Then
           MSComm1.PortOpen = False
           PORTLABEL.BackColor = vbYellow
      DURUM.Text = "port " & PORT.Text & "No Exist" & Err & vbCrLf
  
  '       Text3.Text = Err
      Error.Clear
      Timer1.Enabled = False
      GoTo son
      'list1.AddItem "Port " & i & NoExistMsg
      End If
      
            
      If Err = 8012 Then
      
      DURUM.BackColor = vbGreen: DURUM.Text = " Kapatýlan portu tekrar kapattýnýz: " & Err & " öncelikle PORT seçin sonra PORT açýn" & vbCrLf
            
            MSComm1.PortOpen = False
            PORTLABEL.BackColor = vbYellow
        
    '     Text3.Text = Err
         
         Error.Clear
         Timer1.Enabled = False
         GoTo son
         
      End If
    
         If Err = 8018 Then
         MSComm1.PortOpen = False
         DURUM.Text = " Port already OPEN,Please Close port and try again " & " We've shut down all ports for you" & vbCrLf
       '  Port already closed, " & Err & " Please select Port and open it.
         DURUM.BackColor = vbRed
         
      '   Text3.Text = Err
         PORTLABEL.BackColor = vbYellow
         Error.Clear
         Timer1.Enabled = False
         GoTo son
         'list1.AddItem "Port " & i & InUseMsg
         'PortInUse% = PortInUse% + 1
      End If
      
      
      
      If MSComm1.PortOpen = True Then
          DURUM.BackColor = vbGreen
          DURUM.Text = "PORT:  " & PORT.Text & " OPENED  " & vbCrLf
          PORTLABEL.BackColor = vbGreen
          Timer1.Enabled = True
            'Timer2.Enabled = True
          
      End If
son:

End Sub

Private Sub Picture1_Click()

A = 50: B = 50: C = 250: D = 250
Picture41.FillStyle = vbSolid

If Picture1.BackColor = &H80FFFF Then Picture1.BackColor = vbRed: saylcd(0) = saylcd(0) + 16: Picture41.FillColor = vbRed Else saylcd(0) = saylcd(0) - 16: Picture1.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label7.Caption = saylcd(0)
End Sub




Private Sub Picture11_Click()
A = 50: B = 450: C = 250: D = 650
Picture41.FillStyle = vbSolid

If Picture11.BackColor = &H80FFFF Then Picture11.BackColor = vbRed: saylcd(2) = saylcd(2) + 16: Picture41.FillColor = vbRed Else saylcd(2) = saylcd(2) - 16: Picture11.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label9.Caption = saylcd(2)
End Sub

Private Sub Picture12_Click()
A = 250: B = 450: C = 450: D = 650
Picture41.FillStyle = vbSolid

If Picture12.BackColor = &H80FFFF Then Picture12.BackColor = vbRed: saylcd(2) = saylcd(2) + 8: Picture41.FillColor = vbRed Else saylcd(2) = saylcd(2) - 8: Picture12.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label9.Caption = saylcd(2)
End Sub

Private Sub Picture13_Click()
A = 450: B = 450: C = 650: D = 650
Picture41.FillStyle = vbSolid

If Picture13.BackColor = &H80FFFF Then Picture13.BackColor = vbRed: saylcd(2) = saylcd(2) + 4: Picture41.FillColor = vbRed Else saylcd(2) = saylcd(2) - 4: Picture13.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label9.Caption = saylcd(2)

End Sub

Private Sub Picture14_Click()
A = 650: B = 450: C = 850: D = 650
Picture41.FillStyle = vbSolid

If Picture14.BackColor = &H80FFFF Then Picture14.BackColor = vbRed: saylcd(2) = saylcd(2) + 2: Picture41.FillColor = vbRed Else saylcd(2) = saylcd(2) - 2: Picture14.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label9.Caption = saylcd(2)

End Sub

Private Sub Picture15_Click()
A = 850: B = 450: C = 1050: D = 650
Picture41.FillStyle = vbSolid

If Picture15.BackColor = &H80FFFF Then Picture15.BackColor = vbRed: saylcd(2) = saylcd(2) + 1: Picture41.FillColor = vbRed Else saylcd(2) = saylcd(2) - 1: Picture15.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label9.Caption = saylcd(2)

End Sub

Private Sub Picture16_Click()
A = 50: B = 650: C = 250: D = 850
Picture41.FillStyle = vbSolid

If Picture16.BackColor = &H80FFFF Then Picture16.BackColor = vbRed: saylcd(3) = saylcd(3) + 16: Picture41.FillColor = vbRed Else saylcd(3) = saylcd(3) - 16: Picture16.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label10.Caption = saylcd(3)
End Sub

Private Sub Picture17_Click()
A = 250: B = 650: C = 450: D = 850
Picture41.FillStyle = vbSolid

If Picture17.BackColor = &H80FFFF Then Picture17.BackColor = vbRed: saylcd(3) = saylcd(3) + 8: Picture41.FillColor = vbRed Else saylcd(3) = saylcd(3) - 8: Picture17.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label10.Caption = saylcd(3)

End Sub

Private Sub Picture18_Click()
A = 450: B = 650: C = 650: D = 850
Picture41.FillStyle = vbSolid

If Picture18.BackColor = &H80FFFF Then Picture18.BackColor = vbRed: saylcd(3) = saylcd(3) + 4: Picture41.FillColor = vbRed Else saylcd(3) = saylcd(3) - 4: Picture18.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label10.Caption = saylcd(3)

End Sub

Private Sub Picture19_Click()
A = 650: B = 650: C = 850: D = 850
Picture41.FillStyle = vbSolid

If Picture19.BackColor = &H80FFFF Then Picture19.BackColor = vbRed: saylcd(3) = saylcd(3) + 2: Picture41.FillColor = vbRed Else saylcd(3) = saylcd(3) - 2: Picture19.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label10.Caption = saylcd(3)

End Sub
Private Sub Picture20_Click()
A = 850: B = 650: C = 1050: D = 850
Picture41.FillStyle = vbSolid

If Picture20.BackColor = &H80FFFF Then Picture20.BackColor = vbRed: saylcd(3) = saylcd(3) + 1: Picture41.FillColor = vbRed Else saylcd(3) = saylcd(3) - 1: Picture20.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label10.Caption = saylcd(3)

End Sub


Private Sub Picture2_Click()
A = 250: B = 50: C = 450: D = 250
Picture41.FillStyle = vbSolid

If Picture2.BackColor = &H80FFFF Then Picture2.BackColor = vbRed: saylcd(0) = saylcd(0) + 8: Picture41.FillColor = vbRed Else saylcd(0) = saylcd(0) - 8: Picture2.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label7.Caption = saylcd(0)
End Sub



Private Sub Picture21_Click()
A = 50: B = 850: C = 250: D = 1050
Picture41.FillStyle = vbSolid

If Picture21.BackColor = &H80FFFF Then Picture21.BackColor = vbRed: saylcd(4) = saylcd(4) + 16: Picture41.FillColor = vbRed Else saylcd(4) = saylcd(4) - 16: Picture21.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label11.Caption = saylcd(4)

End Sub

Private Sub Picture22_Click()
A = 250: B = 850: C = 450: D = 1050
Picture41.FillStyle = vbSolid

If Picture22.BackColor = &H80FFFF Then Picture22.BackColor = vbRed: saylcd(4) = saylcd(4) + 8: Picture41.FillColor = vbRed Else saylcd(4) = saylcd(4) - 8: Picture22.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label11.Caption = saylcd(4)

End Sub

Private Sub Picture23_Click()
A = 450: B = 850: C = 650: D = 1050
Picture41.FillStyle = vbSolid

If Picture23.BackColor = &H80FFFF Then Picture23.BackColor = vbRed: saylcd(4) = saylcd(4) + 4: Picture41.FillColor = vbRed Else saylcd(4) = saylcd(4) - 4: Picture23.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label11.Caption = saylcd(4)

End Sub

Private Sub Picture24_Click()
A = 650: B = 850: C = 850: D = 1050
Picture41.FillStyle = vbSolid

If Picture24.BackColor = &H80FFFF Then Picture24.BackColor = vbRed: saylcd(4) = saylcd(4) + 2: Picture41.FillColor = vbRed Else saylcd(4) = saylcd(4) - 2: Picture24.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label11.Caption = saylcd(4)
End Sub

Private Sub Picture25_Click()
A = 850: B = 850: C = 1050: D = 1050
Picture41.FillStyle = vbSolid

If Picture25.BackColor = &H80FFFF Then Picture25.BackColor = vbRed: saylcd(4) = saylcd(4) + 1: Picture41.FillColor = vbRed Else saylcd(4) = saylcd(4) - 1: Picture25.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label11.Caption = saylcd(4)
End Sub

Private Sub Picture26_Click()
A = 50: B = 1050: C = 250: D = 1250
Picture41.FillStyle = vbSolid

If Picture26.BackColor = &H80FFFF Then Picture26.BackColor = vbRed: saylcd(5) = saylcd(5) + 16: Picture41.FillColor = vbRed Else saylcd(5) = saylcd(5) - 16: Picture26.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label12.Caption = saylcd(5)
End Sub

Private Sub Picture27_Click()
A = 250: B = 1050: C = 450: D = 1250
Picture41.FillStyle = vbSolid

If Picture27.BackColor = &H80FFFF Then Picture27.BackColor = vbRed: saylcd(5) = saylcd(5) + 8: Picture41.FillColor = vbRed Else saylcd(5) = saylcd(5) - 8: Picture27.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label12.Caption = saylcd(5)

End Sub

Private Sub Picture28_Click()
A = 450: B = 1050: C = 650: D = 1250
Picture41.FillStyle = vbSolid

If Picture28.BackColor = &H80FFFF Then Picture28.BackColor = vbRed: saylcd(5) = saylcd(5) + 4: Picture41.FillColor = vbRed Else saylcd(5) = saylcd(5) - 4: Picture28.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label12.Caption = saylcd(5)

End Sub

Private Sub Picture29_Click()
A = 650: B = 1050: C = 850: D = 1250
Picture41.FillStyle = vbSolid

If Picture29.BackColor = &H80FFFF Then Picture29.BackColor = vbRed: saylcd(5) = saylcd(5) + 2: Picture41.FillColor = vbRed Else saylcd(5) = saylcd(5) - 2: Picture29.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label12.Caption = saylcd(5)

End Sub
Private Sub Picture30_Click()
A = 850: B = 1050: C = 1050: D = 1250
Picture41.FillStyle = vbSolid

If Picture30.BackColor = &H80FFFF Then Picture30.BackColor = vbRed: saylcd(5) = saylcd(5) + 1: Picture41.FillColor = vbRed Else saylcd(5) = saylcd(5) - 1: Picture30.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label12.Caption = saylcd(5)

End Sub

Private Sub Picture3_Click()
A = 450: B = 50: C = 650: D = 250
Picture41.FillStyle = vbSolid

If Picture3.BackColor = &H80FFFF Then Picture3.BackColor = vbRed: saylcd(0) = saylcd(0) + 4: Picture41.FillColor = vbRed Else saylcd(0) = saylcd(0) - 4: Picture3.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label7.Caption = saylcd(0)
End Sub
Private Sub Picture31_Click()
A = 50: B = 1250: C = 250: D = 1450
Picture41.FillStyle = vbSolid

If Picture31.BackColor = &H80FFFF Then Picture31.BackColor = vbRed: saylcd(6) = saylcd(6) + 16: Picture41.FillColor = vbRed Else saylcd(6) = saylcd(6) - 16: Picture31.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label13.Caption = saylcd(6)

End Sub

Private Sub Picture32_Click()
A = 250: B = 1250: C = 450: D = 1450
Picture41.FillStyle = vbSolid

If Picture32.BackColor = &H80FFFF Then Picture32.BackColor = vbRed: saylcd(6) = saylcd(6) + 8: Picture41.FillColor = vbRed Else saylcd(6) = saylcd(6) - 8: Picture32.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label13.Caption = saylcd(6)
End Sub

Private Sub Picture33_Click()
A = 450: B = 1250: C = 650: D = 1450
Picture41.FillStyle = vbSolid

If Picture33.BackColor = &H80FFFF Then Picture33.BackColor = vbRed: saylcd(6) = saylcd(6) + 4: Picture41.FillColor = vbRed Else saylcd(6) = saylcd(6) - 4: Picture33.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label13.Caption = saylcd(6)
End Sub

Private Sub Picture34_Click()
A = 650: B = 1250: C = 850: D = 1450
Picture41.FillStyle = vbSolid

If Picture34.BackColor = &H80FFFF Then Picture34.BackColor = vbRed: saylcd(6) = saylcd(6) + 2: Picture41.FillColor = vbRed Else saylcd(6) = saylcd(6) - 2: Picture34.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label13.Caption = saylcd(6)

End Sub

Private Sub Picture35_Click()
A = 850: B = 1250: C = 1050: D = 1450
Picture41.FillStyle = vbSolid

If Picture35.BackColor = &H80FFFF Then Picture35.BackColor = vbRed: saylcd(6) = saylcd(6) + 1: Picture41.FillColor = vbRed Else saylcd(6) = saylcd(6) - 1: Picture35.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label13.Caption = saylcd(6)

End Sub

Private Sub Picture36_Click()
A = 50: B = 1450: C = 250: D = 1650
Picture41.FillStyle = vbSolid

If Picture36.BackColor = &H80FFFF Then Picture36.BackColor = vbRed: saylcd(7) = saylcd(7) + 16: Picture41.FillColor = vbRed Else saylcd(7) = saylcd(7) - 16: Picture36.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label14.Caption = saylcd(7)

End Sub

Private Sub Picture37_Click()
A = 250: B = 1450: C = 450: D = 1650
Picture41.FillStyle = vbSolid

If Picture37.BackColor = &H80FFFF Then Picture37.BackColor = vbRed: saylcd(7) = saylcd(7) + 8: Picture41.FillColor = vbRed Else saylcd(7) = saylcd(7) - 8: Picture37.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label14.Caption = saylcd(7)

End Sub

Private Sub Picture38_Click()
A = 450: B = 1450: C = 650: D = 1650
Picture41.FillStyle = vbSolid

If Picture38.BackColor = &H80FFFF Then Picture38.BackColor = vbRed: saylcd(7) = saylcd(7) + 4: Picture41.FillColor = vbRed Else saylcd(7) = saylcd(7) - 4: Picture38.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label14.Caption = saylcd(7)
End Sub

Private Sub Picture39_Click()
A = 650: B = 1450: C = 850: D = 1650
Picture41.FillStyle = vbSolid

If Picture39.BackColor = &H80FFFF Then Picture39.BackColor = vbRed: saylcd(7) = saylcd(7) + 2: Picture41.FillColor = vbRed Else saylcd(7) = saylcd(7) - 2: Picture39.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label14.Caption = saylcd(7)

End Sub

Private Sub Picture4_Click()
A = 650: B = 50: C = 850: D = 250
Picture41.FillStyle = vbSolid

If Picture4.BackColor = &H80FFFF Then Picture4.BackColor = vbRed: saylcd(0) = saylcd(0) + 2: Picture41.FillColor = vbRed Else saylcd(0) = saylcd(0) - 2: Picture4.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label7.Caption = saylcd(0)
End Sub

Private Sub Picture40_Click()
A = 850: B = 1450: C = 1050: D = 1650
Picture41.FillStyle = vbSolid

If Picture40.BackColor = &H80FFFF Then Picture40.BackColor = vbRed: saylcd(7) = saylcd(7) + 1: Picture41.FillColor = vbRed Else saylcd(7) = saylcd(7) - 1: Picture40.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label14.Caption = saylcd(7)
End Sub

Private Sub Picture5_Click()
A = 850: B = 50: C = 1050: D = 250
Picture41.FillStyle = vbSolid

If Picture5.BackColor = &H80FFFF Then Picture5.BackColor = vbRed: saylcd(0) = saylcd(0) + 1: Picture41.FillColor = vbRed Else saylcd(0) = saylcd(0) - 1: Picture5.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label7.Caption = saylcd(0)
End Sub

Private Sub Picture6_Click()
A = 50: B = 250: C = 250: D = 450
Picture41.FillStyle = vbSolid

If Picture6.BackColor = &H80FFFF Then Picture6.BackColor = vbRed: saylcd(1) = saylcd(1) + 16: Picture41.FillColor = vbRed Else saylcd(1) = saylcd(1) - 16: Picture6.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label8.Caption = saylcd(1)
End Sub

Private Sub Picture7_Click()
A = 250: B = 250: C = 450: D = 450
Picture41.FillStyle = vbSolid

If Picture7.BackColor = &H80FFFF Then Picture7.BackColor = vbRed: saylcd(1) = saylcd(1) + 8: Picture41.FillColor = vbRed Else saylcd(1) = saylcd(1) - 8: Picture7.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label8.Caption = saylcd(1)
End Sub

Private Sub Picture8_Click()
A = 450: B = 250: C = 650: D = 450
Picture41.FillStyle = vbSolid

If Picture8.BackColor = &H80FFFF Then Picture8.BackColor = vbRed: saylcd(1) = saylcd(1) + 4: Picture41.FillColor = vbRed Else saylcd(1) = saylcd(1) - 4: Picture8.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label8.Caption = saylcd(1)

End Sub

Private Sub Picture9_Click()
A = 650: B = 250: C = 850: D = 450
Picture41.FillStyle = vbSolid

If Picture9.BackColor = &H80FFFF Then Picture9.BackColor = vbRed: saylcd(1) = saylcd(1) + 2: Picture41.FillColor = vbRed Else saylcd(1) = saylcd(1) - 2: Picture9.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label8.Caption = saylcd(1)

End Sub
Private Sub Picture10_Click()
A = 850: B = 250: C = 1050: D = 450
Picture41.FillStyle = vbSolid

If Picture10.BackColor = &H80FFFF Then Picture10.BackColor = vbRed: saylcd(1) = saylcd(1) + 1: Picture41.FillColor = vbRed Else saylcd(1) = saylcd(1) - 1: Picture10.BackColor = &H80FFFF: Picture41.FillColor = &H8000000F
Picture41.Line (A, B)-(C, D), &H8000000F, B
Label8.Caption = saylcd(1)
End Sub






Private Sub Timer1_Timer()
gelen = MSComm1.Input 'pic tarafýndan yollanan datayý texte almak için
If gelen = "" Then GoTo atla
If gelen = 13 Then Text1.Text = Text1.Text & vbCrLf: GoTo atla
If gelen = 10 Then Text1.Text = Text1.Text & vbCrLf: GoTo atla


Text1.Text = Text1.Text & gelen
'If Text1.Text = "LCD R" Then READY.Text = 1 ':text1.Text=""
bak = 0: bak = InStr(1, Text1.Text, "R")
If bak > 0 Then READY.Text = 1: Text17.BackColor = &HFFFFFF: Text17.Text = ""
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
  If Timer - X > Delay Then Text3.Text = Timer + X: Text2.Refresh: Text5.Refresh Else Text3.Text = Timer - X: Text3.Refresh: GoTo bekle
'  Text4.Text = Timer
atla:
End Sub



Private Sub Timer2_Timer()
Dim den As Integer
Dim aa As Byte
'Text14.Text = "A"

aa = Asc("A") '          ***********************************   aþýk taki kýsmý hex olarak gönder**************************
If MSComm1.PortOpen = True Then Else GoTo atla
      If READY.Text = 1 And sayani = 0 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDD": Call Command1_Click
      If READY.Text = 1 And sayani = 1 Then READY.Text = 0: sayani = sayani + 1: List1.ListIndex = 1: Call List1_Click: Call Command4_Click:: Text2.Text = "LCDNC 3-": Call Command1_Click
      If READY.Text = 1 And sayani = 2 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-AIK": Call Command1_Click
      'If READY.Text = 1 And sayani = 3 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 2,1-HEX ":  MSComm1.Output = Text2.Text + Hex$(Asc("A")) + " DEC" + Str(Asc("A")) + "(A)"
      
      If READY.Text = 1 And sayani = 3 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 2,1-HEX ":  Text2.Text = Text2.Text + Hex$(Asc("A")) + " DEC" + Str(Asc("A")) + "(A)": Call Command1_Click
      If READY.Text = 1 And sayani = 4 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-DISP. WILL CLOSE": Call Command1_Click
      If READY.Text = 1 And sayani = 5 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDC": Call Command1_Click
      If READY.Text = 1 And sayani = 6 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-DISP. OPENED    ": Call Command1_Click
      If READY.Text = 1 And sayani = 7 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDO": Call Command1_Click
      If READY.Text = 1 And sayani = 8 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CUR.UNDER   ": Call Command1_Click
      If READY.Text = 1 And sayani = 9 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCU": Call Command1_Click
      If READY.Text = 1 And sayani = 10 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CUR.HIDDEN  ": Call Command1_Click
      If READY.Text = 1 And sayani = 11 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCH": Call Command1_Click
      If READY.Text = 1 And sayani = 12 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CUR.BOX     ": Call Command1_Click
      If READY.Text = 1 And sayani = 13 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCB": Call Command1_Click
      
      If READY.Text = 1 And sayani = 14 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CUR SHIFT L<=": Call Command1_Click
      If READY.Text = 1 And sayani = 15 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCL": Call Command1_Click
      If READY.Text = 1 And sayani = 16 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCL": Call Command1_Click
      If READY.Text = 1 And sayani = 17 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCL": Call Command1_Click
      If READY.Text = 1 And sayani = 18 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CUR SHIFT R=>": Call Command1_Click
      If READY.Text = 1 And sayani = 19 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCR": Call Command1_Click
      If READY.Text = 1 And sayani = 20 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCR": Call Command1_Click
      If READY.Text = 1 And sayani = 21 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCR": Call Command1_Click
      If READY.Text = 1 And sayani = 22 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-DISP. SHIFT R==>": Call Command1_Click
      If READY.Text = 1 And sayani = 23 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSR": Call Command1_Click
      If READY.Text = 1 And sayani = 24 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSR": Call Command1_Click
      If READY.Text = 1 And sayani = 25 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSR": Call Command1_Click
      If READY.Text = 1 And sayani = 26 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-DISP. SHIFT L<==": Call Command1_Click
      If READY.Text = 1 And sayani = 27 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSL": Call Command1_Click
      If READY.Text = 1 And sayani = 28 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSL": Call Command1_Click
      If READY.Text = 1 And sayani = 29 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSL": Call Command1_Click
      If READY.Text = 1 And sayani = 30 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-CURSOR HOME     ": Call Command1_Click
      If READY.Text = 1 And sayani = 31 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDHO": Call Command1_Click
      If READY.Text = 1 And sayani = 32 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-BACKLIGHT CLOSE ": Call Command1_Click
      If READY.Text = 1 And sayani = 33 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDBC": Call Command1_Click
      If READY.Text = 1 And sayani = 34 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-BACKLIGHT OPEN  ": Call Command1_Click
      If READY.Text = 1 And sayani = 35 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDBO": Call Command1_Click
      If READY.Text = 1 And sayani = 36 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-BACKLIGHT  %10  ": Call Command1_Click
      If READY.Text = 1 And sayani = 37 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDBL 1": Call Command1_Click
      If READY.Text = 1 And sayani = 38 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-BACKLIGHT  %90  ": Call Command1_Click
      If READY.Text = 1 And sayani = 39 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDBL 9": Call Command1_Click
      If READY.Text = 1 And sayani = 40 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-BACKLIGHT  %40  ": Call Command1_Click
      If READY.Text = 1 And sayani = 41 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDBL 4": Call Command1_Click
      If READY.Text = 1 And sayani = 42 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-EEPROM RECORDING": Call Command1_Click
      If READY.Text = 1 And sayani = 43 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 2,1-                ": Call Command1_Click
      If READY.Text = 1 And sayani = 44 Then READY.Text = 0: sayani = sayani + 1: Text1.Text = "": MSComm1.Output = "LCDEW 13-" + Chr$(Val("&H" + "E")) + Chr$(Val("&H" + "0")) + Chr$(Val("&H" + "F")) + Chr$(Val("&H" + "10")) + Chr$(Val("&H" + "13")) + Chr$(Val("&H" + "11")) + Chr$(Val("&H" + "F")) + Chr$(Val("&H" + "0"))
      If READY.Text = 1 And sayani = 45 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDSC 13,3-                ": Call Command1_Click
      If READY.Text = 1 And sayani = 46 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 2,1-AIK": Call Command1_Click
      If READY.Text = 1 And sayani = 47 Then READY.Text = 0: sayani = sayani + 1: Text1.Text = "": MSComm1.Output = "LCDWR 1,1-" + Chr$(Val("&H" + "3")) + "  READ CH. EPROM "
      If READY.Text = 1 And sayani = 48 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDD": Call Command1_Click
      If READY.Text = 1 And sayani = 49 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCB": Call Command1_Click
      If READY.Text = 1 And sayani = 50 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDER": Call Command1_Click
      If READY.Text = 1 And sayani = 51 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDD": Call Command1_Click
      If READY.Text = 1 And sayani = 52 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDCB": Call Command1_Click
      If READY.Text = 1 And sayani = 53 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDDD": Call Command1_Click
      If READY.Text = 1 And sayani = 54 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDWR 1,1-READ   CHARACTER": Call Command1_Click
      If READY.Text = 1 And sayani = 55 Then READY.Text = 0: sayani = sayani + 1: Text2.Text = "LCDRC 1,14-": Call Command1_Click: Text1.Text = ""
If sayani = 56 Then Text1.Text = "LCD R": READY.Text = 1: sayani = sayani + 1
If sayani > 56 Then sayani = sayani + 1

If sayani > 70 Then
Timer2.Enabled = False
Call ANIMATION_Click
Text1.Text = "": READY.Text = 0
Call TIMESEND_Click
End If

atla:

End Sub

Private Sub Timer3_Timer()
Text5.Text = Time:
If MSComm1.PortOpen = True And Text4.Text = "TIME SENDING" And READY.Text = "1" And saybak = 1 Then saybak = 2: READY.Text = 0: Text1.Text = "": MSComm1.Output = "LCDWR 2,4-" + Text15.Text: GoTo son
If MSComm1.PortOpen = True And Text4.Text = "TIME SENDING" And READY.Text = "1" And saybak > 1 Then READY.Text = 0: Text1.Text = "": MSComm1.Output = "LCDWR 1,4-" + Text5.Text

son:

End Sub


Private Sub Timer4_Timer()
sayani = Val(timer4_sayac.Text)
If saybak = 0 And sayani = List1.ListCount Then sayani = 0: saybak = 0: Timer4.Enabled = False: timer4_sayac.Text = 0: GoTo kapat
'If saybak = 1 And (List1.ListCount + sayani) = 25 Then Timer4.Enabled = False: timer4_sayac.Text = 0: GoTo kapat
List1.ListIndex = sayani: Call List1_Click:
ara = 0
ara = InStr(1, Text14.Text, "END")
If ara > 0 Then sayani = 0: saybak = 0: Timer4.Enabled = False: timer4_sayac.Text = 0: GoTo kapat

Call Command4_Click:
If saybak = 0 Then Text2.Text = "LCDEW " + Trim$(Str$(sayani)) + "-": Call Command1_Click
If saybak = 1 Then Text2.Text = "LCDEW " + Trim$(Str$(((List1.ListCount - 1) + sayani))) + "-": Call Command1_Click
sayani = sayani + 1
bekle:
If READY.Text = 1 Then
    Else: GoTo bekle
End If

'If sayani = 5 Then
'timer4_sayac.Text = 0
'Timer4.Enabled = False
'Else
'timer4_sayac.Text = sayani
'End If
timer4_sayac.Text = sayani
kapat:

End Sub

Private Sub TIMESEND_Click()
Pause 1
If MSComm1.PortOpen = True And Text4.Text = "TIME STOP" Then saybak = 1:  Text4.Text = "TIME SENDING": Text15.Text = Date: TIMESEND.BackColor = &HFF00&: READY.Text = 0: Text1.Text = "":  Timer3.Enabled = True Else TIMESEND.BackColor = &HFF&: Text4.Text = "TIME STOP": Timer3.Enabled = False
If MSComm1.PortOpen = True And Text4.Text = "TIME SENDING" Then READY.Text = 0: MSComm1.Output = "LCDDD"


'If MSComm1.PortOpen = True And Text4.Text = "TIME STOP" Then READY.Text = 0: MSComm1.Output = "LCDDD"
'Pause 1
'If MSComm1.PortOpen = True And Text4.Text = "TIME STOP" Then bak = 0:  Text4.Text = "TIME SENDING": Text15.Text = Date: TIMESEND.BackColor = &HFF00&: READY.Text = 0: Text1.Text = "": MSComm1.Output = "LCDWR 2,4-" + Text15.Text: Timer3.Enabled = True Else TIMESEND.BackColor = &HFF&: Text4.Text = "TIME STOP": Timer3.Enabled = False


'Text4.Text = baktime
End Sub

Private Sub VScroll1_Change()
Label1.Caption = VScroll1.Value
Text14.Text = List1.List(VScroll1.Value)
Call Command3_Click
End Sub
