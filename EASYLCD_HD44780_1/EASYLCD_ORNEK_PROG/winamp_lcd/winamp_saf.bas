Attribute VB_Name = "WinAmp_saf"
'WinampMod - winamp.bas
'
'By MidTerror - midterror@hotmail.com
'
'Updated by Thegreatone - scotttasker@gmail.com
'
'Re-Update by TDQWERTY - AlexDias@gmail.com
'(problem opening id3 editor solved, working for
'winamp modern skin, addeded id3v2 tag reading support)
'improvement of ID3v1 and ID3v2 reading/checking
'addeded MPEG info reading, fixed getWinampWindowText bug
'
'Feel free to mail comments, bugs, advice
'I'd appreciate it if you gave me some credit
'If you make a program out of this. If not
'then it's ok, but I wouldn't mind seeing the
'program, so feel free to send me programs you
'make with this.

Option Explicit

'All the Declarations
Private Declare Function PostMessage2 Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long
Private Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Public Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SendMessageS Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As String) As Long
Public Declare Function SendMessageCDS Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As COPYDATASTRUCT) As Long
Public Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function GetWindowText Lib "user32" Alias "GetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String, ByVal cch As Long) As Long

Public Const WM_USER = &H400
Public Const WM_WA_IPC = WM_USER
Public Const WM_COPYDATA = &H4A
Public Const WM_COMMAND = &H111
Public Const WM_CHAR = &H102

Public lHandle As Long

'Registry Info
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Private Const HKEY_CLASSES_ROOT = &H80000000
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Const WINAMP_REG_KEY = "WinAmp.File\shell\play\command"
Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
Private Const KEY_QUERY_VALUE = &H1

Public hwnd_winamp As Long
Public Const WM_GETTEXT = &HD
Public Const vbKeyShift = &H10
Public Const vbKeyCtrl = &H11
Public Const vbKeyAlt = &H12
Public Const IPC_DELETE = 101
Public Const IPC_ISPLAYING = 104
Public Const IPC_GETOUTPUTTIME = 105
Public Const IPC_JUMPTOTIME = 106
Public Const IPC_WRITEPLAYLIST = 120
Public Const IPC_SETPLAYLISTPOS = 121
Public Const IPC_SETVOLUME = 122
Public Const IPC_SETPANNING = 123
Public Const IPC_GETLISTLENGTH = 124
Public Const IPC_SETSKIN = 200
Public Const IPC_GETSKIN = 201
Public Const IPC_GETLISTPOS = 125
Public Const IPC_GETINFO = 126
Public Const IPC_GETEQDATA = 127
Public Const IPC_PLAYFILE = 100
Public Const IPC_CHDIR = 103
Public Const WINAMP_OPTIONS_EQ = 40036
Public Const WINAMP_OPTIONS_PLEDIT = 40040
Public Const WINAMP_VOLUMEUP = 40058
Public Const WINAMP_VOLUMEDOWN = 40059
Public Const WINAMP_FFWD5S = 40060
Public Const WINAMP_REW5S = 40061
Public Const WINAMP_BUTTON1 = 40044
Public Const WINAMP_BUTTON2 = 40045
Public Const WINAMP_BUTTON3 = 40046
Public Const WINAMP_BUTTON4 = 40047
Public Const WINAMP_BUTTON5 = 40048
Public Const WINAMP_BUTTON1_SHIFT = 40144
Public Const WINAMP_BUTTON4_SHIFT = 40147
Public Const WINAMP_BUTTON5_SHIFT = 40148
Public Const WINAMP_BUTTON1_CTRL = 40154
Public Const WINAMP_BUTTON2_CTRL = 40155
Public Const WINAMP_BUTTON5_CTRL = 40158
Public Const WINAMP_FILE_PLAY = 40029
Public Const WINAMP_OPTIONS_PREFS = 40012
Public Const WINAMP_OPTIONS_AOT = 40019
Public Const WINAMP_HELP_ABOUT = 40041

Public Const ID3Editor = 40188
Private Const BM_GETSTATE As Long = &HF2
Private Const BST_CHECKED As Long = &H1
Private Const BST_FOCUS As Long = &H8
Private Const BST_INDETERMINATE As Long = &H2
Private Const BST_PUSHED As Long = &H4
Private Const BST_UNCHECKED As Long = &H0

