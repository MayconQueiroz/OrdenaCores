:: @ECHO OFF
gcc OCor.c -o OCor.exe
:: IF %ERRORLEVEL% == 0 ( OCor.exe 0.3 0.59 0.11 )
:: IF NOT %ERRORLEVEL% == 0 ( GOTO FIM )
gcc EscreveBitMap.c -o EscreveBitMap.exe
:: IF %ERRORLEVEL% == 0 ( EscreveBitMap.exe )
:FIM
