Outfile "rtGCS.EXE"

InstallDir $PROGRAMFILES\rtGCS

Section

SetOutPath $INSTDIR

File /r "C:\Users\Uporabnik\Documents\GitHub\qgroundcontrol-build\release\*"

SetOutPath $INSTDIR\plugins

File /r "C:\Users\Uporabnik\Documents\GitHub\qgroundcontrol\plugins\*"

SetOutPath "$PROGRAMFILES64\FlightGear 3.4.0\data\Aircraft"

File /r "C:\Users\Uporabnik\Documents\GitHub\qgroundcontrol-build\vehicles\*"

CreateShortcut "$DESKTOP\rtGCS.lnk" "$INSTDIR\rtGCS.EXE" "$INSTDIR\rtlogo.ico"

SectionEnd