Public Type COPYDATASTRUCT
        dwData As Long
        cbData As Long
        lpData As String
End Type

'Song Info
Public Type Mp3InfoType
        id3v1 As Boolean
        title As Variant
        Artist As Variant
        Album As Variant
        Year As Variant
        Genre As Variant
        Comment As Variant
        Track As Variant
        Mystery As Variant
        MPEGInfo As Variant
        
        id3v2 As Boolean
        id3v2_Track As Variant
        ID3v2_Title As Variant
        id3v2_Artist As Variant
        id3v2_Album As Variant
        id3v2_Year As Variant
        id3v2_Genre As Variant
        id3v2_Comment As Variant
        id3v2_Composer As Variant
        id3v2_OrgArtist As Variant
        id3v2_Copyright As Variant
        id3v2_Url As Variant
        id3v2_EncodedBy As Variant
End Type

Public MP3Info As Mp3InfoType

'Gets path/filename
Public Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, ByVal lpFilePart As String) As Long

'TypeText Declares
Public Declare Function SetForegroundWindow Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function GetForegroundWindow Lib "user32" () As Long
Public Declare Sub keybd_event Lib "user32" (ByVal bVk As Byte, ByVal bScan As Byte, ByVal dwFlags As Long, ByVal dwExtraInfo As Long)
Public Declare Function VkKeyScan Lib "user32" Alias "VkKeyScanA" (ByVal cChar As Byte) As Integer
Public Declare Function MapVirtualKey Lib "user32" Alias "MapVirtualKeyA" (ByVal wCode As Long, ByVal wMapType As Long) As Long
Public Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Public Const KEYEVENTF_KEYUP = &H2

Public Function TypeText(TextToType As String, WindowToTypeIn As Long) As Long
'This is a function I made to send text
'To a certain application using modules
'Has nothing to do with winamp, you can skip it, I use
'it in a different function
    Dim mVK As Long
    Dim mScan As Long
    Dim A As Integer
    Dim CurrentForeground As Long
    Dim GiveUpCount As Integer
    Dim ShiftDown As Boolean, AltDown As Boolean, ControlDown As Boolean
    
    If TextToType = "" Then Exit Function
    
    CurrentForeground = GetForegroundWindow()
    
    For A = 1 To Len(TextToType)
        
        mVK = VkKeyScan(Asc(Mid(TextToType, A, 1)))
        mScan = MapVirtualKey(mVK, 0)
        
        ShiftDown = (mVK And &H100)
        ControlDown = (mVK And &H200)
        AltDown = (mVK And &H400)
        
        mVK = mVK And &HFF
        
        GiveUpCount = 0
        
        Do While GetForegroundWindow() <> WindowToTypeIn And GiveUpCount < 20
            GiveUpCount = GiveUpCount + 1
            SetForegroundWindow WindowToTypeIn
            DoEvents
        Loop
        
        If GetForegroundWindow() <> WindowToTypeIn Then TypeText = 0: Exit Function
        
        If ShiftDown Then keybd_event &H10, 0, 0, 0
        If ControlDown And &H200 Then keybd_event &H11, 0, 0, 0
        If AltDown And &H400 Then keybd_event &H12, 0, 0, 0
        
        keybd_event mVK, mScan, 0, 0
        
        If ShiftDown Then keybd_event &H10, 0, KEYEVENTF_KEYUP, 0
        If ControlDown Then keybd_event &H11, 0, KEYEVENTF_KEYUP, 0
        If AltDown Then keybd_event &H12, 0, KEYEVENTF_KEYUP, 0
        
    Next A
    
    SetForegroundWindow CurrentForeground
    
    TypeText = 1
    
End Function

Public Function RegGetString$(hInKey As Long, ByVal subkey$, ByVal valname$)
'I got this from Microsoft's page and edited it a bit
'Has nothing to do with winamp, you can skip it, I use
'it in a different function
    Dim RetVal$, hSubKey As Long, dwType As Long, SZ As Long, v$, R As Long
    RetVal$ = ""
    R = RegOpenKeyEx(hInKey, subkey$, 0, KEY_QUERY_VALUE, hSubKey)
    If R <> 0 Then Exit Function
    SZ = 256
    v$ = String$(SZ, 0)
    R = RegQueryValueEx(hSubKey, valname$, 0, dwType, ByVal v$, SZ)
    If R = 0 And dwType = 1 Then
        RetVal$ = Left(v$, SZ - 1)
    Else
        RetVal$ = ""
    End If


    If hInKey = 0 Then R = RegCloseKey(hSubKey)
    RegGetString$ = RetVal$
