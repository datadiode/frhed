Option Explicit
''
' This script creates the master POT file (en-US.pot).
'
' Copyright (C) 2007 by Tim Gerundt
' Released under the "GNU General Public License"
'
' ID line follows -- this is updated by SVN
' $Id: CreateMasterPotFile.vbs 473 2009-04-09 16:30:19Z gerundt $

Const ForReading = 1

Const NO_BLOCK = 0
Const MENU_BLOCK = 1
Const DIALOGEX_BLOCK = 2
Const STRINGTABLE_BLOCK = 3
Const VERSIONINFO_BLOCK = 4
Const ACCELERATORS_BLOCK = 5
Const TEXTINCLUDE_BLOCK = 6
Const BITMAP_BLOCK = 7

Dim oFSO, bRunFromCmd

Set oFSO = CreateObject("Scripting.FileSystemObject")

bRunFromCmd = False
If LCase(oFSO.GetFileName(Wscript.FullName)) = "cscript.exe" Then
  bRunFromCmd = True
End If

Call Main

''
' ...
Sub Main
  Dim oStrings, sCodePage
  Dim StartTime, EndTime, Seconds
  Dim bNecessary, oFile
  
  StartTime = Time
  
  InfoBox "Creating POT file from heksedit.rc...", 3
  
  bNecessary = True
  If (oFSO.FileExists("en-US.pot") = True) And (oFSO.FileExists("heksedit.rc") = True) Then 'If the POT and RC file exists...
    bNecessary = GetArchiveBit("../../Frhed/heksedit.rc") Or GetArchiveBit("en-US.pot") Or GetArchiveBit("heksedit.rc") 'RCs or POT file changed?
  End If
  
  If (bNecessary = True) Then 'If update necessary...
    Set oStrings = GetStringsFromRcFile("../../Frhed/heksedit.rc", sCodePage)
    CreateMasterPotFile "en-US.pot", oStrings, sCodePage
    SetArchiveBit "../../Frhed/heksedit.rc", False
    SetArchiveBit "en-US.pot", False
    SetArchiveBit "heksedit.rc", False
    For Each oFile In oFSO.GetFolder(".").Files 'For all files in the current folder...
      If (LCase(oFSO.GetExtensionName(oFile.Name)) = "po") Then 'If a PO file...
        SetArchiveBit oFile.Path, True
      End If
    Next

    EndTime = Time
    Seconds = DateDiff("s", StartTime, EndTime)
    
    InfoBox "POT file created, after " & Seconds & " second(s).", 10
  Else 'If update NOT necessary...
    InfoBox "POT file already up-to-date.", 10
  End If
End Sub

''
' ...
Class CString
  Dim Comment, References, Context, Id, Str
End Class

