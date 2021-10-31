Attribute VB_Name = "modMP3"
'Written By:    Jesse Yeager
'Dependencies:  None
'This module is for reading MP3 files, as well as reading and writing ID3v1 and ID3v2 Tags.


Option Explicit



Private Const ID3v2_AENC As String = "AENC"   'Audio encryption
Private Const ID3v2_APIC As String = "APIC"   'Attached picture
Private Const ID3v2_ASPI As String = "ASPI"   'Audio seek point index

Private Const ID3v2_COMM As String = "COMM"   'Comments
Private Const ID3v2_COMR As String = "COMR"   'Commercial frame

Private Const ID3v2_ENCR As String = "ENCR"   'Encryption method registration
Private Const ID3v2_EQU2 As String = "EQU2"   'Equalisation(2)
Private Const ID3v2_ETCO As String = "ETCO"   'Event timing codes

Private Const ID3v2_GEOB As String = "GEOB"   'General encapsulated object
Private Const ID3v2_GRID As String = "GRID"   'Group identification registration

Private Const ID3v2_LINK As String = "LINK"   'Linked information

Private Const ID3v2_MCDI As String = "MCDI"   'Music CD identifier
Private Const ID3v2_MLLT As String = "MLLT"   'MPEG location lookup table

Private Const ID3v2_OWNE As String = "OWNE"   'Ownership frame

Private Const ID3v2_PRIV As String = "PRIV"   'Private frame
Private Const ID3v2_PCNT As String = "PCNT"   'Play counter
Private Const ID3v2_POPM As String = "POPM"   'Popularimeter
Private Const ID3v2_POSS As String = "POSS"   'Position synchronisation frame

Private Const ID3v2_RBUF As String = "RBUF"   'Recommended buffer size
Private Const ID3v2_RVA2 As String = "RVA2"   'Relative volume adjustment (2)
Private Const ID3v2_RVRB As String = "RVRB"   'Reverb

Private Const ID3v2_SEEK As String = "SEEK"   'Seek frame
Private Const ID3v2_SIGN As String = "SIGN"   'Signature frame
Private Const ID3v2_SYLT As String = "SYLT"   'Synchronised lyric/text
Private Const ID3v2_SYTC As String = "SYTC"   'Synchronised tempo codes

Private Const ID3v2_TALB As String = "TALB"   'Album/Movie/Show title
Private Const ID3v2_TBPM As String = "TBPM"   'BPM (beats per minute)
Private Const ID3v2_TCOM As String = "TCOM"   'Composer
Private Const ID3v2_TCON As String = "TCON"   'Content type
Private Const ID3v2_TCOP As String = "TCOP"   'Copyright message
Private Const ID3v2_TDEN As String = "TDEN"   'Encoding time
Private Const ID3v2_TDLY As String = "TDLY"   'Playlist delay
Private Const ID3v2_TDOR As String = "TDOR"   'Original release time
Private Const ID3v2_TDRC As String = "TDRC"   'Recording time
Private Const ID3v2_TDRL As String = "TDRL"   'Release time
Private Const ID3v2_TDTG As String = "TDTG"   'Tagging time
Private Const ID3v2_TENC As String = "TENC"   'Encoded by
Private Const ID3v2_TEXT As String = "TEXT"   'Lyricist/Text writer
Private Const ID3v2_TFLT As String = "TFLT"   'File type
Private Const ID3v2_TIPL As String = "TIPL"   'Involved people list
Private Const ID3v2_TIT1 As String = "TIT1"   'Content group description
Private Const ID3v2_TIT2 As String = "TIT2"   'Title/songname/content description
Private Const ID3v2_TIT3 As String = "TIT3"   'Subtitle/Description refinement
Private Const ID3v2_TKEY As String = "TKEY"   'Initial key
Private Const ID3v2_TLAN As String = "TLAN"   'Language(s)
Private Const ID3v2_TLEN As String = "TLEN"   'Length
Private Const ID3v2_TMCL As String = "TMCL"   'Musician credits list
Private Const ID3v2_TMED As String = "TMED"   'Media type
Private Const ID3v2_TMOO As String = "TMOO"   'Mood
Private Const ID3v2_TOAL As String = "TOAL"   'Original album/movie/show title
Private Const ID3v2_TOFN As String = "TOFN"   'Original filename
Private Const ID3v2_TOLY As String = "TOLY"   'Original lyricist(s)/text writer(s)
Private Const ID3v2_TOPE As String = "TOPE"   'Original artist(s)/performer(s)
Private Const ID3v2_TOWN As String = "TOWN"   'File owner/licensee
Private Const ID3v2_TPE1 As String = "TPE1"   'Lead performer(s)/Soloist(s)
Private Const ID3v2_TPE2 As String = "TPE2"   'Band / orchestra / accompaniment
Private Const ID3v2_TPE3 As String = "TPE3"   'Conductor/performer refinement
Private Const ID3v2_TPE4 As String = "TPE4"   'Interpreted, remixed, or otherwise modified by
Private Const ID3v2_TPOS As String = "TPOS"   'Part of a set
Private Const ID3v2_TPRO As String = "TPRO"   'Produced notice
Private Const ID3v2_TPUB As String = "TPUB"   'Publisher
Private Const ID3v2_TRCK As String = "TRCK"   'Track number/Position in set
Private Const ID3v2_TRSN As String = "TRSN"   'Internet radio station name
Private Const ID3v2_TRSO As String = "TRSO"   'Internet radio station owner
Private Const ID3v2_TSOA As String = "TSOA"   'Album sort order
Private Const ID3v2_TSOP As String = "TSOP"   'Performer sort order
Private Const ID3v2_TSOT As String = "TSOT"   'Title sort order
Private Const ID3v2_TSRC As String = "TSRC"   'ISRC (international standard recording code)
Private Const ID3v2_TSSE As String = "TSSE"   'Software/Hardware and settings used for encoding
Private Const ID3v2_TSST As String = "TSST"   'Set subtitle
Private Const ID3v2_TXXX As String = "TXXX"   'User defined text information frame
Private Const ID3v2_TYER As String = "TYER"   'Year

Private Const ID3v2_UFID As String = "UFID"   'Unique file identifier
Private Const ID3v2_USER As String = "USER"   'Terms of use
Private Const ID3v2_USLT As String = "USLT"   'Unsynchronised lyric/text transcription

Private Const ID3v2_WCOM As String = "WCOM"   'Commercial information
Private Const ID3v2_WCOP As String = "WCOP"   'Copyright/Legal information
Private Const ID3v2_WOAF As String = "WOAF"   'Official audio file webpage
Private Const ID3v2_WOAR As String = "WOAR"   'Official artist/performer webpage
Private Const ID3v2_WOAS As String = "WOAS"   'Official audio source webpage
Private Const ID3v2_WORS As String = "WORS"   'Official Internet radio station homepage
Private Const ID3v2_WPAY As String = "WPAY"   'Payment
Private Const ID3v2_WPUB As String = "WPUB"   'Publishers official webpage
Private Const ID3v2_WXXX As String = "WXXX"   'User defined URL link frame