End Function

Public Function FindWinamp() As Long
'Find winamp window
'Returns 1 if winamp is open, 0 if not
    hwnd_winamp = FindWindow("Winamp v1.x", vbNullString)
    If hwnd_winamp Then FindWinamp = 1 Else FindWinamp = 0
End Function

Public Function DeletePlayList() As Long
'Clears the play list
    DeletePlayList = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_DELETE)
End Function
Public Function IsPlaying() As Long
'Returns:
'1 If playing
'3 if paused
'0 if stopped
    IsPlaying = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_ISPLAYING)
End Function

Public Function GetSongLength() As Long
'Finds the song length in Seconds
    GetSongLength = SendMessage(hwnd_winamp, WM_WA_IPC, 1, IPC_GETOUTPUTTIME)
End Function

Public Function GetCurrentSongPosition() As Double
'Finds the current song position in milliseconds
    GetCurrentSongPosition = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_GETOUTPUTTIME)
End Function

Public Function SetCurrentSongPosition(Optional Seconds As Long, Optional Ms As Long)
'Sets the current position in the song
'Returns:
'0 if success
'1 if eof
'-1 if not playing
    SetCurrentSongPosition = SendMessage(hwnd_winamp, WM_WA_IPC, (Seconds * 1000 + Ms), IPC_JUMPTOTIME)
End Function

Public Function WritePlayList() As Long
'Writes the current playlist to C:\WINAMP_DIR\Winamp.m3u
'And then finds the play position
'Now obsolete, but good for old version of winamp
'Look at GetPlayListPosition
    WritePlayList = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_WRITEPLAYLIST)
End Function

Public Function SetPlayListPosition(Position As Integer) As Long
'Sets which song to play (0 being first)
    SetPlayListPosition = SendMessage(hwnd_winamp, WM_WA_IPC, Position, IPC_SETPLAYLISTPOS)
End Function

Public Function SetVolume(Volume As Integer) As Long
'Sets the volume (Volume must be between 0 - 255)
    SetVolume = SendMessage(hwnd_winamp, WM_WA_IPC, Volume, IPC_SETVOLUME)
End Function

Public Function SetPanning(PanPosition As Integer) As Long
'Sets the panning (PanPosition must be between 0 - 255)
    SetPanning = SendMessage(hwnd_winamp, WM_WA_IPC, PanPosition, IPC_SETPANNING)
End Function

Public Function GetPlayListLength() As Long
'Gets amount of songs in play list
    GetPlayListLength = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_GETLISTLENGTH)
End Function

Public Function GetPlayListPosition() As Long
'Returns which song its playing in the playlist
'0 being first
    GetPlayListPosition = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_GETLISTPOS)
End Function

Public Function GetSamplerate() As Long
'Gets the samplerate
    GetSamplerate = SendMessage(hwnd_winamp, WM_WA_IPC, 0, IPC_GETINFO)
End Function

Public Function GetBitrate() As Long
'Gets the bitrate
    GetBitrate = SendMessage(hwnd_winamp, WM_WA_IPC, 1, IPC_GETINFO)
End Function

Public Function GetChannels() As Long
'Gets the channel
    GetChannels = SendMessage(hwnd_winamp, WM_WA_IPC, 2, IPC_GETINFO)
End Function

Public Function GetEQBandData(BandNumber As Integer) As Long
'Get each EQ banddata (0 being the first, 9 being last)
'Returns 0 - 255
    If BandNumber > 9 Then Exit Function
    GetEQBandData = SendMessage(hwnd_winamp, WM_WA_IPC, BandNumber, IPC_GETEQDATA)
End Function

Public Function GetEQPreampValue() As Long
'Gets the preamp value (Between 0 - 255)
    GetEQPreampValue = SendMessage(hwnd_winamp, WM_WA_IPC, 10, IPC_GETEQDATA)
End Function

