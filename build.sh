#!/bin/sh
# ============================================================
#  build.sh — Linux / macOS
#  รันจาก root ของโปรเจกต์:  ./build.sh
#  รัน Web Server:  ./build/server
#  รัน Terminal TUI: ./build/tui
# ============================================================
set -e
mkdir -p build

echo "==> Compiling C/C++ objects..."
gcc -O2 -c vendor/miniz.c                   -o build/miniz.o
g++ -std=c++17 -O2 -pthread -c src/utils.cpp         -o build/utils.o
g++ -std=c++17 -O2 -pthread -c src/hotel.cpp         -o build/hotel.o
g++ -std=c++17 -O2 -pthread -c src/reservation.cpp   -o build/reservation.o
g++ -std=c++17 -O2 -pthread -c src/user.cpp          -o build/user.o
g++ -std=c++17 -O2 -pthread -c src/console_utils.cpp -o build/console_utils.o
g++ -std=c++17 -O2 -pthread -c src/tui.cpp           -o build/tui.o

echo "==> Linking Web Server (./build/server)..."
g++ -std=c++17 -O2 -pthread -c src/main.cpp          -o build/main.o
g++ -pthread -o build/server build/miniz.o build/utils.o build/hotel.o build/reservation.o build/user.o build/main.o

echo "==> Linking Terminal TUI (./build/tui)..."
g++ -std=c++17 -O2 -pthread -c src/main_tui.cpp      -o build/main_tui.o
g++ -pthread -o build/tui build/miniz.o build/utils.o build/hotel.o build/reservation.o build/user.o build/console_utils.o build/tui.o build/main_tui.o

echo "============================================================"
echo " Build เสร็จสมบูรณ์:"
echo "   - Web Server:    ./build/server  (http://localhost:8093)"
echo "   - Terminal UI:   ./build/tui"
echo "============================================================"
