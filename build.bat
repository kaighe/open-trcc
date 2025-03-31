@echo off

g++ -shared -Iinclude -Llib -o build/trcc.dll src/trcc.cpp -l"usb-1.0"