Public Function GetEQEnabled()
'1 if EQ is enabled
'0 if it isn't
    GetEQEnabled = SendMessage(hwnd_winamp, WM_WA_IPC, 11, IPC_GETEQDATA)
End Function

Public Function GetEQAutoLoad()
'1 if EQ is autoloaded
'0 if it isn't
    GetEQAutoLoad = SendMessage(hwnd_winamp, WM_WA_IPC, 12, IPC_GETEQDATA)
End Function

Public Function PlayFile(FileToPlay As String) As Long
'Adds FileToPlay to the play list
    Dim CDS As COPYDATASTRUCT
    CDS.dwData = IPC_PLAYFILE
    CDS.lpData = FileToPlay
    CDS.cbData = Len(FileToPlay) + 1
    PlayFile = SendMessageCDS(hwnd_winamp, WM_COPYDATA, 0, CDS)
End Function

Public Function ChangeDirectory(Directory As String) As Long
'Changes directory
    Dim CDS As COPYDATASTRUCT
    CDS.dwData = IPC_CHDIR
    CDS.lpData = Directory
    CDS.cbData = Len(Directory) + 1
    ChangeDirectory = SendMessageCDS(hwnd_winamp, WM_COPYDATA, 0, CDS)
End Function

Public Function ToggleEQWindow() As Long
'Turns on or off the EQ window
    ToggleEQWindow = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_OPTIONS_EQ, 0)
End Function

Public Function TogglePlayListWindow() As Long
'Turns on or off play list window
    TogglePlayListWindow = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_OPTIONS_PLEDIT, 0)
End Function

Public Function VolumeUp() As Long
'Raises the volume a tiny bit
    VolumeUp = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_VOLUMEUP, 0)
End Function
Public Function VolumeDown() As Long
'Sets the volume down a tiny bit
    VolumeDown = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_VOLUMEDOWN, 0)
End Function

Public Function Rewind() As Long
'Rewinds by 5 seconds
    Rewind = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_REW5S, 0)
End Function

Public Function FastForward() As Long
'Fast forwards by 5 seconds
    FastForward = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_FFWD5S, 0)
End Function

Public Function PreviousSong() As Long
'Plays the previous song
    PreviousSong = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON1, 0)
End Function

Public Function PlaySong() As Long
'Plays the current song
    PlaySong = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON2, 0)
End Function

Public Function PauseSong() As Long
'Pauses playing
    PauseSong = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON3, 0)
End Function
Public Function StopSong() As Long
'Stops playing
    StopSong = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON4, 0)
End Function

Public Function NextSong() As Long
'Plays the next song in the playlist
    NextSong = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON5, 0)
End Function

Public Function FadeStop() As Long
'slowly fades away until it stops
    FadeStop = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON4_SHIFT, 0)
End Function

Public Function Back10Songs() As Long
'Goes to the first song in the play list
    Back10Songs = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON1_CTRL, 0)
End Function

Public Function Forward10Songs() As Long
'Goes to the last song in the play list
    Forward10Songs = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON5_CTRL, 0)
End Function
Public Function OpenLocation() As Long
'Shows Open Location Dialog
    OpenLocation = PostMessage(hwnd_winamp, WM_COMMAND, WINAMP_BUTTON2_CTRL, 0)
End Function
Public Function LoadFile() As Long
'Shows Load a file dialog
    LoadFile = PostMessage(hwnd_winamp, WM_COMMAND, WINAMP_FILE_PLAY, 0)
End Function
Public Function ShowPreferences() As Long
'Shows Preferences Dialog
    ShowPreferences = PostMessage(hwnd_winamp, WM_COMMAND, WINAMP_OPTIONS_PREFS, 0)
End Function
Public Function ShowID3Box() As Long
'Shows ID3 editor
    ShowID3Box = PostMessage(hwnd_winamp, WM_COMMAND, ID3Editor, 0)
End Function
Public Function ToggleAlwaysOnTop() As Long
'Turns Always On Top On and Off
    ToggleAlwaysOnTop = SendMessage(hwnd_winamp, WM_COMMAND, WINAMP_OPTIONS_AOT, 0)
End Function

Public Function ShowAbout() As Long
'Shows About Box
    ShowAbout = PostMessage(hwnd_winamp, WM_COMMAND, WINAMP_HELP_ABOUT, 0)