''
' ...
Function GetStringsFromRcFile(ByVal sRcFilePath, ByRef sCodePage)
  Dim oBlacklist, oStrings, oString, oRcFile, sLine, iLine
  Dim sRcFileName, iBlockType, sReference, sString, sComment, sContext, oMatch, sTemp, sKey
  Dim oLcFile, sLcLine, fContinuation

  Set oBlacklist = GetStringBlacklist("StringBlacklist.txt")
  
  Set oStrings = CreateObject("Scripting.Dictionary")
  
  If (oFSO.FileExists(sRcFilePath) = True) Then 'If the RC file exists...
    sRcFileName = oFSO.GetFileName(sRcFilePath)
    iLine = 0
    iBlockType = NO_BLOCK
    sCodePage = ""
    Set oRcFile = oFSO.OpenTextFile(sRcFilePath, ForReading)
    Set oLcFile = oFSO.CreateTextFile("heksedit.rc", True)
    Do Until oRcFile.AtEndOfStream = True 'For all lines...
      sLcLine = oRcFile.ReadLine
      sLine = Trim(sLcLine)
      sLine = Replace(sLine, vbTab, " ")
      iLine = iLine + 1
      
      sReference = sRcFileName & ":" & iLine
      sString = ""
      sComment = ""
      sContext = ""
      
      If fContinuation Then
        ' Nothing to do
      ElseIf (Left(sLine, 2) = "//") Then 'If comment line...
        sLine = ""
        'IGNORE FOR SPEEDUP!
      ElseIf InStr(sLine, " TEXTINCLUDE") > 0 Then 'TEXTINCLUDE...
        iBlockType = TEXTINCLUDE_BLOCK
      ElseIf InStr(sLine, " MENU") > 0 And InStr(sLine, "IDR_") > 0 Then 'MENU...
        iBlockType = MENU_BLOCK
      ElseIf InStr(sLine, " DIALOG") > 0 Then 'DIALOG(EX)...
        iBlockType = DIALOGEX_BLOCK
      ElseIf InStr(sLine, "STRINGTABLE") > 0 Then 'STRINGTABLE...
        iBlockType = STRINGTABLE_BLOCK
      ElseIf InStr(sLine, " VERSIONINFO") > 0 Then 'VERSIONINFO...
        iBlockType = VERSIONINFO_BLOCK
      ElseIf InStr(sLine, " ACCELERATORS") > 0 Then 'ACCELERATORS...
        iBlockType = ACCELERATORS_BLOCK
      ElseIf InStr(sLine, " BITMAP ") > 0 Then 'BITMAP...
        iBlockType = BITMAP_BLOCK
        sLcLine = "//" & sLcLine
      ElseIf (sLine = "BEGIN") Then 'BEGIN...
        'IGNORE FOR SPEEDUP!
      ElseIf (sLine = "END") Then 'END...
        If (iBlockType = STRINGTABLE_BLOCK) Or (iBlockType = TEXTINCLUDE_BLOCK) Then 'If inside STRINGTABLE or TEXTINCLUDE...
          iBlockType = NO_BLOCK
        End If
      ElseIf sLine <> "" Then 'If NOT empty line...
        Select Case iBlockType
          Case NO_BLOCK:
            If FoundRegExpMatch(sLine, "LANGUAGE (LANG_\w*, SUBLANG_\w*)", oMatch) Then 'LANGUAGE...
              sString = oMatch.SubMatches(0)
              sComment = "LANGUAGE, SUBLANGUAGE"
            ElseIf FoundRegExpMatch(sLine, "code_page\(([\d]+)\)", oMatch) Then 'code_page...
              sString = oMatch.SubMatches(0)
              sComment = "Codepage"
              sCodePage = oMatch.SubMatches(0)
            End If
            
          Case MENU_BLOCK, DIALOGEX_BLOCK, STRINGTABLE_BLOCK:
            If InStr(sLine, """") > 0 Then 'If quote found (for speedup)...
              '--------------------------------------------------------------------------------
              ' Replace 1st string literal only - 2nd string literal specifies control class!
              '--------------------------------------------------------------------------------
              If FoundRegExpMatch(sLine, """((?:""""|[^""])*)""", oMatch) Then 'String...
                sTemp = oMatch.SubMatches(0)
                If (sTemp <> "") And (oBlacklist.Exists(sTemp) = False) Then 'If NOT blacklisted...
                  sLcLine = Replace(sLcLine, """" & sTemp & """", """" & sReference & """", 1, 1)
                  sString = Replace(sTemp, """""", "\""")
                  If FoundRegExpMatch(sLine, "//#\. (.*?)$", oMatch) Then 'If found a comment for the translators...
                    sComment = Trim(oMatch.SubMatches(0))
                  ElseIf FoundRegExpMatch(sLine, "//msgctxt (.*?)$", oMatch) Then 'If found a context for the translation...
                    sContext = Trim(oMatch.SubMatches(0))
                    sComment = sContext
                  End If
                End If
              End If
            End If
            
          Case VERSIONINFO_BLOCK:
            If FoundRegExpMatch(sLine, "BLOCK ""([0-9A-F]+)""", oMatch) Then 'StringFileInfo.Block...
              sString = oMatch.SubMatches(0)
              sComment = "StringFileInfo.Block"
            ElseIf FoundRegExpMatch(sLine, "VALUE ""Comments"", ""(.*?)\\?0?""", oMatch) Then 'StringFileInfo.Comments...
              sString = oMatch.SubMatches(0)
              sComment = "You should use a string like ""Translated by "" followed by the translator names for this string. It is ONLY VISIBLE in the StringFileInfo.Comments property from the final resource file!"
            ElseIf FoundRegExpMatch(sLine, "VALUE ""Translation"", (.*?)$", oMatch) Then 'VarFileInfo.Translation...
              sString = oMatch.SubMatches(0)
              sComment = "VarFileInfo.Translation"
            End If
            
        End Select
      End If
      
      If (sString <> "") Then
        sKey = sContext & sString
        Set oString = New CString
        If (oStrings.Exists(sKey) = True) Then 'If the key is already used...
          Set oString = oStrings(sKey)
        End If
        If (sComment <> "") Then
          oString.Comment = sComment
        End If
        If (oString.References <> "") Then
          oString.References = oString.References & vbTab & sReference
        Else
          oString.References = sReference
        End If
        oString.Context = sContext
        oString.Id = sString
        oString.Str = ""
        
        If (oStrings.Exists(sKey) = True) Then 'If the key is already used...
          Set oStrings(sKey) = oString
        Else 'If the key is NOT already used...
          oStrings.Add sContext & sString, oString
        End If
      End If
      oLcFile.WriteLine sLcLine
      fContinuation = sLine <> "" And InStr(",|", Right(sLine, 1)) <> 0
    Loop
    oLcFile.WriteLine "en-US.pot RCDATA ""en-US.pot"""
    oRcFile.Close
    oLcFile.Close
  End If
  Set GetStringsFromRcFile = oStrings
End Function

''
' ...
Function GetStringBlacklist(ByVal sTxtFilePath)
  Dim oBlacklist, oTxtFile, sLine
  
  Set oBlacklist = CreateObject("Scripting.Dictionary")
  
  If (oFSO.FileExists(sTxtFilePath) = True) Then 'If the blacklist file exists...
    Set oTxtFile = oFSO.OpenTextFile(sTxtFilePath, ForReading)
    Do Until oTxtFile.AtEndOfStream = True 'For all lines...
      sLine = Trim(oTxtFile.ReadLine)
      
      If (sLine <> "") Then
        If (oBlacklist.Exists(sLine) = False) Then 'If the key is NOT already used...
          oBlacklist.Add sLine, True
        End If
      End If
    Loop
    oTxtFile.Close
  End If
  Set GetStringBlacklist = oBlacklist
End Function

''
' ...
Sub CreateMasterPotFile(ByVal sPotPath, ByVal oStrings, ByVal sCodePage)
  Dim oPotFile, sKey, oString, aReferences, i
  
  Set oPotFile = oFSO.CreateTextFile(sPotPath, True)
  
  oPotFile.WriteLine "# This file is part of Frhed <http://frhed.sourceforge.net/>"
  oPotFile.WriteLine "# Released under the ""GNU General Public License"""
  oPotFile.WriteLine "#"
  oPotFile.WriteLine "# ID line follows -- this is updated by SVN"
  oPotFile.WriteLine "# $" & "Id: " & "$"
  oPotFile.WriteLine "#"
  oPotFile.WriteLine "msgid """""
  oPotFile.WriteLine "msgstr """""
  oPotFile.WriteLine """Project-Id-Version: Frhed\n"""
  oPotFile.WriteLine """Report-Msgid-Bugs-To: http://sourceforge.net/tracker/?group_id=13216&atid=113216\n"""
  oPotFile.WriteLine """POT-Creation-Date: " & GetPotCreationDate() & "\n"""
  oPotFile.WriteLine """PO-Revision-Date: \n"""
  oPotFile.WriteLine """Last-Translator: \n"""
  oPotFile.WriteLine """Language-Team: English <frhed-devel@lists.sourceforge.net>\n"""
  oPotFile.WriteLine """MIME-Version: 1.0\n"""
  oPotFile.WriteLine """Content-Type: text/plain; charset=CP" & sCodePage & "\n"""
  oPotFile.WriteLine """Content-Transfer-Encoding: 8bit\n"""
  oPotFile.WriteLine """X-Poedit-Language: English\n"""
  oPotFile.WriteLine """X-Poedit-SourceCharset: CP" & sCodePage & "\n"""
  oPotFile.WriteLine """X-Poedit-Basepath: ../../FRHED\n"""
  'oPotFile.WriteLine """X-Generator: CreateMasterPotFile.vbs\n"""
  oPotFile.WriteLine
  For Each sKey In oStrings.Keys 'For all strings...
    Set oString = oStrings(sKey)
    If (oString.Comment <> "") Then 'If comment exists...
      oPotFile.WriteLine "#. " & oString.Comment
    End If
    aReferences = Split(oString.References, vbTab)
    For i = LBound(aReferences) To UBound(aReferences) 'For all references...
      oPotFile.WriteLine "#: " & aReferences(i)
    Next
    oPotFile.WriteLine "#, c-format"
    If (oString.Context <> "") Then 'If context exists...
      oPotFile.WriteLine "msgctxt """ & oString.Context & """"
    End If
    oPotFile.WriteLine "msgid """ & oString.Id & """"
    oPotFile.WriteLine "msgstr """""
    oPotFile.WriteLine
  Next
  oPotFile.Close
End Sub

''
' ...
Function FoundRegExpMatch(ByVal sString, ByVal sPattern, ByRef oMatchReturn)
  Dim oRegExp, oMatches
  
  Set oRegExp = New RegExp
  oRegExp.Pattern = sPattern
  oRegExp.IgnoreCase = True
  
  Set oMatchReturn = Nothing
  FoundRegExpMatch = False
  If oRegExp.Test(sString) Then
    Set oMatches = oRegExp.Execute(sString)
    Set oMatchReturn = oMatches(0)
    FoundRegExpMatch = True
  End If
End Function

''
' ...
Function GetPotCreationDate()
  Dim oNow, sYear, sMonth, sDay, sHour, sMinute
  
  oNow = Now()
  sYear = Year(oNow)
  sMonth = Month(oNow)
  If (sMonth < 10) Then sMonth = "0" & sMonth
  sDay = Day(oNow)
  If (sDay < 10) Then sDay = "0" & sDay
  sHour = Hour(oNow)
  If (sHour < 10) Then sHour = "0" & sHour
  sMinute = Minute(oNow)
  If (sMinute < 10) Then sMinute = "0" & sMinute
  
  GetPotCreationDate = sYear & "-" & sMonth & "-" & sDay & " " & sHour & ":" & sMinute & "+0000"
End Function

''
' ...
Function InfoBox(ByVal sText, ByVal iSecondsToWait)
  Dim oShell
  
  If (bRunFromCmd = False) Then 'If run from command line...
    Set oShell = Wscript.CreateObject("WScript.Shell")
    InfoBox = oShell.Popup(sText, iSecondsToWait, Wscript.ScriptName, 64)
  Else 'If NOT run from command line...
    Wscript.Echo sText
  End If
End Function

''
' ...
Function GetArchiveBit(ByVal sFilePath)
  Dim oFile
  GetArchiveBit = False
  If oFSO.FileExists(sFilePath) Then 'If the file exists...
    Set oFile = oFSO.GetFile(sFilePath)
    If (oFile.Attributes And 32) = 32 Then 'If archive bit set...
      GetArchiveBit = True
    End If
  End If
End Function

''
' ...
Sub SetArchiveBit(ByVal sFilePath, ByVal bValue)
  Dim oFile
  If oFSO.FileExists(sFilePath) Then 'If the file exists...
    Set oFile = oFSO.GetFile(sFilePath)
    If bValue Xor (oFile.Attributes And 32) = 32 Then 'If archive bit different...
      oFile.Attributes = oFile.Attributes Xor 32
    End If
  End If
End Sub