Private Function ID3v2_BuildTagString(ByVal songTitle$, ByVal songArtist$, ByVal songAlbum$, ByVal songYear As Long, ByVal songComment$, ByVal songTrackNumber As Long, ByVal songGenre$, ByVal songComposer$, ByVal songOriginalArtist$, ByVal songCopyright$, ByVal songURL$, ByVal songEncodedBy$) As String

Dim i As Long, tempStr$
If songGenre$ <> "" Then
  For i = 0 To 255
    tempStr$ = MP3_GetGenreString(i)
    If StrComp(tempStr$, songGenre$, vbTextCompare) = 0 Then
      songGenre$ = "(" & i & ")" & songGenre$
      Exit For
    End If
  Next i
End If

Dim tempTrack$, tempYear$
tempTrack$ = songTrackNumber
tempYear$ = songYear

Dim outStr$:  outStr$ = ""
outStr$ = outStr$ & "ID3" & Chr$(3) & Chr$(0) & Chr$(0) & String$(4, 0)
outStr$ = outStr$ & ID3v2_BuildTENCstring(songEncodedBy$)
outStr$ = outStr$ & ID3v2_BuildWXXXstring(songURL$)
outStr$ = outStr$ & ID3v2_BuildTCOPstring(songCopyright$)
outStr$ = outStr$ & ID3v2_BuildTOPEstring(songOriginalArtist$)
outStr$ = outStr$ & ID3v2_BuildTCOMstring(songComposer$)
outStr$ = outStr$ & ID3v2_BuildTRCKstring(tempTrack$)

outStr$ = outStr$ & ID3v2_BuildTIT2string(songTitle$)
outStr$ = outStr$ & ID3v2_BuildTALBstring(songAlbum$)
outStr$ = outStr$ & ID3v2_BuildTYERstring(tempYear$)
outStr$ = outStr$ & ID3v2_BuildCOMMstring(songComment)
outStr$ = outStr$ & ID3v2_BuildTCONstring(songGenre$)
outStr$ = outStr$ & ID3v2_BuildTPE1string(songArtist$)

Dim tempLen As Long, numHigh As Long, numMidH As Long, numMidL As Long, numLow As Long
tempLen = Len(outStr$) - 10
ID3v2_4BytesFromLONG_SynchSafe tempLen, numHigh, numMidH, numMidL, numLow

Mid$(outStr$, 7, 1) = Chr$(numHigh)
Mid$(outStr$, 8, 1) = Chr$(numMidH)
Mid$(outStr$, 9, 1) = Chr$(numMidL)
Mid$(outStr$, 10, 1) = Chr$(numLow)


ID3v2_BuildTagString = outStr$

End Function

Private Function ID3v1_BuildTagString(ByVal songTitle$, ByVal songArtist$, ByVal songAlbum$, ByVal songYear As Long, ByVal songComment$, ByVal songTrackNumber As Long, ByVal songGenreCode As Long) As String

If songTrackNumber > 255 Or songTrackNumber < 0 Then songTrackNumber = 0
If songGenreCode > 255 Or songGenreCode < 0 Then songGenreCode = 12   'Other

Dim outStr$:  outStr$ = ""
outStr$ = outStr$ & "TAG"
outStr$ = outStr$ & ID3v1_FormatString(songTitle$, 30)
outStr$ = outStr$ & ID3v1_FormatString(songArtist$, 30)
outStr$ = outStr$ & ID3v1_FormatString(songAlbum$, 30)
outStr$ = outStr$ & Format$(songYear, "0000")

If songTrackNumber < 1 Then
  outStr$ = outStr$ & ID3v1_FormatString(songComment$, 30)
Else
  outStr$ = outStr$ & ID3v1_FormatString(songComment$, 28) & Chr$(0) & Chr$(songTrackNumber)
End If

outStr$ = outStr$ & Chr$(songGenreCode)

ID3v1_BuildTagString = outStr$

End Function

Private Function ID3v2_BuildTextFrameString(ByVal id3v2TagType As String, ByVal id3v2TagString$, Optional ByVal textStartPos As Long = 11) As String

Dim strLen As Long
strLen = Len(id3v2TagString$)

If Len(id3v2TagString$) = 0 Then
  ID3v2_BuildTextFrameString = ""
  Exit Function
End If


Dim numHigh As Long, numMidH As Long, numMidL As Long, numLow As Long
ID3v2_4BytesFromLONG_SynchSafe strLen + 1 + (textStartPos - 11), numHigh, numMidH, numMidL, numLow

Dim outStr$
outStr$ = id3v2TagType$ & Chr$(numHigh) & Chr$(numMidH) & Chr$(numMidL) & Chr$(numLow) _
        & Chr$(0) & Chr$(0) _
        & String$(textStartPos - 11, 0) _
        & Chr$(0) & id3v2TagString$

ID3v2_BuildTextFrameString = outStr$

End Function

Private Sub ID3v2_GetTIT2info(ByRef id3v2FrameBytes() As Byte, ByRef songTitle$)

songTitle$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Function ID3v2_BuildTIT2string(ByRef songTitle$) As String

ID3v2_BuildTIT2string = ID3v2_BuildTextFrameString(ID3v2_TIT2, songTitle$)

End Function

Private Function ID3v2_BuildTPE1string(ByRef songArtist$) As String

ID3v2_BuildTPE1string = ID3v2_BuildTextFrameString(ID3v2_TPE1, songArtist$)

End Function



Private Function ID3v2_BuildTALBstring(ByRef songAlbum$) As String

ID3v2_BuildTALBstring = ID3v2_BuildTextFrameString(ID3v2_TALB, songAlbum$)

End Function

Private Function ID3v2_BuildTRCKstring(ByRef songTrackNumber$) As String

ID3v2_BuildTRCKstring = ID3v2_BuildTextFrameString(ID3v2_TRCK, songTrackNumber$)

End Function

Private Function ID3v2_BuildTENCstring(ByRef songEncodedBy$) As String

ID3v2_BuildTENCstring = ID3v2_BuildTextFrameString(ID3v2_TENC, songEncodedBy$)

End Function

Private Function ID3v2_BuildTCOPstring(ByRef songCopyright$) As String

ID3v2_BuildTCOPstring = ID3v2_BuildTextFrameString(ID3v2_TCOP, songCopyright$)

End Function

Private Function ID3v2_BuildTCOMstring(ByRef songComposer$) As String

ID3v2_BuildTCOMstring = ID3v2_BuildTextFrameString(ID3v2_TCOM, songComposer$)

End Function

Private Function ID3v2_BuildTOPEstring(ByRef songOriginalArtist$) As String

ID3v2_BuildTOPEstring = ID3v2_BuildTextFrameString(ID3v2_TOPE, songOriginalArtist$)

End Function

Private Function ID3v2_BuildTYERstring(ByRef songYear$) As String

ID3v2_BuildTYERstring = ID3v2_BuildTextFrameString(ID3v2_TYER, songYear$)

End Function

Private Function ID3v2_BuildWXXXstring(ByRef songURL$) As String

ID3v2_BuildWXXXstring = ID3v2_BuildTextFrameString(ID3v2_WXXX, songURL$, 12)

End Function

Private Function ID3v2_BuildCOMMstring(ByRef songComment$) As String

ID3v2_BuildCOMMstring = ID3v2_BuildTextFrameString(ID3v2_COMM, songComment$, 15)

End Function

