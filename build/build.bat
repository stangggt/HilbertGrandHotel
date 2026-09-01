@echo off
REM ============================================================
REM  build.bat — Windows (MinGW / GCC)
REM  รันจาก root ของโปรเจกต์:  build\build.bat
REM ============================================================
if not exist build mkdir build

echo ==> Compiling C/C++ objects...
gcc -O2 -c vendor\miniz.c -o build\miniz.o
g++ -std=c++17 -O2 -c src\utils.cpp -o build\utils.o
g++ -std=c++17 -O2 -c src\hotel.cpp -o build\hotel.o
g++ -std=c++17 -O2 -c src\reservation.cpp -o build\reservation.o
g++ -std=c++17 -O2 -c src\user.cpp -o build\user.o
g++ -std=c++17 -O2 -c src\console_utils.cpp -o build\console_utils.o
g++ -std=c++17 -O2 -c src\tui.cpp -o build\tui.o

echo ==> Linking Web Server (build\server.exe)...
g++ -std=c++17 -O2 -c src\main.cpp -o build\main.o
g++ -o build\server.exe build\miniz.o build\utils.o build\hotel.o build\reservation.o build\user.o build\main.o -lws2_32

echo ==> Linking Terminal TUI (build\tui.exe)...
g++ -std=c++17 -O2 -c src\main_tui.cpp -o build\main_tui.o
g++ -o build\tui.exe build\miniz.o build\utils.o build\hotel.o build\reservation.o build\user.o build\console_utils.o build\tui.o build\main_tui.o -lws2_32

echo ============================================================
echo  Build เสร็จสมบูรณ์:
echo    - Web Server:    build\server.exe  (http://localhost:8093)
echo    - Terminal UI:   build\tui.exe
echo ============================================================
