C:\Qt\Qt5.14.1\5.14.1\msvc2017_64\bin\windeployqt.exe TextEditor.exe
xcopy .\Qt5Core.dll                 .\TextEditor\    /C /Y
xcopy .\Qt5Gui.dll                  .\TextEditor\    /C /Y
xcopy .\Qt5Svg.dll                  .\TextEditor\    /C /Y
xcopy .\Qt5Widgets.dll              .\TextEditor\    /C /Y
xcopy .\TextEditor.exe              .\TextEditor\    /C /Y
xcopy .\iconengines                 .\TextEditor\iconengines\     /C /E /H /Y
xcopy .\imageformats                 .\TextEditor\imageformats\     /C /E /H /Y
xcopy .\platforms                 .\TextEditor\platforms\     /C /E /H /Y
xcopy .\styles                 .\TextEditor\styles\     /C /E /H /Y
xcopy .\translations                 .\TextEditor\translations\     /C /E /H /Y
"C:\Program Files\WinRAR\WinRAR.exe" a ".\TextEditor.zip" ".\TextEditor"  /Y