Private Sub ID3v2_GetTCOMinfo(ByRef id3v2FrameBytes() As Byte, ByRef songComposer$)

songComposer$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetTOPEinfo(ByRef id3v2FrameBytes() As Byte, ByRef songOriginalArtist$)

songOriginalArtist$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetTCOPinfo(ByRef id3v2FrameBytes() As Byte, ByRef songCopyright$)

songCopyright$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetTENCinfo(ByRef id3v2FrameBytes() As Byte, ByRef songEncodedBy$)

songEncodedBy$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetCOMMinfo(ByRef id3v2FrameBytes() As Byte, ByRef songComment$)

songComment$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes(), 15)

End Sub

Private Sub ID3v2_GetWXXXinfo(ByRef id3v2FrameBytes() As Byte, ByRef songURL$)

songURL$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes(), 12)

End Sub


Private Sub ID3v2_GetTALBinfo(ByRef id3v2FrameBytes() As Byte, ByRef songAlbum$)

songAlbum$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub
Private Sub ID3v2_GetTYERinfo(ByRef id3v2FrameBytes() As Byte, ByRef songYear$)

songYear$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub
Private Sub ID3v2_GetTPE1info(ByRef id3v2FrameBytes() As Byte, ByRef songArtist$)

songArtist$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetTCONinfo(ByRef id3v2FrameBytes() As Byte, ByRef songContent$)

songContent$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Sub ID3v2_GetTRCKinfo(ByRef id3v2FrameBytes() As Byte, ByRef songTrackNumber$)

songTrackNumber$ = ID3v2_GetTextFrameInfo(id3v2FrameBytes())

End Sub

Private Function ID3v2_BuildTCONstring(ByRef songContent$) As String

ID3v2_BuildTCONstring = ID3v2_BuildTextFrameString(ID3v2_TCON, songContent$)

End Function

Private Function ID3v2_GetTextFrameInfo(ByRef id3v2FrameBytes() As Byte, Optional ByVal textStartPos As Long = 11) As String


Dim tempFrameLength As Long
tempFrameLength = ID3v2_4BytesToLONG_SynchSafe(id3v2FrameBytes(4), id3v2FrameBytes(5), id3v2FrameBytes(6), id3v2FrameBytes(7)) + 10

Dim tempTextFlags As Long
tempTextFlags = id3v2FrameBytes(10)

Dim tempStr$, outStr$, i As Long, tempBytes() As Byte

If tempTextFlags = 0 Then
  For i = textStartPos To tempFrameLength - 1
    tempStr$ = tempStr$ & Chr$(id3v2FrameBytes(i))
  Next i

ElseIf tempTextFlags = 1 Or tempTextFlags = 2 Then
  ReDim tempBytes(0 To tempFrameLength - textStartPos)
  For i = textStartPos To tempFrameLength - 1
    tempBytes(i - textStartPos) = id3v2FrameBytes(i)
  Next i
  If tempFrameLength - 1 >= textStartPos Then
    tempStr$ = ID3v2_ReadUnicode_UTF16(tempBytes(), (tempTextFlags = 2))
  End If

ElseIf tempTextFlags = 3 Then
  ReDim tempBytes(0 To tempFrameLength - textStartPos)
  For i = textStartPos To tempFrameLength - 1
    tempBytes(i - textStartPos) = id3v2FrameBytes(i)
  Next i
  tempStr$ = ID3v2_ReadUnicode_UTF8(tempBytes())
  
End If


outStr$ = ""
For i = Len(tempStr$) To 1 Step -1
  If Asc(Mid$(tempStr$, i, 1)) <> 0 Then
    outStr$ = Mid$(tempStr$, 1, i)
    Exit For
  End If
Next i

ID3v2_GetTextFrameInfo = outStr$

End Function


Private Function ID3v2_ReadUnicode_UTF16(ByRef strBytes() As Byte, Optional ByVal BigEndian As Boolean = True) As String

Dim cVal1 As Long, cVal2 As Long

cVal1 = strBytes(0)
cVal2 = strBytes(1)

Dim tStart As Long

If cVal1 = &HFF And cVal2 = &HFE Then
  BigEndian = True
  tStart = 2
ElseIf cVal1 = &HFE And cVal2 = &HFF Then
  BigEndian = False
  tStart = 2
Else
  tStart = 0
End If

Dim i As Long, byteCount As Long
Dim outStr$

For i = tStart To UBound(strBytes())
  If byteCount Mod 2 = 1 Then
    If BigEndian <> False Then
      cVal1 = cVal1 + strBytes(i)
    Else
      cVal1 = strBytes(i)
      cVal1 = cVal1 * 256
    End If
    outStr$ = outStr$ & ChrW$(cVal1)
  End If
  
  byteCount = byteCount + 1
Next i

ID3v2_ReadUnicode_UTF16 = outStr$

End Function


Private Function ID3v2_ReadUnicode_UTF8(ByRef strBytes() As Byte) As String

Dim cVal1 As Long, cVal2 As Long

Dim i As Long, j As Long, byteCount As Long
Dim charLen As Long
Dim outStr$


For i = 0 To UBound(strBytes())
  If strBytes(i) < 128 Then
    outStr$ = outStr$ & Chr$(strBytes(i))
    byteCount = byteCount + 1
  Else
    charLen = 0
    cVal2 = 0
    For j = 7 To 2 Step -1
      If MP3_GetBit(strBytes(i), j) <> False Then charLen = charLen + 1 Else Exit For
    Next j
    
    For j = (charLen - 1) To 0 Step -1
      If j > 0 Then
        cVal1 = (strBytes(i + j) And 127)
        cVal2 = cVal2 + (cVal1 * 64)
      Else
        cVal1 = (strBytes(i + j) And ((2 ^ (7 - charLen)) - 1))
        cVal2 = cVal2 + (cVal1 * 64)
      End If
    Next j
    outStr$ = outStr$ & ChrW$(cVal2)
    i = i + charLen - 1
  End If
  
Next i

ID3v2_ReadUnicode_UTF8 = outStr$

End Function

Private Function ID3v1_FormatString(ByVal inpString$, ByVal strMaxLength As Long) As String

Dim outStr$
outStr$ = Left$(inpString$ & String$(strMaxLength, 0), strMaxLength)

ID3v1_FormatString = outStr$

End Function

Public Function MP3_GetGenreString(ByVal mp3GenreCode As Long) As String

Dim outStr$

