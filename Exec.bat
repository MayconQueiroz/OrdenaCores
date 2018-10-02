OCor.exe 0.3 0.59 0.11
IF NOT %ERRORLEVEL% == 0 ( GOTO FIM )
EscreveBitMap.exe
:FIM
SHUTDOWN /S /F
