@ECHO OFF
REM ***************************************************************************
REM I like using windows cmd instead of msys2 shell. For some reason I have
REM difficulty running scons on msys2. Therefore I run this batch file
REM to allow me to run the esp-idf make on the windows cmd shell. Once this
REM batch file runs, I can issue "make flash" to run the esp-idf makefile.
REM Your install is probably different than mine so you need to change 
REM these paths accordingly.
REM ***************************************************************************
PATH="C:\Tools\msys32\var\opt\xtensa-esp32-elf-1.22.0-61-gab8375a-5.2.0\bin";%PATH%
PATH="C:\Tools\msys32\usr\bin";%PATH%
