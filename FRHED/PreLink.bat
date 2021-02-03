cd
echo %0
echo $(IntDir) = %1
echo $(TargetPath) = %2
REM ~ cd ..\Translations\Frhed
REM ~ cscript CreateMasterPotFile.vbs
REM ~ cscript UpdatePoFilesFromPotFile.vbs
REM ~ cd ..\..\FRHED
rc /fo%~1\lang.res /i.. ..\Translations\Frhed\heksedit.rc
mkdir %~2\..\Languages
link /DLL /NOENTRY /MACHINE:IX86 /OUT:%~2\..\Languages\heksedit.lng %~1\lang.res
editbin.exe /OSVERSION:4.0 /SUBSYSTEM:WINDOWS,4.0 %2\..\Languages\heksedit.lng
copy ..\Translations\Frhed\*.po %2\..\Languages
