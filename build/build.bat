@echo off
REM Windows (MinGW)
gcc -O2 -c vendor\miniz.c -o miniz.o
g++ -std=c++17 -O2 -o server.exe src\server.cpp miniz.o -lws2_32
echo build เสร็จ  ->  server.exe
