@echo off
REM ============================================================
REM  setup.bat - ติดตั้ง environment + คอมไพล์ Hilbert Grand Hotel
REM  วางไว้ที่ root ของโปรเจกต์ (ระดับเดียวกับ Makefile)
REM  ดับเบิลคลิก หรือรัน:  setup.bat
REM ============================================================
chcp 65001 >nul
setlocal enabledelayedexpansion
cd /d "%~dp0"

echo.
echo ============================================================
echo   HILBERT GRAND HOTEL - Environment Setup
echo ============================================================
echo   โฟลเดอร์: %cd%
echo.

REM ---------- 1. ตรวจโครงสร้าง ----------
echo ==^> 1/5 ตรวจโครงสร้างโปรเจกต์
set MISSING=0
for %%d in (src include public vendor) do (
  if exist "%%d\" ( echo   [OK] พบโฟลเดอร์ %%d\
  ) else ( echo   [!!] ไม่พบโฟลเดอร์ %%d\ & set MISSING=1 )
)
if "%MISSING%"=="1" (
  echo   [!!] ไฟล์นี้ไม่ได้อยู่ที่ root ของโปรเจกต์
  echo        ย้าย setup.bat ไปไว้ระดับเดียวกับ Makefile แล้วรันใหม่
  pause & exit /b 1
)
if exist "data\hotel.xlsx" (
  echo   [OK] พบฐานข้อมูล data\hotel.xlsx
) else (
  echo   [~~] ไม่พบ data\hotel.xlsx - โปรแกรมจะรันได้แต่ไม่มีข้อมูลห้อง
)

REM ---------- 2. ตรวจ compiler ----------
echo.
echo ==^> 2/5 ตรวจ compiler
where g++ >nul 2>&1
if errorlevel 1 goto NOCOMPILER
where gcc >nul 2>&1
if errorlevel 1 goto NOCOMPILER
for /f "tokens=*" %%v in ('g++ -dumpversion') do echo   [OK] g++ %%v
for /f "tokens=*" %%v in ('gcc -dumpversion') do echo   [OK] gcc %%v
goto COMPILER_OK

:NOCOMPILER
echo   [!!] ไม่พบ g++ / gcc ในเครื่อง
echo.
echo   ต้องติดตั้ง MinGW-w64 ก่อน เลือกวิธีใดวิธีหนึ่ง:
echo.
echo   วิธี A (แนะนำ) เปิด PowerShell แล้วรัน:
echo       winget install -e --id MSYS2.MSYS2
echo     จากนั้นเปิด "MSYS2 UCRT64" แล้วรัน:
echo       pacman -S --needed mingw-w64-ucrt-x86_64-toolchain make
echo     แล้วเพิ่ม C:\msys64\ucrt64\bin เข้า PATH
echo.
echo   วิธี B ดาวน์โหลด w64devkit จาก github.com/skeeto/w64devkit
echo     แตกไฟล์แล้วเพิ่มโฟลเดอร์ bin เข้า PATH
echo.
echo   ติดตั้งเสร็จแล้วเปิด cmd ใหม่ แล้วรัน setup.bat อีกครั้ง
pause & exit /b 1

:COMPILER_OK

REM ---------- 3. ล้างของเก่า ----------
echo.
echo ==^> 3/5 ล้างไฟล์คอมไพล์เก่า
if not exist "build\" mkdir build
del /q build\*.o        >nul 2>&1
del /q build\server.exe >nul 2>&1
del /q build\tui.exe    >nul 2>&1
echo   [OK] ล้าง build\ แล้ว

REM ---------- 4. คอมไพล์ ----------
echo.
echo ==^> 4/5 คอมไพล์ (miniz ด้วย gcc, ที่เหลือด้วย g++)

echo   gcc  -^> vendor\miniz.c
gcc -O2 -c vendor\miniz.c -o build\miniz.o
if errorlevel 1 ( echo   [!!] miniz.c คอมไพล์ไม่ผ่าน & pause & exit /b 1 )

set OBJS=build\miniz.o
for %%f in (src\*.cpp) do (
  if /i not "%%~nf"=="main" if /i not "%%~nf"=="main_tui" (
    echo   g++  -^> %%f
    g++ -std=c++17 -O2 -Iinclude -c "%%f" -o "build\%%~nf.o"
    if errorlevel 1 ( echo   [!!] %%f ไม่ผ่าน & pause & exit /b 1 )
    set OBJS=!OBJS! build\%%~nf.o
  )
)

echo   link -^> build\server.exe
g++ -std=c++17 -O2 -Iinclude src\main.cpp !OBJS! -o build\server.exe -lws2_32
if errorlevel 1 ( echo   [!!] link server ไม่ผ่าน & pause & exit /b 1 )

echo   link -^> build\tui.exe
g++ -std=c++17 -O2 -Iinclude src\main_tui.cpp !OBJS! -o build\tui.exe
if errorlevel 1 ( echo   [!!] link tui ไม่ผ่าน & pause & exit /b 1 )

REM ---------- 5. ตรวจผล ----------
echo.
echo ==^> 5/5 ตรวจไฟล์ที่ได้
if exist "build\server.exe" ( echo   [OK] build\server.exe พร้อมใช้งาน ) else ( echo   [!!] ไม่พบ server.exe )
if exist "build\tui.exe"    ( echo   [OK] build\tui.exe พร้อมใช้งาน )    else ( echo   [!!] ไม่พบ tui.exe )

echo.
echo ============================================================
echo   ติดตั้งเสร็จสมบูรณ์
echo ============================================================
echo   รันโปรแกรมด้วย:  run.bat
echo.
pause
