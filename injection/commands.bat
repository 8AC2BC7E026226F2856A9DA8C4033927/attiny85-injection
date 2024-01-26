@rem copy dash (ascii code: 45)
cmd /c exit 45
setx DASH %=exitcodeAscii%

@rem delete environment variable (PowerShell)
[Environment]::SetEnvironmentVariable('DASH', $null, 'User')

@rem set user locale (PowerShell)
Set-WinUserLanguageList -LanguageList de-DE -force

@rem .vbs script to run bat script (0: invisible, 1: visible)
CreateObject("Shell.Application").ShellExecute "script.bat",,"","runas",1

@rem sample .bat script
@echo off&set /p DUMMY=Hit ENTER to continue...

@rem create invisible admin shell running .bat script
cmd /k cd %temp%&echo|set /p="Visual Basic Script">script.vbs&echo|set /p="Batch Script">script.bat&script.vbs&exit

cmd /k cd %temp% & echo CreateObject("Shell.Application").ShellExecute "script.bat",,"","runas",1>script.vbs & echo set /p DUMMY=Hit ENTER to continue...>script.bat & script.vbs & exit

Powershell -Command cd %temp% | echo "this is a test" > test.txt
Powershell -Command Start-Process C:\Users\wanja\Documents\Arduino\cmd\test.bat -Verb RunAs
Powershell -Windowstyle Hidden -Command Start-Process wscript.exe -ArgumentList "C:\Users\wanja\Documents\Arduino\cmd\invisible.vbs C:\Users\wanja\Documents\Arduino\cmd\test.bat"

cmd /k cd %temp%&echo|set /p="CreateObject("Shell.Application").ShellExecute "script.bat",,"","runas",1">script.vbs&echo set /p DUMMY=Hit ENTER to continue...>script.bat&script.vbs&exit