Select Case mp3GenreCode
 Case 0:   outStr$ = "Blues"
 Case 1:   outStr$ = "Classic Rock"
 Case 2:   outStr$ = "Country"
 Case 3:   outStr$ = "Dance"
 Case 4:   outStr$ = "Disco"
 Case 5:   outStr$ = "Funk"
 Case 6:   outStr$ = "Grunge"
 Case 7:   outStr$ = "Hip-Hop"
 Case 8:   outStr$ = "Jazz"
 Case 9:   outStr$ = "Metal"
 Case 10:  outStr$ = "New Age"
 Case 11:  outStr$ = "Oldies"
 Case 12:  outStr$ = "Other"
 Case 13:  outStr$ = "Pop"
 Case 14:  outStr$ = "R&B"
 Case 15:  outStr$ = "Rap"
 Case 16:  outStr$ = "Reggae"
 Case 17:  outStr$ = "Rock"
 Case 18:  outStr$ = "Techno"
 Case 19:  outStr$ = "Industrial"
 Case 20:  outStr$ = "Alternative"
 Case 21:  outStr$ = "Ska"
 Case 22:  outStr$ = "Death Metal"
 Case 23:  outStr$ = "Pranks"
 Case 24:  outStr$ = "Soundtrack"
 Case 25:  outStr$ = "Euro-Techno"
 Case 26:  outStr$ = "Ambient"
 Case 27:  outStr$ = "Trip-Hop"
 Case 28:  outStr$ = "Vocal"
 Case 29:  outStr$ = "Jazz+Funk"
 Case 30:  outStr$ = "Fusion"
 Case 31:  outStr$ = "Trance"
 Case 32:  outStr$ = "Classical"
 Case 33:  outStr$ = "Instrumental"
 Case 34:  outStr$ = "Acid"
 Case 35:  outStr$ = "House"
 Case 36:  outStr$ = "Game"
 Case 37:  outStr$ = "Sound Clip"
 Case 38:  outStr$ = "Gospel"
 Case 39:  outStr$ = "Noise"
 
 Case 40:  outStr$ = "AlternRock"
 Case 41:  outStr$ = "Bass"
 Case 42:  outStr$ = "Soul"
 Case 43:  outStr$ = "Punk"
 Case 44:  outStr$ = "Space"
 Case 45:  outStr$ = "Meditative"
 Case 46:  outStr$ = "Instrumental Pop"
 Case 47:  outStr$ = "Instrumental Rock"
 Case 48:  outStr$ = "Ethnic"
 Case 49:  outStr$ = "Gothic"
 Case 50:  outStr$ = "Darkwave"
 Case 51:  outStr$ = "Techno-Industrial"
 Case 52:  outStr$ = "Electronic"
 Case 53:  outStr$ = "Pop-Folk"
 Case 54:  outStr$ = "Eurodance"
 Case 55:  outStr$ = "Dream"
 Case 56:  outStr$ = "Southern Rock"
 Case 57:  outStr$ = "Comedy"
 Case 58:  outStr$ = "Cult"
 Case 59:  outStr$ = "Gangsta"
 Case 60:  outStr$ = "Top 40"
 Case 61:  outStr$ = "Christian Rap"
 Case 62:  outStr$ = "Pop/Funk"
 Case 63:  outStr$ = "Jungle"
 Case 64:  outStr$ = "Native American"
 Case 65:  outStr$ = "Cabaret"
 Case 66:  outStr$ = "New Wave"
 Case 67:  outStr$ = "Psychadelic"
 Case 68:  outStr$ = "Rave"
 Case 69:  outStr$ = "Showtunes"
 Case 70:  outStr$ = "Trailer"
 Case 71:  outStr$ = "Lo-Fi"
 Case 72:  outStr$ = "Tribal"
 Case 73:  outStr$ = "Acid Punk"
 Case 74:  outStr$ = "Acid Jazz"
 Case 75:  outStr$ = "Polka"
 Case 76:  outStr$ = "Retro"
 Case 77:  outStr$ = "Musical"
 Case 78:  outStr$ = "Rock & Roll"
 Case 79:  outStr$ = "Hard Rock"
 
 Case Else:  outStr$ = "Unknown"
End Select

MP3_GetGenreString = outStr$

End Function

Private Function MP3_TrimString(ByVal mp3String$) As String

Dim p1 As Long

p1 = InStr(mp3String$, Chr$(0))
If p1 <> 0 Then mp3String$ = Left$(mp3String$, p1 - 1)

mp3String$ = Trim$(mp3String$)


MP3_TrimString = mp3String$

End Function


Private Function MP3file_FindFirstFrameOffset(ByVal mp3FileName$) As Long

Dim fNum As Long, fOffset As Long, fLen As Long
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
fLen = LOF(fNum)
fOffset = 1


Dim tempBytes() As Byte:  ReDim tempBytes(0 To 4000)
Dim retVal As Long:       retVal = -1

Dim i As Long, prev255 As Boolean:  prev255 = False

Dim tempTagLen As Long, tempStr$:  tempStr$ = String$(3, 0)

Do
  Get #fNum, fOffset, tempStr$
  If tempStr$ = "ID3" Then
    ID3v2_ReadTagHeader mp3FileName$, fOffset, tempTagLen, 0, 0, False, False, False, 0, fNum
    fOffset = fOffset + tempTagLen
  End If
  
  Get #fNum, fOffset, tempBytes()
  
  For i = 0 To UBound(tempBytes())
    If prev255 <> False Then
      If (tempBytes(i) And 224) = 224 Then
        retVal = fOffset + i - 1
        Exit For
      End If
    End If
    
    If tempBytes(i) = 255 Then
      prev255 = True
    Else
      prev255 = False
    End If
  Next i
  
  If retVal <> -1 Then Exit Do
  
  fOffset = fOffset + UBound(tempBytes()) + 1
Loop

Close #fNum
MP3file_FindFirstFrameOffset = retVal
Exit Function


FileError:
 Close #fNum
 MP3file_FindFirstFrameOffset = -1


End Function

Private Function MP3file_ReadFrame(ByVal mp3FileName$, ByVal mpgFrameOffset As Long, ByRef mp3FrameLength As Long, ByRef mpgAudioVersion As Single, ByRef mpgLayerDesc As Long, ByRef mpgChannelsPerSample As Long, ByRef mpgSamplesPerSecond As Long, ByRef mpgBitsPerSecond As Long, ByRef mpgCopyRight As Boolean, Optional ByVal openFileNumber As Long = -1) As Boolean

Dim fNum As Long, bArray(0 To 3) As Byte
If openFileNumber = -1 Then
  On Error GoTo FileError
  fNum = FreeFile()
  Open mp3FileName$ For Binary As #fNum
  On Error GoTo 0
Else
  fNum = openFileNumber
End If

Get #fNum, mpgFrameOffset, bArray()
If openFileNumber = -1 Then Close #fNum


Dim numLONG As Long
numLONG = MP3_4BytesToLONG(bArray(0), bArray(1), bArray(2), bArray(3))

If (numLONG And &HFFE00000) <> &HFFE00000 Then
  GoTo FileError
End If


Dim tempLong As Long

tempLong = 0
If MP3_GetBit(numLONG, 20) Then MP3_SetBit tempLong, 1
If MP3_GetBit(numLONG, 19) Then MP3_SetBit tempLong, 0
Select Case tempLong
 Case 0:      mpgAudioVersion = 2.5
 Case 2:      mpgAudioVersion = 2
 Case 3:      mpgAudioVersion = 1
 Case Else:   mpgAudioVersion = 0
End Select


tempLong = 0
If MP3_GetBit(numLONG, 18) Then MP3_SetBit tempLong, 1
If MP3_GetBit(numLONG, 17) Then MP3_SetBit tempLong, 0
Select Case tempLong
 Case 1:      mpgLayerDesc = 3
 Case 2:      mpgLayerDesc = 2
 Case 3:      mpgLayerDesc = 1
 Case Else:   mpgAudioVersion = 0
End Select