End Function

Public Function ToggleRepeat() As Long
'Turns On/Off the repeat songs
    ToggleRepeat = TypeText("r", hwnd_winamp)
End Function

Public Function ToggleShuffle() As Long
'Turns On/Off the shuffle songs
    ToggleShuffle = TypeText("s", hwnd_winamp)
End Function

Public Function ToggleWindowShade() As Long
'Turns On/Off Window Shade mode
    keybd_event vbKeyCtrl, 0, 0, 0
        ToggleWindowShade = TypeText("w", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleDoubleSize() As Long
'Turns on/off doublesize
    keybd_event vbKeyCtrl, 0, 0, 0
        ToggleDoubleSize = TypeText("d", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleEasyMove() As Long
'turns on/off easy move
    keybd_event vbKeyCtrl, 0, 0, 0
        ToggleEasyMove = TypeText("r", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleTimeDisplay() As Long
'Changes type of time display
    keybd_event vbKeyCtrl, 0, 0, 0
        ToggleTimeDisplay = TypeText("t", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleMainWindow() As Long
'Hides/Shows winamp
    keybd_event vbKeyAlt, 0, 0, 0
        ToggleMainWindow = TypeText("w", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleMiniBrowser() As Long
'Hides/Shows Mini Browser
    keybd_event vbKeyAlt, 0, 0, 0
        ToggleMiniBrowser = TypeText("t", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ShowSkinBrowser() As Long
'Shows Skin Browser
    keybd_event vbKeyAlt, 0, 0, 0
        ShowSkinBrowser = TypeText("s", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function
Public Function ShowVisualOptions() As Long
'Shows Visual Options
    keybd_event vbKeyAlt, 0, 0, 0
        ShowVisualOptions = TypeText("o", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ShowConfigureVisualPlugin() As Long
'Shows Configuration for current visual plugin
    keybd_event vbKeyAlt, 0, 0, 0
        ShowConfigureVisualPlugin = TypeText("k", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ToggleVisualPlugin() As Long
'Shows/Hides visual plugin
    keybd_event vbKeyAlt, 0, 0, 0
        ToggleVisualPlugin = TypeText("K", hwnd_winamp)
    keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function ShowVisualPluginsSelect() As Long
'Shows visual plugins selection
    keybd_event vbKeyCtrl, 0, 0, 0
        ShowVisualPluginsSelect = TypeText("k", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function


Public Function StopAfterCurrentSong() As Long
'Stop playing after current song
    keybd_event vbKeyCtrl, 0, 0, 0
        StopAfterCurrentSong = TypeText("v", hwnd_winamp)
    keybd_event vbKeyCtrl, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function OpenDirectory() As Long
'Shows Open Directory dialog
    OpenDirectory = TypeText("L", hwnd_winamp)
End Function

Public Function ShowInfoBox() As Long
'Shows info box for current song

'ShowInfoBox = PostMessage(hwnd_winamp, &H433, 0, 0)
'PostMessage2 hwnd_winamp, &H433, 0&, 0&

keybd_event vbKeyAlt, 0, 0, 0
ShowInfoBox = TypeText("3", hwnd_winamp)
keybd_event vbKeyAlt, 0, KEYEVENTF_KEYUP, 0
End Function

Public Function GetMp3Info() As Long
'Finds all the info about the current mp3 and sets
'Mp3Info to the info
'Mp3Info.Title = title
'Mp3Info.Artist = artist and so on
    
    Dim hwnd_InfoBox As Long
    Dim hwnd_TmpText As Long
    Dim TmpText As String * 256
    Dim TextLen As Long
    Dim aaa As Long
    'ShowInfoBfox
    ShowID3Box
    DoEvents
    Sleep 50
    
    Do While hwnd_InfoBox = 0
        DoEvents
        hwnd_InfoBox = FindWindow("#32770", "File Info")
    Loop
   'hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Button", "ID3v&1 Tag")
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Button", "ID3v2")
    MP3Info.id3v1 = ((SendMessage(hwnd_TmpText, BM_GETSTATE, 0&, ByVal 0&) And BST_CHECKED) = BST_CHECKED)
    If MP3Info.id3v1 = False Then
    With MP3Info
        .Album = "ID3v1 is disabled"
        .Artist = "ID3v1 is disabled"
        .Comment = "ID3v1 is disabled"
        .Genre = "ID3v1 is disabled"
        .title = "ID3v1 is disabled"
        .Track = "ID3v1 is disabled"
        .Year = "ID3v1 is disabled"
        .Mystery = "ID3v1 is disabled"
    End With
    Else:
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Track = ""
        Else:
        MP3Info.Track = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.title = ""
        Else:
        MP3Info.title = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Artist = ""
        Else:
        MP3Info.Artist = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Album = ""
        Else:
        MP3Info.Album = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Year = ""
        Else:
        MP3Info.Year = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "ComboBox", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Genre = ""
        Else:
        MP3Info.Genre = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.Comment = ""
        Else:
        MP3Info.Comment = Left(TmpText, TextLen)
        End If
    End If
    
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Button", vbNullString)
   
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
    TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
    If TmpText = vbNullString Then
    MP3Info.MPEGInfo = ""
    Else:
    MP3Info.MPEGInfo = Left(TmpText, TextLen)
    End If
'hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Button", "ID3v&2 Tag")
'hwnd_InfoBox = FindWindow(hwnd_InfoBox, "SysTabControl32")
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "SysTabControl32", vbNullString)
    aaa = hwnd_TmpText
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Button", vbNullString)   ' safak  buradan sonrasý pencere numarasý doðru verilse de çalýþmýyor.
    
    MP3Info.id3v2 = ((SendMessage(hwnd_TmpText, BM_GETSTATE, 0&, ByVal 0&) And BST_CHECKED) = BST_CHECKED)
    
    If MP3Info.id3v2 = False Then
    With MP3Info
        .id3v2_Album = "ID3v2 is disabled"
        .id3v2_Artist = "ID3v2 is disabled"
        .id3v2_Comment = "ID3v2 is disabled"
        .id3v2_Composer = "ID3v2 is disabled"
        .id3v2_Copyright = "ID3v2 is disabled"
        .id3v2_EncodedBy = "ID3v2 is disabled"
        .id3v2_Genre = "ID3v2 is disabled"
        .id3v2_OrgArtist = "ID3v2 is disabled"
        .ID3v2_Title = "ID3v2 is disabled"
        .id3v2_Track = "ID3v2 is disabled"
        .id3v2_Url = "ID3v2 is disabled"
        .id3v2_Year = "ID3v2 is disabled"
    End With
    Else:
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Track = ""
        Else:
        MP3Info.id3v2_Track = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.ID3v2_Title = ""
        Else:
        MP3Info.ID3v2_Title = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Artist = ""
        Else:
        MP3Info.id3v2_Artist = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Album = ""
        Else:
        MP3Info.id3v2_Album = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Year = ""
        Else:
        MP3Info.id3v2_Year = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "ComboBox", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Genre = ""
        Else:
        MP3Info.id3v2_Genre = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Comment = ""
        Else:
        MP3Info.id3v2_Comment = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Composer = ""
        Else:
        MP3Info.id3v2_Composer = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_OrgArtist = ""
        Else:
        MP3Info.id3v2_OrgArtist = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Copyright = ""
        Else:
        MP3Info.id3v2_Copyright = Left(TmpText, TextLen)
        End If
        
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_Url = ""
        Else:
        MP3Info.id3v2_Url = Left(TmpText, TextLen)
        End If
    
        hwnd_TmpText = FindWindowEx(hwnd_InfoBox, hwnd_TmpText, "Edit", vbNullString)
        TextLen = SendMessageS(hwnd_TmpText, WM_GETTEXT, Len(TmpText), TmpText)
        If TmpText = vbNullString Then
        MP3Info.id3v2_EncodedBy = ""
        Else:
        MP3Info.id3v2_EncodedBy = Left(TmpText, TextLen)
        End If
    End If ' end of id3v2 tags
    
    DoEvents
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Button", "&Cancel")
    hwnd_TmpText = FindWindowEx(hwnd_InfoBox, 0, "Button", "&Cancel")
    DoEvents
    
    ShowWindow hwnd_InfoBox, 1 'SW_SHOWNORMAL = 1
    PostMessage2 hwnd_InfoBox, &H10, 0&, 0& '&H10 = WM_CLOSE
    
    'keybd_event vbKeyAlt, 0, 0, 0
    'TypeText vbKeyF4, hwnd_InfoBox
    'keybd_event vbKeyAlt, 0, 0, 0
    'TypeText Chr(13), hwnd_TmpText
   ' DoEvents
    'TypeText Chr(13), hwnd_TmpText
    ' Sleep 500
End Function

Public Function GetWinampPathAndExeFile() As String
'Finds the path of winamp
    
    Dim WinampPath As String
    
    WinampPath = RegGetString(HKEY_CLASSES_ROOT, WINAMP_REG_KEY, "")
    If Len(WinampPath) < 8 Then GetWinampPathAndExeFile = "": Exit Function
    WinampPath = Mid(WinampPath, 2, Len(WinampPath) - 7)
    GetWinampPathAndExeFile = WinampPath
End Function
Public Function GetWinampPath() As String
    Dim A As Integer
    GetWinampPath = GetWinampPathAndExeFile
        
    GetWinampPath = Left$(GetWinampPath, InStrRev(GetWinampPath, "\"))
End Function

Public Function GetCurrentSongPath() As String
'Finds the path of the song currently playing
    Dim CurrentPosition As Integer
    Dim PathOfWinamp As String
    Dim CurrentSongPath As String
    Dim A As Integer
    Dim Enter As Long
    Dim All As String
    
    Static CorrectedFile As String
    Static WholeFile As String

    CurrentPosition = GetPlayListPosition
    GetCurrentSongPath = ""
    
    If CurrentPosition = -1 Then Exit Function
    PathOfWinamp = GetWinampPath
    If PathOfWinamp = "" Then Exit Function
    
    If FindWinamp = 0 Then Exit Function
    If WritePlayList = -1 Then Exit Function
    
    If FileExists(PathOfWinamp & "WINAMP.m3u") Then
        On Error GoTo NoFile
        Open PathOfWinamp & "WINAMP.m3u" For Input As #1
        All = Input(LOF(1), 1)
    End If
    If WholeFile <> All And All <> "" Then
        WholeFile = All
        All = CorrectList(All)
        
        CorrectedFile = All
    Else
        All = CorrectedFile
    End If
    
    For A = 1 To CurrentPosition
        Enter = InStr(All, Chr$(13))
        All = Mid$(All, Enter + 2)
    Next A
    
    Enter = InStr(All, Chr$(13))
    If Enter > 0 Then
        GetCurrentSongPath = Left$(All, Enter - 1)
    End If
    On Error GoTo 0
    Close #1
    Exit Function
    
NoFile:
    If Err = 75 Or Err = 53 Then
        'Path/File access error
        'File not found
        Resume Next
    ElseIf Err = 52 Then
        'Bad file name or number
        Resume Next
    End If
End Function

Public Function GetPathOfSongInPlayList(PlayListPosition As Integer)
'Finds the path of the song in the playlist (0 being first)
Dim PathOfWinamp As String
Dim SongPath As String
Dim A As Integer

    'Stop
    If PlayListPosition > GetPlayListLength() Then Exit Function
    PathOfWinamp = GetWinampPath
    If PathOfWinamp = "" Then Exit Function
        
    If FindWinamp = 0 Then Exit Function
    If WritePlayList = -1 Then Exit Function
    
    Open PathOfWinamp & "WINAMP.m3u" For Input As #1
    Line Input #1, SongPath
    On Error Resume Next
    For A = 1 To (PlayListPosition + 1)
        Line Input #1, SongPath
        Line Input #1, SongPath
    Next A
    On Error GoTo 0
    Close #1
    
    If SongPath = "#EXTM3U" Then SongPath = ""
    
    GetPathOfSongInPlayList = SongPath
    
End Function

Public Function GetFileAbsolutePosition(File As String) As Long
    'Finds the path of the song in the playlist (0 being first)
    Dim PathOfWinamp As String
    Dim SongPath As String
    Dim All As String
    Dim A As Integer
    Dim Last As Long
    Dim ExtInf As Long, Enter As Long

    Last = GetPlayListLength
    GetFileAbsolutePosition = -1
    
    PathOfWinamp = GetWinampPath
    If PathOfWinamp = "" Then Exit Function
        
    If FindWinamp = 0 Then Exit Function
    If WritePlayList = -1 Then Exit Function
    
    Open PathOfWinamp & "WINAMP.m3u" For Input As #1
    All = Input(LOF(1), 1)
    All = CorrectList(All)
    
    For A = 1 To Last
        Enter = InStr(All, Chr$(13))
        If UCase$(Left$(All, Enter - 1)) = UCase$(File) Then
            GetFileAbsolutePosition = A - 1
            Exit For
        End If
        All = Mid$(All, Enter + 2)
    Next A
    On Error GoTo 0
    Close #1
    
    'If SongPath = "#EXTM3U" Then SongPath = ""
End Function

Public Function IsFileOnList(File As String) As Boolean
    'Returns -1 is was not found
    Dim PathOfWinamp As String
    Dim A As Integer
    Dim All As String
    
    IsFileOnList = False
    
    PathOfWinamp = GetWinampPath
    If PathOfWinamp = "" Then Exit Function

    If FindWinamp = 0 Then Exit Function
    If WritePlayList = -1 Then Exit Function
    
    On Error Resume Next
    Open PathOfWinamp & "WINAMP.m3u" For Input As #1
    All = Input(LOF(1), 1)
    Close #1
    On Error GoTo 0
    
    If InStr(UCase$(All), UCase$(File)) Then
        IsFileOnList = True
    End If
    
End Function

Private Function CorrectList(All As String) As String
    Dim ExtInf As Long, Enter As Long
    All = Mid$(All, 10)
    Do
        ExtInf = InStr(All, "#EXTINF")
        If ExtInf Then
            Enter = InStr(ExtInf + 1, All, Chr$(13))
            If ExtInf = 1 Then
                All = Mid$(All, Enter + 2)
            Else
                All = Left$(All, ExtInf - 1) & Mid$(All, Enter + 2)
            End If
        End If
    Loop Until ExtInf = 0
    
    CorrectList = All
End Function

Public Function FileExists(ByVal strPathName As String) As Integer
    Dim intFileNum As Integer

    On Error Resume Next

    '
    'Remove any trailing directory separator character
    '
    If Right$(strPathName, 1) = "\" Then
        strPathName = Left$(strPathName, Len(strPathName) - 1)
    End If

    '
    'Attempt to open the file, return value of this function is False
    'if an error occurs on open, True otherwise
    '
    intFileNum = FreeFile
    Open strPathName For Input As intFileNum

    FileExists = IIf(Err, False, True)

    Close intFileNum

    Err = 0
End Function

Function getWinampWindowText()
lHandle = FindWindow("Winamp v1.x", vbNullString) 'This is for finding the window, "Winamp v1.x" is the reference to the window type of the Winamp pogram
If lHandle > 0 Then 'making sure the window exists
    Dim lRet As Long
    Dim sTitle As String * 256
    Dim sCaption As String
    lRet = GetWindowText(lHandle, sTitle, Len(sTitle))
    sCaption = Left(sTitle, InStr(1, sTitle, vbNullChar, vbTextCompare))
    sCaption = Replace(sCaption, " - Winamp", "")
    Do
        If IsNumeric(Left(sCaption, 1)) = True Or Left(sCaption, 1) = "." Or Left(sCaption, 1) = " " Then
        sCaption = Right(sCaption, Len(sCaption) - 1)
        Else
        Exit Do
        End If
    Loop
    Do
        If IsNumeric(Right(sCaption, 1)) = True Or Right(sCaption, 1) = ")" Or Right(sCaption, 1) = " " Or Right(sCaption, 1) = ":" Then 'removes the number from the winamp currently playing song.
        sCaption = Left(sCaption, Len(sCaption) - 1)
        ElseIf Right(sCaption, 1) = "(" Then
        sCaption = Left(sCaption, Len(sCaption) - 1)
        Exit Do
        Else
        Exit Do
        End If
    Loop
    getWinampWindowText = sCaption 'sets the return value of the module to the edited sCaption strong, which now contains the song name and artist...
Else
    getWinampWindowText = "Winamp isn't currently playing" 'sets the return value of the module to the edited sCaption string which has jut been set because the winamp title could not be found
End If
End Function
