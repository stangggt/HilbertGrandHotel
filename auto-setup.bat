@echo off
REM ============================================================
REM  auto-setup.bat - ไฟล์เดียวจบ: ติดตั้ง compiler + คอมไพล์ + รัน
REM  Hilbert Grand Hotel  -  ดับเบิลคลิกไฟล์นี้ได้เลย
REM  (ส่วนล่างของไฟล์เป็นสคริปต์ PowerShell ที่ batch เรียกใช้เอง)
REM ============================================================
chcp 65001 >nul
cd /d "%~dp0"
set "HGH_ROOT=%~dp0"
set "HGH_SELF=%~f0"
where powershell >nul 2>&1 || (echo   [!!] ไม่พบ PowerShell ในเครื่อง & pause & exit /b 1)
powershell -NoProfile -ExecutionPolicy Bypass -Command "$c=[IO.File]::ReadAllText($env:HGH_SELF,[Text.Encoding]::UTF8); Invoke-Expression $c.Substring($c.LastIndexOf('#PSBEGIN')+8)"
set RC=%ERRORLEVEL%
echo.
if not "%RC%"=="0" echo   [!!] จบการทำงานด้วย error code %RC%
pause
exit /b %RC%
#PSBEGIN
# ============================================================
#  auto-setup.ps1 - ติดตั้ง compiler อัตโนมัติ + คอมไพล์ + รัน
#  Hilbert Grand Hotel
#  เรียกผ่าน auto-setup.bat (ไม่ต้องรันไฟล์นี้ตรง ๆ)
# ============================================================

