#!/bin/sh
# ============================================================
#  build.sh — Linux / macOS
#  รันจาก root ของโปรเจกต์:  ./build.sh  แล้ว  ./build/server
# ============================================================
set -e
mkdir -p build
gcc -O2 -c vendor/miniz.c            -o build/miniz.o
g++ -std=c++17 -O2 -pthread -c src/utils.cpp       -o build/utils.o
g++ -std=c++17 -O2 -pthread -c src/hotel.cpp       -o build/hotel.o
g++ -std=c++17 -O2 -pthread -c src/reservation.cpp -o build/reservation.o
g++ -std=c++17 -O2 -pthread -c src/main.cpp        -o build/main.o
g++ -pthread -o build/server build/miniz.o build/utils.o build/hotel.o build/reservation.o build/main.o
echo "build เสร็จ  ->  ./build/server"
