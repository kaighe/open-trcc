@echo off

mkdir "build/include"
mkdir "build/lib"
mkdir "temp"

g++ -Iinclude -Llib -c -o temp/trcc.o src/trcc.cpp -l"usb-1.0"
g++ -Iinclude -Llib -o build/lib/trcc.dll temp/trcc.o -s -shared -Wl,--subsystem,windows -l"usb-1.0"
@REM ar rcs build/libtrcc.a temp/trcc.o