tempLong = 0
If MP3_GetBit(numLONG, 15) Then MP3_SetBit tempLong, 3
If MP3_GetBit(numLONG, 14) Then MP3_SetBit tempLong, 2
If MP3_GetBit(numLONG, 13) Then MP3_SetBit tempLong, 1
If MP3_GetBit(numLONG, 12) Then MP3_SetBit tempLong, 0
If mpgAudioVersion = 1 And mpgLayerDesc = 1 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 32
   Case 2:      mpgBitsPerSecond = 64
   Case 3:      mpgBitsPerSecond = 96
   Case 4:      mpgBitsPerSecond = 128
   Case 5:      mpgBitsPerSecond = 160
   Case 6:      mpgBitsPerSecond = 192
   Case 7:      mpgBitsPerSecond = 224
   Case 8:      mpgBitsPerSecond = 256
   Case 9:      mpgBitsPerSecond = 288
   Case 10:     mpgBitsPerSecond = 320
   Case 11:     mpgBitsPerSecond = 352
   Case 12:     mpgBitsPerSecond = 384
   Case 13:     mpgBitsPerSecond = 416
   Case 14:     mpgBitsPerSecond = 448
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
ElseIf mpgAudioVersion = 1 And mpgLayerDesc = 2 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 32
   Case 2:      mpgBitsPerSecond = 48
   Case 3:      mpgBitsPerSecond = 56
   Case 4:      mpgBitsPerSecond = 64
   Case 5:      mpgBitsPerSecond = 80
   Case 6:      mpgBitsPerSecond = 96
   Case 7:      mpgBitsPerSecond = 112
   Case 8:      mpgBitsPerSecond = 128
   Case 9:      mpgBitsPerSecond = 160
   Case 10:     mpgBitsPerSecond = 192
   Case 11:     mpgBitsPerSecond = 224
   Case 12:     mpgBitsPerSecond = 256
   Case 13:     mpgBitsPerSecond = 320
   Case 14:     mpgBitsPerSecond = 384
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
ElseIf mpgAudioVersion = 1 And mpgLayerDesc = 3 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 32
   Case 2:      mpgBitsPerSecond = 40
   Case 3:      mpgBitsPerSecond = 48
   Case 4:      mpgBitsPerSecond = 56
   Case 5:      mpgBitsPerSecond = 64
   Case 6:      mpgBitsPerSecond = 80
   Case 7:      mpgBitsPerSecond = 96
   Case 8:      mpgBitsPerSecond = 112
   Case 9:      mpgBitsPerSecond = 128
   Case 10:     mpgBitsPerSecond = 160
   Case 11:     mpgBitsPerSecond = 192
   Case 12:     mpgBitsPerSecond = 224
   Case 13:     mpgBitsPerSecond = 256
   Case 14:     mpgBitsPerSecond = 320
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
ElseIf mpgAudioVersion = 2 And mpgLayerDesc = 1 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 32
   Case 2:      mpgBitsPerSecond = 48
   Case 3:      mpgBitsPerSecond = 56
   Case 4:      mpgBitsPerSecond = 64
   Case 5:      mpgBitsPerSecond = 80
   Case 6:      mpgBitsPerSecond = 96
   Case 7:      mpgBitsPerSecond = 112
   Case 8:      mpgBitsPerSecond = 128
   Case 9:      mpgBitsPerSecond = 144
   Case 10:     mpgBitsPerSecond = 160
   Case 11:     mpgBitsPerSecond = 176
   Case 12:     mpgBitsPerSecond = 192
   Case 13:     mpgBitsPerSecond = 224
   Case 14:     mpgBitsPerSecond = 256
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
ElseIf mpgAudioVersion = 2 And mpgLayerDesc = 2 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 8
   Case 2:      mpgBitsPerSecond = 16
   Case 3:      mpgBitsPerSecond = 24
   Case 4:      mpgBitsPerSecond = 32
   Case 5:      mpgBitsPerSecond = 40
   Case 6:      mpgBitsPerSecond = 48
   Case 7:      mpgBitsPerSecond = 56
   Case 8:      mpgBitsPerSecond = 64
   Case 9:      mpgBitsPerSecond = 80
   Case 10:     mpgBitsPerSecond = 96
   Case 11:     mpgBitsPerSecond = 112
   Case 12:     mpgBitsPerSecond = 128
   Case 13:     mpgBitsPerSecond = 144
   Case 14:     mpgBitsPerSecond = 160
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
ElseIf mpgAudioVersion = 2 And mpgLayerDesc = 3 Then
  Select Case tempLong
   Case 1:      mpgBitsPerSecond = 8
   Case 2:      mpgBitsPerSecond = 16
   Case 3:      mpgBitsPerSecond = 24
   Case 4:      mpgBitsPerSecond = 32
   Case 5:      mpgBitsPerSecond = 40
   Case 6:      mpgBitsPerSecond = 48
   Case 7:      mpgBitsPerSecond = 56
   Case 8:      mpgBitsPerSecond = 64
   Case 9:      mpgBitsPerSecond = 80
   Case 10:     mpgBitsPerSecond = 96
   Case 11:     mpgBitsPerSecond = 112
   Case 12:     mpgBitsPerSecond = 128
   Case 13:     mpgBitsPerSecond = 144
   Case 14:     mpgBitsPerSecond = 160
   Case Else:   mpgBitsPerSecond = 0
  End Select
  
End If
mpgBitsPerSecond = mpgBitsPerSecond * 1000


tempLong = 0
If MP3_GetBit(numLONG, 11) Then MP3_SetBit tempLong, 1
If MP3_GetBit(numLONG, 10) Then MP3_SetBit tempLong, 0
Select Case tempLong
 Case 0:
              If mpgAudioVersion = 1 Then
                mpgSamplesPerSecond = 44100
              ElseIf mpgAudioVersion = 2 Then
                mpgSamplesPerSecond = 22050
              ElseIf mpgAudioVersion = 2.5 Then
                mpgSamplesPerSecond = 11025
              End If
 Case 1:
              If mpgAudioVersion = 1 Then
                mpgSamplesPerSecond = 48000
              ElseIf mpgAudioVersion = 2 Then
                mpgSamplesPerSecond = 24000
              ElseIf mpgAudioVersion = 2.5 Then
                mpgSamplesPerSecond = 12000
              End If
 Case 2:
              If mpgAudioVersion = 1 Then
                mpgSamplesPerSecond = 32000
              ElseIf mpgAudioVersion = 2 Then
                mpgSamplesPerSecond = 16000
              ElseIf mpgAudioVersion = 2.5 Then
                mpgSamplesPerSecond = 8000
              End If
              
 Case Else:   mpgSamplesPerSecond = 0
End Select

Dim tempPadding As Long
If MP3_GetBit(numLONG, 9) Then
  tempPadding = 1
End If

tempLong = 0
If MP3_GetBit(numLONG, 7) Then MP3_SetBit tempLong, 1
If MP3_GetBit(numLONG, 6) Then MP3_SetBit tempLong, 0
Select Case tempLong
 Case 0:      mpgChannelsPerSample = 2
 Case 1:      mpgChannelsPerSample = 2
 Case 2:      mpgChannelsPerSample = 2
 Case 3:      mpgChannelsPerSample = 1
 Case Else:   mpgChannelsPerSample = 0
End Select

mpgCopyRight = MP3_GetBit(numLONG, 3)

If openFileNumber = -1 Then Close #fNum

