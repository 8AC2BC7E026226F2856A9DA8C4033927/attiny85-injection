@echo off
@rem switch locale back to german
PowerShell Set-WinUserLanguageList -LanguageList de-DE -force
Powershell (New-Object System.Media.SoundPlayer "$env:windir\Media\tada.wav").PlaySync()

timeout 4
start cmd /c "net session & echo success & pause"