$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$Root    = $env:HGH_ROOT.TrimEnd('\')
$Tools   = Join-Path $Root 'tools'
$BuildDir= Join-Path $Root 'build'
Set-Location $Root

function Say($m, $c='Gray') { Write-Host "  $m" -ForegroundColor $c }
function Head($m) { Write-Host ""; Write-Host "==> $m" -ForegroundColor Cyan }

Write-Host ""
Write-Host "============================================================" -ForegroundColor DarkCyan
Write-Host "  HILBERT GRAND HOTEL - Auto Setup" -ForegroundColor White
Write-Host "============================================================" -ForegroundColor DarkCyan
Say "โฟลเดอร์: $Root"

# ---------- 1. ตรวจโครงสร้าง ----------
Head "1/5 ตรวจโครงสร้างโปรเจกต์"
$missing = @()
foreach ($d in 'src','include','public','vendor') {
    if (Test-Path (Join-Path $Root $d)) { Say "[OK] พบโฟลเดอร์ $d\" Green }
    else { Say "[!!] ไม่พบโฟลเดอร์ $d\" Red; $missing += $d }
}
if ($missing.Count -gt 0) {
    Say "[!!] ไฟล์นี้ไม่ได้อยู่ที่ root ของโปรเจกต์ (ระดับเดียวกับ Makefile)" Red
    exit 1
}
if (Test-Path (Join-Path $Root 'data\hotel.xlsx')) { Say "[OK] พบฐานข้อมูล data\hotel.xlsx" Green }
else { Say "[~~] ไม่พบ data\hotel.xlsx - รันได้แต่จะไม่มีข้อมูลห้อง" Yellow }

# ---------- 2. หา / ติดตั้ง compiler ----------
Head "2/5 ตรวจ compiler (g++ / gcc)"

function Find-Gpp {
    # 2.1 มีใน PATH อยู่แล้ว
    $c = Get-Command g++ -ErrorAction SilentlyContinue
    if ($c) { return (Split-Path -Parent $c.Source) }
    # 2.2 เคยติดตั้งไว้ใน tools\ ของโปรเจกต์
    if (Test-Path $Tools) {
        $f = Get-ChildItem -Path $Tools -Filter 'g++.exe' -Recurse -ErrorAction SilentlyContinue |
             Select-Object -First 1
        if ($f) { return $f.DirectoryName }
    }
    # 2.3 ที่ติดตั้งไว้ทั่วไปในเครื่อง
    foreach ($p in 'C:\msys64\ucrt64\bin','C:\msys64\mingw64\bin','C:\mingw64\bin',
                   'C:\ProgramData\mingw64\mingw64\bin','C:\Strawberry\c\bin') {
        if (Test-Path (Join-Path $p 'g++.exe')) { return $p }
    }
    return $null
}

$BinDir = Find-Gpp

if (-not $BinDir) {
    Say "[~~] ไม่พบ g++ ในเครื่อง - จะดาวน์โหลด w64devkit มาติดตั้งให้อัตโนมัติ" Yellow
    Say "     (แบบพกพา ลงในโฟลเดอร์ tools\ ของโปรเจกต์ ไม่ต้องใช้สิทธิ์แอดมิน" Yellow
    Say "      ไม่แก้ PATH ของเครื่อง ลบทิ้งได้ด้วยการลบโฟลเดอร์ tools\)" Yellow

    New-Item -ItemType Directory -Force -Path $Tools | Out-Null
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

    $asset = $null
    try {
        Say "ค้นหาเวอร์ชันล่าสุดจาก GitHub..."
        $rel = Invoke-RestMethod -Uri 'https://api.github.com/repos/skeeto/w64devkit/releases/latest' `
                                 -Headers @{ 'User-Agent' = 'hgh-setup' }
        $asset = $rel.assets | Where-Object { $_.name -match 'x64.*\.zip$' -or $_.name -match '^w64devkit-\d.*\.zip$' } | Select-Object -First 1
        if (-not $asset) {
            $asset = $rel.assets | Where-Object { $_.name -match 'x64.*\.exe$' -or $_.name -match '^w64devkit-\d.*\.exe$' } | Select-Object -First 1
        }
    } catch {
        Say "[!!] ต่อ GitHub API ไม่ได้: $($_.Exception.Message)" Red
    }

    if (-not $asset) {
        Write-Host ""
        Say "[!!] ติดตั้งอัตโนมัติไม่สำเร็จ (อาจไม่มีเน็ต หรือถูกไฟร์วอลล์บล็อก)" Red
        Say "     ติดตั้งเองด้วยวิธีใดวิธีหนึ่ง:" Yellow
        Say "     A) winget install -e --id MSYS2.MSYS2" Yellow
        Say "        แล้วเปิด MSYS2 UCRT64 รัน: pacman -S --needed mingw-w64-ucrt-x86_64-toolchain make" Yellow
        Say "     B) โหลด w64devkit จาก https://github.com/skeeto/w64devkit/releases" Yellow
        Say "        แตกไฟล์ไว้ที่  $Tools" Yellow
        Say "     เสร็จแล้วรัน auto-setup.bat ใหม่อีกครั้ง" Yellow
        exit 1
    }

    $dl = Join-Path $Tools $asset.name
    Say "ดาวน์โหลด $($asset.name) ($([math]::Round($asset.size/1MB,1)) MB) ..."
    $pp = $ProgressPreference; $ProgressPreference = 'SilentlyContinue'
    Invoke-WebRequest -Uri $asset.browser_download_url -OutFile $dl -UseBasicParsing
    $ProgressPreference = $pp
    Say "[OK] ดาวน์โหลดเสร็จ" Green

    Say "กำลังแตกไฟล์ (ใช้เวลาสักครู่) ..."
    if ($asset.name -like '*.zip') {
        Expand-Archive -Path $dl -DestinationPath $Tools -Force
    } else {
        # ไฟล์ .exe ของ w64devkit เป็น 7-Zip self-extracting
        $p = Start-Process -FilePath $dl -ArgumentList "-y", "-o`"$Tools`"" -Wait -PassThru -NoNewWindow
        if ($p.ExitCode -ne 0) { Say "[!!] แตกไฟล์ไม่สำเร็จ (exit $($p.ExitCode))" Red; exit 1 }
    }
    Remove-Item $dl -Force -ErrorAction SilentlyContinue

    $BinDir = Find-Gpp
    if (-not $BinDir) { Say "[!!] แตกไฟล์แล้วแต่ยังหา g++.exe ไม่เจอใน $Tools" Red; exit 1 }
    Say "[OK] ติดตั้ง compiler เรียบร้อย" Green
}

$env:PATH = "$BinDir;$env:PATH"
Say "[OK] ใช้ compiler จาก: $BinDir" Green
Say "[OK] $((& g++ --version | Select-Object -First 1))" Green

# ---------- 3. ล้างของเก่า ----------
Head "3/5 ล้างไฟล์คอมไพล์เก่า"
New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null
Get-ChildItem -Path (Join-Path $BuildDir '*') -Include *.o,server.exe,tui.exe -File -ErrorAction SilentlyContinue |
    Remove-Item -Force -ErrorAction SilentlyContinue
Say "[OK] ล้าง build\ แล้ว" Green

# ---------- 4. คอมไพล์ ----------
Head "4/5 คอมไพล์"
$STATIC = '-static','-static-libgcc','-static-libstdc++'   # ให้ .exe รันได้โดยไม่ต้องพึ่ง DLL ของ compiler

Say "gcc  -> vendor\miniz.c"
& gcc -O2 -c vendor\miniz.c -o build\miniz.o
if ($LASTEXITCODE -ne 0) { Say "[!!] miniz.c คอมไพล์ไม่ผ่าน" Red; exit 1 }

$objs = @('build\miniz.o')
foreach ($f in Get-ChildItem 'src\*.cpp')  {
    if ($f.BaseName -in 'main','main_tui') { continue }
    Say "g++  -> src\$($f.Name)"
    $o = "build\$($f.BaseName).o"
    & g++ -std=c++17 -O2 -Iinclude -c $f.FullName -o $o
    if ($LASTEXITCODE -ne 0) { Say "[!!] $($f.Name) ไม่ผ่าน" Red; exit 1 }
    $objs += $o
}

# ลิงก์: ลองแบบ static ก่อน (ได้ .exe ที่ไม่ต้องพึ่ง DLL ของ compiler)
# ถ้าไม่ผ่าน ถอย -static ออกแล้วลองใหม่ MinGW บางชุดไม่มี .a ครบให้ลิงก์แบบ static
function Link-Exe($label, $srcFile, $extraLibs) {
    Say "link -> $label"
    $base = @('-std=c++17','-O2','-Iinclude',$srcFile) + $objs + @('-o',$label)
    $out = & g++ @base @STATIC @extraLibs 2>&1
    if ($LASTEXITCODE -eq 0) { return $true }

    Say "[~~] ลิงก์แบบ static ไม่ผ่าน ลองใหม่แบบปกติ..." Yellow
    $out2 = & g++ @base @extraLibs 2>&1
    if ($LASTEXITCODE -eq 0) {
        Say "[OK] ลิงก์ผ่านแบบปกติ (ต้องรัน .exe จากเครื่องที่มี compiler นี้)" Yellow
        return $true
    }

    Say "[!!] link $label ไม่ผ่าน - ข้อความจาก g++:" Red
    Write-Host ""
    $out2 | ForEach-Object { Write-Host "    $_" -ForegroundColor DarkYellow }
    Write-Host ""
    return $false
}

if (-not (Link-Exe 'build\server.exe' 'src\main.cpp' @('-lws2_32'))) { exit 1 }
if (-not (Link-Exe 'build\tui.exe'    'src\main_tui.cpp' @()))       { exit 1 }

# ---------- 5. ตรวจผล + รัน ----------
Head "5/5 ตรวจไฟล์ที่ได้"
foreach ($e in 'build\server.exe','build\tui.exe') {
    if (Test-Path $e) { Say "[OK] $e พร้อมใช้งาน" Green } else { Say "[!!] ไม่พบ $e" Red }
}

Write-Host ""
Write-Host "============================================================" -ForegroundColor DarkCyan
Write-Host "  ติดตั้งเสร็จสมบูรณ์" -ForegroundColor Green
Write-Host "============================================================" -ForegroundColor DarkCyan

if ($env:HGH_NORUN -eq '1') { Say "ข้ามการรัน (HGH_NORUN=1) - เปิดเองด้วย run.bat"; exit 0 }

$PORT = 8093
Write-Host ""
Write-Host "  1. เปิด Web Server  (http://localhost:$PORT)"
Write-Host "  2. เปิด Terminal TUI"
Write-Host "  3. ยังไม่รัน (ออก)"
Write-Host ""
$choice = Read-Host "  เลือก [1-3]"

switch ($choice) {
    '1' {
        $busy = (Get-NetTCPConnection -LocalPort $PORT -State Listen -ErrorAction SilentlyContinue)
        if ($busy) { Say "[~~] พอร์ต $PORT ถูกใช้อยู่ (PID $($busy.OwningProcess -join ',')) ปิดตัวเก่าก่อน" Yellow; exit 1 }
        Say "บัญชีทดสอบ: admin/admin123 . staff/staff123 . guest/guest123" Yellow
        Say "กด Ctrl+C เพื่อหยุดเซิร์ฟเวอร์" Yellow
        Start-Process "http://localhost:$PORT"
        & .\build\server.exe
    }
    '2' {
        Say "บัญชีทดสอบ: admin/admin123 . staff/staff123 . guest/guest123" Yellow
        & .\build\tui.exe
    }
    default { Say "เปิดโปรแกรมภายหลังด้วย run.bat" }
}