If mpgLayerDesc = 1 Then
  mp3FrameLength = Fix(12 * mpgBitsPerSecond / mpgSamplesPerSecond + tempPadding) * 4
Else
  mp3FrameLength = Fix(144 * mpgBitsPerSecond / mpgSamplesPerSecond) + tempPadding
End If

MP3file_ReadFrame = True

Exit Function

FileError:
 If openFileNumber = -1 Then Close #fNum
 MP3file_ReadFrame = False
 mp3FrameLength = 0
 mpgAudioVersion = 0
 mpgLayerDesc = 0
 mpgChannelsPerSample = 0
 mpgSamplesPerSecond = 0
 mpgBitsPerSecond = 0
 mpgCopyRight = False

End Function

Private Function ID3v2_ReadTagFrame(ByVal mp3FileName$, ByVal tagFrameOffset As Long, ByRef tagFrameLength As Long, ByRef tagFrameType As String, ByRef tagFrameIsCompressed As Boolean, Optional ByVal openFileNumber As Long = -1) As Boolean

Dim fNum As Long, bArray(0 To 9) As Byte
If openFileNumber = -1 Then
  On Error GoTo FileError
  fNum = FreeFile()
  Open mp3FileName$ For Binary As #fNum
  On Error GoTo 0
Else
  fNum = openFileNumber
End If

Get #fNum, tagFrameOffset, bArray()
If openFileNumber = -1 Then Close #fNum

Dim tempStr$: tempStr$ = String$(4, 0)

Dim i As Long
For i = 0 To 3
  Mid$(tempStr$, i + 1, 1) = Chr$(bArray(i))
Next i
tagFrameType$ = tempStr$

tagFrameLength = ID3v2_4BytesToLONG_SynchSafe(bArray(4), bArray(5), bArray(6), bArray(7)) + 10


ID3v2_ReadTagFrame = True

Exit Function

FileError:
 If openFileNumber = -1 Then Close #fNum
 ID3v2_ReadTagFrame = False
 tagFrameLength = 0
 tagFrameType = ""
 tagFrameIsCompressed = False
 
End Function

Private Function ID3v2_ReadTagHeader(ByVal mp3FileName$, ByVal tagOffset As Long, ByRef tagLength As Long, ByRef tagVersion As Single, ByRef tagExtendedHeaderLength As Long, ByRef tagIsUnsync As Boolean, ByRef tagHasFooter As Boolean, ByRef tagIsExperimental As Boolean, ByRef tagFrameOffset As Long, Optional ByVal openFileNumber As Long = -1) As Boolean

Dim fNum As Long, bArray(0 To 13) As Byte
If openFileNumber = -1 Then
  On Error GoTo FileError
  fNum = FreeFile()
  Open mp3FileName$ For Binary As #fNum
  On Error GoTo 0
Else
  fNum = openFileNumber
End If

Get #fNum, tagOffset, bArray()
If openFileNumber = -1 Then Close #fNum

Dim tempHasExtended As Boolean

tagLength = ID3v2_4BytesToLONG_SynchSafe(bArray(6), bArray(7), bArray(8), bArray(9)) + 10

tagVersion = bArray(3) + (bArray(4) / 10)
tagIsUnsync = MP3_GetBit(bArray(5), 7)
tempHasExtended = MP3_GetBit(bArray(5), 6)
tagIsExperimental = MP3_GetBit(bArray(5), 5)
tagHasFooter = MP3_GetBit(bArray(5), 4)

If tempHasExtended = False Then
  tagExtendedHeaderLength = 0
  tagFrameOffset = tagOffset + 10
Else
  tagExtendedHeaderLength = ID3v2_4BytesToLONG_SynchSafe(bArray(10), bArray(11), bArray(12), bArray(13))
  tagFrameOffset = tagOffset + 20
End If

If tagHasFooter <> False Then tagLength = tagLength + 10

ID3v2_ReadTagHeader = True

Exit Function

FileError:
 If openFileNumber = -1 Then Close #fNum
 ID3v2_ReadTagHeader = False
 tagLength = 0
 tagVersion = 0
 tagExtendedHeaderLength = 0
 tagIsUnsync = False
 tagIsExperimental = False
 tagHasFooter = False
 
   
End Function


Private Function MP3_GetBit(ByVal aNumber As Long, ByVal bitNumber As Long) As Boolean

Dim expVal As Long
expVal = 2 ^ bitNumber

If (aNumber And expVal) = expVal Then
  MP3_GetBit = True
Else
  MP3_GetBit = False
End If

End Function

Private Sub MP3_SetBit(ByRef aNumber As Long, ByVal bitNumber As Long)

Dim expVal As Long
expVal = 2 ^ bitNumber

aNumber = (aNumber Or expVal)

End Sub

Public Function MP3file_RemoveTags(ByVal mp3FileName$, ByVal remID3v1 As Boolean, ByVal remID3v2 As Boolean, ByVal tempFileName$) As Boolean

If remID3v1 = False And remID3v2 = False Then
  MP3file_RemoveTags = True
  Exit Function
End If

Dim startOffset As Long, numBytesToCopy As Long
If remID3v2 <> False Then
  startOffset = MP3file_FindFirstFrameOffset(mp3FileName$)
Else
  startOffset = 1
End If

Dim fLen As Long
fLen = FileLen(mp3FileName$)

numBytesToCopy = fLen - startOffset + 1

If remID3v1 <> False And MP3read_HasTag_ID3v1(mp3FileName$) <> False Then
  numBytesToCopy = numBytesToCopy - 128
End If


FileCopy mp3FileName$, tempFileName$


Dim mp3BytesRead As Long:  mp3BytesRead = 0

Dim mp3FNum As Long, mp3Offset As Long
Dim outFNum As Long, outOffset As Long

mp3FNum = FreeFile()
Open tempFileName$ For Binary As #mp3FNum
mp3Offset = startOffset

outFNum = FreeFile()
Open mp3FileName$ For Output As #outFNum
Close #outFNum
Open mp3FileName$ For Binary As #outFNum
outOffset = 1

Dim byteBuffer() As Byte, BufferSize As Long, defBufferSize As Long
defBufferSize = 32000
ReDim byteBuffer(0 To defBufferSize - 1)
BufferSize = defBufferSize

Do
  If numBytesToCopy - mp3BytesRead > defBufferSize Then
    
  Else
    BufferSize = numBytesToCopy - mp3BytesRead
    ReDim byteBuffer(0 To BufferSize - 1)
  End If
  Get #mp3FNum, mp3Offset, byteBuffer()
  Put #outFNum, outOffset, byteBuffer()
  
  mp3BytesRead = mp3BytesRead + BufferSize
  
  mp3Offset = mp3Offset + BufferSize
  outOffset = outOffset + BufferSize
  
  If mp3BytesRead >= numBytesToCopy Then Exit Do
Loop


Close #outFNum
Close #mp3FNum

MP3file_RemoveTags = True

On Error Resume Next
Kill tempFileName$

Exit Function



FileError:
 Close #outFNum
 Close #mp3FNum
 MP3file_RemoveTags = False


End Function






Public Function MP3file_SetTagInfo_ID3v1(ByVal mp3FileName$, ByVal songTitle$, ByVal songArtist$, ByVal songAlbum$, ByVal songYear As Long, ByVal songComment$, ByVal songTrackNumber As Long, ByVal songGenreCode As Long) As Boolean

