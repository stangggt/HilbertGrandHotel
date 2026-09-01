@echo off
REM ============================================================
REM  run.bat - เปิดโปรแกรม Hilbert Grand Hotel
REM  วางไว้ที่ root ของโปรเจกต์ (ระดับเดียวกับ Makefile)
REM  ดับเบิลคลิก หรือรัน:  run.bat
REM ============================================================
chcp 65001 >nul
setlocal
cd /d "%~dp0"
set PORT=8093

if not exist "build\server.exe" if not exist "build\tui.exe" (
  echo   ยังไม่ได้คอมไพล์ - รัน setup.bat ก่อน
  pause & exit /b 1
)
if not exist "data\hotel.xlsx" echo   [~~] เตือน: ไม่พบ data\hotel.xlsx - จะไม่มีข้อมูลห้องขึ้นมา

if /i "%~1"=="server" goto SERVER
if /i "%~1"=="tui"    goto TUI
if /i "%~1"=="test"   goto TEST

:MENU
cls
echo.
echo ============================================================
echo   HILBERT GRAND HOTEL - Launcher
echo ============================================================
echo.
echo   1. เปิด Web Server  (http://localhost:%PORT%)
echo   2. เปิด Terminal TUI
echo   3. ทดสอบ API ด้วย curl
echo   4. คอมไพล์ใหม่ (เรียก setup.bat)
echo   5. ออก
echo.
set /p choice=  เลือก [1-5]: 

if "%choice%"=="1" goto SERVER
if "%choice%"=="2" goto TUI
if "%choice%"=="3" goto TEST
if "%choice%"=="4" call setup.bat & goto MENU
if "%choice%"=="5" exit /b 0
echo   ตัวเลือกไม่ถูกต้อง
timeout /t 2 >nul
goto MENU

:SERVER
if not exist "build\server.exe" ( echo   ไม่พบ build\server.exe & pause & exit /b 1 )
netstat -ano | findstr ":%PORT% " >nul 2>&1
if not errorlevel 1 (
  echo.
  echo   [~~] พอร์ต %PORT% ถูกใช้อยู่ ปิดโปรแกรมตัวเก่าก่อน
  echo        ดู pid ด้วย: netstat -ano ^| findstr %PORT%
  echo        ปิดด้วย:     taskkill /PID ^<pid^> /F
  echo.
  pause & goto MENU
)
echo.
echo ============================================================
echo   WEB SERVER - http://localhost:%PORT%
echo ============================================================
echo   หน้าผู้ใช้/พนักงาน/แอดมิน   http://localhost:%PORT%
echo   หน้าแอดมินเดิม              http://localhost:%PORT%/admin
echo   บัญชีทดสอบ: admin/admin123 . staff/staff123 . guest/guest123
echo   กด Ctrl+C เพื่อหยุดเซิร์ฟเวอร์
echo.
start "" "http://localhost:%PORT%"
build\server.exe
pause
exit /b 0

:TUI
if not exist "build\tui.exe" ( echo   ไม่พบ build\tui.exe & pause & exit /b 1 )
echo   บัญชีทดสอบ: admin/admin123 . staff/staff123 . guest/guest123
timeout /t 1 >nul
build\tui.exe
pause
exit /b 0

:TEST
where curl >nul 2>&1
if errorlevel 1 ( echo   ต้องมี curl & pause & goto MENU )
echo   เปิดเซิร์ฟเวอร์ชั่วคราวเพื่อทดสอบ API...
start "hgh-test-server" /min build\server.exe
timeout /t 3 >nul
echo.
echo --- GET /api/rooms ---
curl -s http://localhost:%PORT%/api/rooms
echo.
echo.
echo --- POST /api/auth/login (admin) ---
curl -s -X POST http://localhost:%PORT%/api/auth/login -H "Content-Type: application/json" -d "{\"username\":\"admin\",\"password\":\"admin123\"}"
echo.
echo.
echo --- GET /api/admin/data ---
curl -s http://localhost:%PORT%/api/admin/data
echo.
echo.
taskkill /FI "WINDOWTITLE eq hgh-test-server*" /F >nul 2>&1
echo   ทดสอบเสร็จ ปิดเซิร์ฟเวอร์แล้ว
pause
goto MENU