If songTrackNumber > 255 Or songTrackNumber < 0 Then songTrackNumber = 0
If songGenreCode > 255 Or songGenreCode < 0 Then songGenreCode = 12   'Other

Dim outStr$
outStr$ = ID3v1_BuildTagString(songTitle$, songArtist$, songAlbum$, songYear, songComment$, songTrackNumber, songGenreCode)

If Len(outStr$) <> 128 Then GoTo FileError

Dim fNum As Long, fOffset As Long, fLen As Long

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

fLen = LOF(fNum)
fOffset = fLen - 127

Dim tempStr$:   tempStr$ = String$(3, 0)
Get #fNum, fOffset, tempStr$
If tempStr$ <> "TAG" Then fOffset = fLen + 1
Put #fNum, fOffset, outStr$
Close #fNum
 
MP3file_SetTagInfo_ID3v1 = True
Exit Function


FileError:
 Close #fNum
 MP3file_SetTagInfo_ID3v1 = False


End Function


Public Function MP3file_SetTagInfo_ID3v2(ByVal mp3FileName$, ByVal songTitle$, ByVal songArtist$, ByVal songAlbum$, ByVal songYear As Long, ByVal songComment$, ByVal songTrackNumber As Long, ByVal songGenre$, ByVal songComposer$, ByVal songOriginalArtist$, ByVal songCopyright$, ByVal songURL$, ByVal songEncodedBy$, ByVal tempFileName$) As Boolean


Dim outStr$
outStr$ = ID3v2_BuildTagString(songTitle$, songArtist$, songAlbum$, songYear, songComment$, songTrackNumber, songGenre$, songComposer$, songOriginalArtist$, songCopyright$, songURL$, songEncodedBy$)

Dim startOffset As Long, outOffset As Long

Dim mp3FNum As Long
startOffset = MP3file_FindFirstFrameOffset(mp3FileName$)
outOffset = Len(outStr$) + 1

FileCopy mp3FileName$, tempFileName$

On Error GoTo FileError
mp3FNum = FreeFile()
Open mp3FileName$ For Output As #mp3FNum
Close #mp3FNum

Dim tempFNum As Long
tempFNum = FreeFile()
Open tempFileName$ For Binary As #tempFNum

mp3FNum = FreeFile()
Open mp3FileName$ For Binary As #mp3FNum

On Error GoTo 0


Put #mp3FNum, 1, outStr$


Dim tempOffset As Long:      tempOffset = startOffset
Dim tempBytesRead As Long:   tempBytesRead = 0
Dim numBytesToCopy As Long:  numBytesToCopy = LOF(tempFNum) - startOffset + 1

Dim byteBuffer() As Byte, BufferSize As Long, defBufferSize As Long
defBufferSize = 32000
ReDim byteBuffer(0 To defBufferSize - 1)
BufferSize = defBufferSize

Do
  If numBytesToCopy - tempBytesRead > defBufferSize Then
    
  Else
    BufferSize = numBytesToCopy - tempBytesRead
    ReDim byteBuffer(0 To BufferSize - 1)
  End If
  Get #tempFNum, tempOffset, byteBuffer()
  Put #mp3FNum, outOffset, byteBuffer()
  
  tempBytesRead = tempBytesRead + BufferSize
  
  tempOffset = tempOffset + BufferSize
  outOffset = outOffset + BufferSize
  
  If tempBytesRead >= numBytesToCopy Then Exit Do
Loop

Close #tempFNum
Close #mp3FNum
  
On Error Resume Next
Kill tempFileName$
  
MP3file_SetTagInfo_ID3v2 = True
Exit Function


FileError:
 Close #tempFNum
 Close #mp3FNum
 MP3file_SetTagInfo_ID3v2 = False


End Function



Public Function MP3read_HasTag_ID3v1(ByVal mp3FileName$) As Boolean

Dim fNum As Long, fOffset As Long, fLen As Long

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

fLen = LOF(fNum)
fOffset = fLen - 127

Dim tempStr$:  tempStr$ = String$(3, 0)
Get #fNum, fOffset, tempStr$

Close #fNum

If tempStr$ = "TAG" Then
  MP3read_HasTag_ID3v1 = True
Else
  MP3read_HasTag_ID3v1 = False
End If

Exit Function


FileError:
 Close #fNum
 MP3read_HasTag_ID3v1 = False


End Function

Public Function MP3read_HasTag_ID3v2(ByVal mp3FileName$) As Boolean

Dim fNum As Long

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

Dim tempStr$:  tempStr$ = String$(3, 0)
Get #fNum, 1, tempStr$

Close #fNum

If tempStr$ = "ID3" Then
  MP3read_HasTag_ID3v2 = True
Else
  MP3read_HasTag_ID3v2 = False
End If

Exit Function


FileError:
 Close #fNum
 MP3read_HasTag_ID3v2 = False

End Function

Public Function MP3read_GetAudioStreamInfo(ByVal mp3FileName$, ByRef mp3ChannelsPerSample As Long, ByRef mp3SamplesPerSecond As Long, ByRef mp3BitsPerSecond As Long, ByRef mp3Copyrighted As Boolean, ByRef mp3DurationSec As Double, ByRef mp3Compression$) As Boolean


Dim fNum As Long, fOffset As Long, fLen As Long
fOffset = MP3file_FindFirstFrameOffset(mp3FileName$)

If fOffset = -1 Then GoTo FileError

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

fLen = LOF(fNum)

Dim tempAudioEncoding As Single
Dim tempLayerDesc     As Long

Dim TorF As Boolean
TorF = MP3file_ReadFrame(mp3FileName$, fOffset, 0, tempAudioEncoding, tempLayerDesc, mp3ChannelsPerSample, mp3SamplesPerSecond, mp3BitsPerSecond, mp3Copyrighted, fNum)

Dim tempFrameCount As Long, tempFrameLen As Long, tempBPS As Long
Do
  If fOffset > fLen Then Exit Do
  TorF = MP3file_ReadFrame(mp3FileName$, fOffset, tempFrameLen, 0, 0, 0, 0, tempBPS, False, fNum)
  fOffset = fOffset + tempFrameLen
  tempFrameCount = tempFrameCount + 1
  If TorF <> True Then Exit Do
Loop

mp3DurationSec = tempFrameCount / 38.5

mp3Compression$ = "MPEG-" & tempAudioEncoding & "  Layer-" & String$(tempLayerDesc, "I")

Close #fNum
MP3read_GetAudioStreamInfo = True

Exit Function


FileError:
 Close #fNum
 
 
End Function


Private Function MP3_4BytesToLONG(ByVal ByteHigh As Byte, ByVal ByteMidH As Byte, ByVal ByteMidL As Byte, ByVal ByteLow As Byte) As Long


Dim longHigh As Long, longMidH As Long, longMidL As Long, longLow As Long
longHigh = ByteHigh
longMidH = ByteMidH
longMidL = ByteMidL
longLow = ByteLow

Dim outVal As Long

If longHigh > 127 Then
  longHigh = longHigh Xor 128
  outVal = (longHigh * 16777216) + (longMidH * 65536) + (longMidL * 256) + longLow
  outVal = outVal - 2147483648#
Else
  outVal = (longHigh * 16777216) + (longMidH * 65536) + (longMidL * 256) + longLow
End If

MP3_4BytesToLONG = outVal

End Function



Private Function ID3v2_4BytesToLONG_SynchSafe(ByVal ByteHigh As Byte, ByVal ByteMidH As Byte, ByVal ByteMidL As Byte, ByVal ByteLow As Byte) As Long

Dim longHigh As Long, longMidH As Long, longMidL As Long, longLow As Long
longHigh = ByteHigh
longMidH = ByteMidH
longMidL = ByteMidL
longLow = ByteLow

Dim outVal As Long
outVal = (longHigh * 2097152) + (longMidH * 16384) + (longMidL * 128) + longLow

ID3v2_4BytesToLONG_SynchSafe = outVal

End Function

Private Sub ID3v2_4BytesFromLONG_SynchSafe(ByVal longValue As Long, ByRef ByteHigh As Long, ByRef ByteMidH As Long, ByRef ByteMidL As Long, ByRef ByteLow As Long)

ByteLow = longValue Mod 128
longValue = (longValue - ByteLow) \ 128

ByteMidL = longValue Mod 128
longValue = (longValue - ByteMidL) \ 128

ByteMidH = longValue Mod 128
longValue = (longValue - ByteMidH) \ 128

ByteHigh = longValue Mod 128
longValue = (longValue - ByteHigh) \ 128

End Sub

Public Function MP3read_GetTagInfo_ID3v1(ByVal mp3FileName$, ByRef songTitle$, ByRef songArtist$, ByRef songAlbum$, ByRef songYear As Long, ByRef songComment$, ByRef songTrackNumber As Long, ByRef songGenreCode As Long) As Boolean

Dim fNum As Long, fOffset As Long, fLen As Long

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

fLen = LOF(fNum)
fOffset = fLen - 127

Dim tempStr$
tempStr$ = String$(128, 0)
Get #fNum, fOffset, tempStr$
Close #fNum

Dim tempComment$

songTitle$ = MP3_TrimString(Mid$(tempStr$, 4, 30))
songArtist$ = MP3_TrimString(Mid$(tempStr$, 34, 30))
songAlbum$ = MP3_TrimString(Mid$(tempStr$, 64, 30))
songYear = CLng(Val(Mid$(tempStr$, 94, 4)))

tempComment$ = Mid$(tempStr$, 98, 30)
songComment$ = MP3_TrimString(tempComment$)

songTrackNumber = 0
If Mid$(tempComment$, 29, 1) = Chr$(0) Then
  If Mid$(tempComment$, 30, 1) <> Chr$(0) Then
    songTrackNumber = Asc(Mid$(tempComment$, 30, 1))
  End If
End If
songGenreCode = Asc(Right$(tempStr$, 1))

MP3read_GetTagInfo_ID3v1 = True

Exit Function


FileError:
 Close #fNum
 MP3read_GetTagInfo_ID3v1 = False
 songTitle$ = ""
 songArtist$ = ""
 songAlbum$ = ""
 songYear = 0
 songComment$ = ""
 songTrackNumber = 0
 songGenreCode = 0

End Function


Public Function MP3read_GetTagInfo_ID3v2(ByVal mp3FileName$, ByRef songTitle$, ByRef songArtist$, ByRef songAlbum$, ByRef songYear$, ByRef songComment$, ByRef songTrackNumber As Long, ByRef songGenre As String, ByRef songComposer$, ByRef songOriginalArtist$, ByRef songCopyright$, ByRef songURL$, ByRef songEncodedBy$) As Boolean

songTitle$ = ""
songArtist$ = ""
songAlbum$ = ""
songYear = 0
songComment$ = ""
songTrackNumber = 0
songGenre = ""

songComposer$ = ""
songOriginalArtist$ = ""
songCopyright$ = ""
songURL$ = ""
songEncodedBy$ = ""

Dim fNum As Long, fOffset As Long, fLen As Long

On Error GoTo FileError
fNum = FreeFile()
Open mp3FileName$ For Binary As #fNum
On Error GoTo 0

fLen = LOF(fNum)
fOffset = 1

Dim tempFrameOffset As Long, tempTagLen As Long
Dim tempYear$, tempTrack$, tempGenre$

Dim tempStr$:  tempStr$ = String$(3, 0)
Get #fNum, fOffset, tempStr$
If tempStr$ <> "ID3" Then
  GoTo FileError
End If

ID3v2_ReadTagHeader mp3FileName$, fOffset, tempTagLen, 0, 0, False, False, False, tempFrameOffset, fNum
fOffset = tempFrameOffset

Dim frameLen As Long, frameType$
Dim id3v2bytes() As Byte

Do
  If fOffset > tempTagLen Then Exit Do

  ID3v2_ReadTagFrame mp3FileName$, fOffset, frameLen, frameType$, False, fNum
  
  If frameType$ = ID3v2_TIT2 Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTIT2info id3v2bytes(), songTitle$
  
  ElseIf frameType$ = ID3v2_TPE1 Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTPE1info id3v2bytes(), songArtist$
  
  ElseIf frameType$ = ID3v2_TALB Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTALBinfo id3v2bytes(), songAlbum$
  
  ElseIf frameType$ = ID3v2_TYER Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTYERinfo id3v2bytes(), tempYear$
    songYear = CLng(Val(tempYear$))
  
  songYear$ = Str$(songYear)
  
  ElseIf frameType$ = ID3v2_COMM Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetCOMMinfo id3v2bytes(), songComment$
  
  ElseIf frameType$ = ID3v2_TRCK Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTRCKinfo id3v2bytes(), tempTrack$
    songTrackNumber = CLng(Val(tempTrack$))
  
  ElseIf frameType$ = ID3v2_TCON Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTCONinfo id3v2bytes(), tempGenre$
    If Mid$(tempGenre$, 1, 1) = "(" Then
      songGenre$ = MP3_GetGenreString(CLng(Val(Mid$(tempGenre$, 2, 3))))
    Else
      songGenre$ = tempGenre$
    End If
    
    
  ElseIf frameType$ = ID3v2_TCOM Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTCOMinfo id3v2bytes(), songComposer$
    
  ElseIf frameType$ = ID3v2_TOPE Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTOPEinfo id3v2bytes(), songOriginalArtist$
    
  ElseIf frameType$ = ID3v2_TCOP Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTCOPinfo id3v2bytes(), songCopyright$
    
  ElseIf frameType$ = ID3v2_WXXX Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetWXXXinfo id3v2bytes(), songURL$
    
  ElseIf frameType$ = ID3v2_TENC Then
    ReDim id3v2bytes(0 To frameLen - 1)
    Get #fNum, fOffset, id3v2bytes()
    ID3v2_GetTENCinfo id3v2bytes(), songEncodedBy$
    
  End If
  
  fOffset = fOffset + frameLen
Loop

Close #fNum
MP3read_GetTagInfo_ID3v2 = True

Exit Function


FileError:
 Close #fNum
 MP3read_GetTagInfo_ID3v2 = False
 songTitle$ = ""
 songArtist$ = ""
 songAlbum$ = ""
 songYear = 0
 songComment$ = ""
 songTrackNumber = 0
 songGenre = ""


End Function

