# ระบบจองโรงแรม Hilbert Grand Hotel — วางตามโครง include / src

```
โปรเจกต์/
├── .github/
├── build/
│   ├── .gitkeep
│   ├── build.bat          ← Windows (คอมไพล์ทั้ง server.exe และ tui.exe)
│   └── (ไฟล์ .o, server และ tui ถูกสร้างที่นี่)
├── build.sh               ← Linux / macOS (คอมไพล์ทั้ง server และ tui)
├── Makefile               ← เพิ่มใหม่ รองรับ make all / server / tui / clean
├── data/
│   ├── .gitkeep
│   └── hotel.xlsx         ← ฐานข้อมูล 4 sheet (รวม sheet users)
├── include/
│   ├── console_utils.h    ← เพิ่มใหม่ (ระบบสี ANSI, จัดคอลัมน์ภาษาไทย, วาดตาราง Box Drawing)
│   ├── hotel.h            ← มีอยู่แล้ว (เพิ่มการอ่าน/เขียน sheet users)
│   ├── reservation.h      ← มีอยู่แล้ว
│   ├── tui.h              ← เพิ่มใหม่ (คลาส TuiApp สำหรับ Terminal Interface)
│   ├── user.h             ← เพิ่มใหม่ (โครงสร้าง User, Role: admin/staff/guest, auth)
│   ├── utils.h            ← มีอยู่แล้ว
│   └── xlsx.h             ← มีอยู่แล้ว (อ่าน/เขียน .xlsx หลาย sheet)
├── public/                ← ส่วน Frontend Webui
│   ├── index.html         ← หน้าเว็บหลัก รวม 4 Portal (Guest, Staff Hub, Admin Panel, Floor Matrix)
│   ├── admin.html         ← หน้าจัดการแอดมินเดิม (เชื่อมต่อ Theme และระบบ User)
│   ├── style.css          ← ดีไซน์ระบบ Dark/Light mode, Glassmorphism
│   ├── app.js             ← ตรรกะ Frontend เชื่อมต่อ REST API C++, เลือกรวมรูปห้อง, สลับ Role
│   └── admin.js           ← สคริปต์แอดมินเดิม
├── src/
│   ├── console_utils.cpp  ← เพิ่มใหม่ (คำนวณความกว้าง UTF-8 ภาษาไทย ตัดสระบนล่างออก)
│   ├── hotel.cpp          ← โหลด/บันทึก sheet users เพิ่มเติม
│   ├── main.cpp           ← HTTP server · เพิ่ม router API สำหรับ auth/login/register
│   ├── main_tui.cpp       ← เพิ่มใหม่ (Entry point สำหรับโปรแกรมคอนโซล ./build/tui)
│   ├── reservation.cpp    ← จัดการการจองห้องพัก
│   ├── tui.cpp            ← เพิ่มใหม่ (ระบบเมนู TUI ลูกค้า/พนักงาน/ผังห้อง 3 ชั้น)
│   ├── user.cpp           ← เพิ่มใหม่ (ระบบตรวจสอบรหัสผ่าน, สมัครสมาชิก, seed บัญชี)
│   └── utils.cpp          ← JSON, วันที่, HTTP response
├── test/
│   └── .gitkeep
└── vendor/
    ├── miniz.c
    └── miniz.h
```

---

## build และรัน

### วิธีที่ 1: ใช้ Makefile

```bash
# คอมไพล์โปรแกรมทั้งหมด (ทั้ง Web Server, TUI, Test Suite, Benchmark)
make all

# รัน Web Server โหมดปกติ (Production Mode)
make run-server

# รัน Web Server โหมดนำเสนอ (Demo Mode เปิด Quick Role Switcher)
make run-demo

# รัน Terminal TUI
make run-tui

# รันชุดทดสอบอัตโนมัติ (Automated Unit & Regression Tests)
make test

# รันการทดสอบประสิทธิภาพโครงสร้างข้อมูล (Academic DSA Benchmark 100k records)
make benchmark

# ล้างไฟล์คอมไพล์
make clean
```

### วิธีที่ 2: ใช้สคริปต์

**Linux / macOS**
```bash
./build.sh
./build/server          # โหมดปกติ
./build/server -f demo  # โหมดเดโม (Demo Mode)
```

**Windows**
```cmd
build\build.bat
build\server.exe        REM โหมดปกติ
build\server.exe -f demo REM โหมดเดโม
```
*รันใน root folder*

| หน้า / ช่องทาง                       | ที่อยู่ / คำสั่ง            |
| ------------------------------------ | --------------------------- |
| เว็บไซต์หลัก (Guest / Staff / Admin) | http://localhost:8093       |
| หน้าแอดมินเดิม                       | http://localhost:8093/admin |
| หน้าจอคอนโซล (Terminal TUI)          | `./build/tui`               |

`miniz.c` ต้อง compile ด้วย **gcc** แยกจาก C++ ถ้าเอาไปใส่ในคำสั่ง g++ ตรง ๆ จะ error

---

## 👤 บัญชีทดสอบระบบ (Demo Accounts)

ระบบมีบัญชีผู้ใช้เริ่มต้น (Default Seeded Accounts) ที่พร้อมใช้งานทันทีสำหรับทุกบทบาท (Role):

| บทบาท (Role) | Username | Password | ชื่อผู้ใช้ (Full Name) | อีเมล / เบอร์โทร | สิทธิ์การเข้าถึงและการทำงาน (Privileges) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **👑 Admin** | `admin` | `admin123` | System Administrator | `admin@hotel.com`<br>`081-000-0001` | เข้าถึง Executive Control Panel, จัดการผู้ใช้, ดูสถิติรายได้, แก้ราคาห้องพัก, Reload/Backup Excel DB, Terminal Console (`Ctrl+K`), และตรวจสอบ Audit Log |
| **💼 Staff** | `staff` | `staff123` | Front Desk Staff | `staff@hotel.com`<br>`081-000-0002` | เข้าถึง Staff Operations Hub, ผังห้องพักสด (PMS Matrix), ตรวจสอบข้อมูลผู้จอง (Room Inspector), จัดการ Check-In / Check-Out, ขยายเวลาพัก (Extend Stay), และพิมพ์ใบเสร็จ (Folio) |
| **👤 Guest** | `guest` | `guest123` | สมชาย ใจดี | `somchai@gmail.com`<br>`081-234-5678` | เข้าถึง Guest Suites, ค้นหาห้องพักตามช่วงวันที่/ราคา/สิ่งอำนวยความสะดวก, จองห้องพัก, ดูประวัติการจองของตนเอง ("My Bookings"), และขอขยายเวลาพัก |

> **💡 โหมดการรันเซิร์ฟเวอร์ (Production vs Demo Mode):**
> - **Production Mode (ปกติ):** `make run-server` หรือ `./build/server` — ระบบจะซ่อนปุ่มสลับบทบาทอัตโนมัติ (Role Switcher Bubble) และ 1-click profiles เพื่อความปลอดภัยตามมาตรฐาน Production โดยต้องเข้าสู่ระบบด้วย Username & Password จริง
> - **Demo Mode (นำเสนอ/ตรวจงาน):** `make run-demo` หรือ `./build/server -f demo` — ระบบจะเปิดใช้งาน Quick Demo Profiles (1-Click Login) และ Floating Role Switcher ที่มุมขวาล่าง เพื่อความสะดวกรวดเร็วในการทดสอบและสาธิตระบบ

---

## 🐳 วิธีรันผ่าน Docker (Run on Docker)

**Docker** ช่วยให้คุณรันโปรแกรมได้ทันทีบนทุกเครื่อง (Linux, Windows, macOS) โดยไม่ต้องติดตั้ง C++ Compiler หรือเครื่องมือใดๆ เพิ่มเติม

> **💡 สำหรับ CachyOS (หากยังไม่ได้ลง Docker):**
> ```bash
> sudo pacman -S docker
> sudo systemctl enable --now docker
> sudo usermod -aG docker $USER    # เพื่อให้รันคำสั่ง docker ได้โดยไม่ต้องพิมพ์ sudo
> newgrp docker
> ```

### ขั้นตอนที่ 1: สร้างไฟล์ `Dockerfile`
สร้างไฟล์ชื่อ `Dockerfile` ไว้ที่โฟลเดอร์หลักของโปรเจกต์ (มีเนื้อหาตามนี้):

```dockerfile
FROM ubuntu:22.04

# ติดตั้งเครื่องมือคอมไพล์ภาษา C/C++
RUN apt-get update && apt-get install -y g++ gcc make && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# คอมไพล์โปรแกรม
RUN make clean && make server

# เปิดพอร์ตใช้งาน
EXPOSE 8093

# เริ่มต้นเซิร์ฟเวอร์
CMD ["./build/server"]
```

### ขั้นตอนที่ 2: สั่งประกอบร่าง (Build Docker Image)
เปิด Terminal ในโฟลเดอร์โปรเจกต์ แล้วพิมพ์คำสั่ง:
```bash
docker build -t hilbert-hotel .
```

### ขั้นตอนที่ 3: สั่งรัน (Run Container)
รันคำสั่งนี้เพื่อเปิดใช้งานเซิร์ฟเวอร์:
```bash
docker run -d \
  --name hotel-app \
  -p 8093:8093 \
  -v $(pwd)/data:/app/data \
  --restart unless-stopped \
  hilbert-hotel
```

> **คำอธิบายตัวเลือกสำคัญ:**
> - `-p 8093:8093` : เชื่อมพอร์ตจากใน Docker ออกมาที่เครื่องเรา ทำให้เข้าเว็บผ่าน `http://localhost:8093` ได้
> - `-v $(pwd)/data:/app/data` : **สำคัญมาก!** เชื่อมโฟลเดอร์ `data/` กับเครื่องจริง เพื่อให้ไฟล์ฐานข้อมูล Excel (`hotel.xlsx`) และ Session ไม่สูญหายเมื่อปิดหรืออัปเดต Docker
> - `--restart unless-stopped` : สั่งให้เปิดโปรแกรมใหม่เองอัตโนมัติเมื่อเครื่องเปิด (ดูหัวข้อถัดไป)

---

## ⚡ วิธีตั้งให้โปรแกรมเปิดทำงานอัตโนมัติเมื่อเปิดเครื่อง (Auto-start on Boot)

หากต้องการให้เซิร์ฟเวอร์เปิดตัวเองขึ้นมาทันทีที่เปิดเครื่องคอมพิวเตอร์ หรือเมื่อรีสตาร์ตเซิร์ฟเวอร์ เลือกลองทำตามวิธีที่สะดวกได้ดังนี้:

### วิธีที่ 1: ใช้ Docker (ง่ายที่สุด แนะนำ ⭐)
หากคุณรันโปรแกรมด้วย Docker อยู่แล้ว แค่ใส่ตัวเลือก `--restart unless-stopped` ในคำสั่งรัน:
```bash
docker run -d --name hotel-app -p 8093:8093 -v $(pwd)/data:/app/data --restart unless-stopped hilbert-hotel
```
- **ผลลัพธ์:** ทุกครั้งที่เปิดเครื่องคอมพิวเตอร์ขึ้นมา Docker จะสั่งให้เซิร์ฟเวอร์โรงแรมเปิดทำงานในพื้นหลังทันที โดยที่คุณไม่ต้องเปิดหน้าจอ Terminal มากดรันเองเลย

---

### วิธีที่ 2: สำหรับ CachyOS / Arch Linux / Ubuntu Server (ผ่าน systemd Service)
หากคุณคอมไพล์รันตรงๆ บนเครื่อง CachyOS โดยไม่ใช้ Docker:

> **💡 สำหรับ CachyOS:** หากยังไม่ได้ติดตั้งเครื่องมือคอมไพล์ ให้พิมพ์:
> ```bash
> sudo pacman -S base-devel gcc make
> ```

1. **สร้างไฟล์บริการระบบ:**
   พิมพ์คำสั่ง:
   ```bash
   sudo nano /etc/systemd/system/hilbert-hotel.service
   ```

2. **ใส่ข้อความด้านล่างนี้ลงไป** (แก้ไข Path โฟลเดอร์ให้ตรงกับที่อยู่ของโปรเจกต์ในเครื่องคุณ):
   ```ini
   [Unit]
   Description=Hilbert Grand Hotel Web Server
   After=network.target

   [Service]
   Type=simple
   User=nuts
   WorkingDirectory=/home/nuts/Projects/DataStructure/Team/HilbertGrandHotel
   ExecStart=/home/nuts/Projects/DataStructure/Team/HilbertGrandHotel/build/server
   Restart=always
   RestartSec=3

   [Install]
   WantedBy=multi-user.target
   ```

3. **สั่งเปิดใช้งานและเริ่มทำงาน:**
   ```bash
   # สั่งให้อ่านไฟล์บริการใหม่
   sudo systemctl daemon-reload

   # สั่งให้เปิดทำงานอัตโนมัติทุกครั้งที่บูตเครื่อง
   sudo systemctl enable hilbert-hotel

   # เริ่มต้นการทำงานทันที
   sudo systemctl start hilbert-hotel
   ```
- ตรวจสอบสถานะการทำงานได้ด้วยคำสั่ง: `sudo systemctl status hilbert-hotel`
- สั่งหยุดการทำงาน: `sudo systemctl stop hilbert-hotel`
- สั่งเริ่มใหม่: `sudo systemctl restart hilbert-hotel`

---

### วิธีที่ 3: สำหรับ Windows
หากคุณใช้งานบน Windows:
1. กดปุ่ม `Windows + R` บนคีย์บอร์ด
2. พิมพ์ `shell:startup` แล้วกด **Enter** (โฟลเดอร์ Startup ของเครื่องจะเปิดขึ้นมา)
3. คลิกขวาที่ไฟล์ `build/server.exe` (หรือไฟล์ `build.bat`) เลือก **Create shortcut** (สร้างทางลัด)
4. นำไฟล์ Shortcut นั้นมาวางไว้ในโฟลเดอร์ Startup
- **ผลลัพธ์:** ทุกครั้งที่คุณเปิดคอมพิวเตอร์และล็อกอินเข้า Windows โปรแกรมเซิร์ฟเวอร์จะเปิดขึ้นมาทำงานให้เองทันที

---

## แต่ละไฟล์ทำอะไร

| ไฟล์                                                 | หน้าที่                                                                                          | PART |
| ---------------------------------------------------- | ------------------------------------------------------------------------------------------------ | ---- |
| `include/utils.h` · `src/utils.cpp`                  | JSON escape/parse · วันที่ · HTTP response · mime · อ่านไฟล์                                     | 3    |
| `include/hotel.h` · `src/hotel.cpp`                  | Room, RoomType · โหลด/บันทึก hotel.xlsx 4 sheet · ค้นหาห้อง · JSON ของห้อง                       | 4    |
| `include/reservation.h` · `src/reservation.cpp`      | Booking · สร้าง แก้ไข เปลี่ยนสถานะ · ตรวจห้องว่าง                                                | 5    |
| `include/xlsx.h`                                     | อ่าน/เขียน .xlsx หลาย sheet (header-only)                                                        | 5    |
| `src/main.cpp`                                       | HTTP server · router API ผู้ใช้/แอดมิน/ล็อกอิน · ให้บริการไฟล์ static                            | 5    |
| `include/user.h` · `src/user.cpp`                    | **[เพิ่มใหม่]** ระบบ User, Role (admin/staff/guest), ตรวจสอบรหัสผ่าน, สมัครสมาชิก, Seed ข้อมูล   | –    |
| `include/console_utils.h` · `src/console_utils.cpp`  | **[เพิ่มใหม่]** ระบบสี ANSI, ตาราง Box Drawing, คำนวณความกว้าง UTF-8 ภาษาไทย (ตัดสระบน/ล่างออก)  | –    |
| `include/tui.h` · `src/tui.cpp` · `src/main_tui.cpp` | **[เพิ่มใหม่]** แอพพลิเคชันคอนโซล TUI แสดงผังห้อง 3 ชั้น, จองห้อง, เช็คอิน/เอาท์, แก้ราคา        | –    |
| `public/index.html` · `style.css` · `app.js`         | **[อัปเกรดใหม่]** Frontend Modern Luxury ดีไซน์แบบ Single-Page 4 Portals, Floating Role Switcher | –    |
| `vendor/miniz.*`                                     | บีบอัด zip สำหรับ .xlsx (public domain)                                                          | –    |

---

## ลำดับการพึ่งพา

```
main.cpp (Web Server)
  ├── hotel.h ────► xlsx.h ──► vendor/miniz.h
  ├── reservation.h
  ├── user.h
  └── utils.h

main_tui.cpp (Terminal TUI)
  ├── tui.h
  │     ├── console_utils.h
  │     ├── hotel.h
  │     ├── reservation.h
  │     └── user.h
  └── utils.h
```

`hotel` กับ `reservation` และ `user` เรียกหากันได้สองทาง — `hotel::saveAll()` บันทึก sheet rooms, room_types, bookings และ users ลงใน `data/hotel.xlsx` โดยมี mutex กลางอยู่ที่ `hotel::g_mtx`

---

## data/hotel.xlsx — 4 sheet

| sheet        | คอลัมน์                                                                                                 |
| ------------ | ------------------------------------------------------------------------------------------------------- |
| `rooms`      | room_id, floor, bed_type (twin/double), tier (normal/vip), price, note                                  |
| `room_types` | tier, bed_type, display_name, amenities (คั่นด้วย `\|`)                                                 |
| `bookings`   | booking_id, room_id, booker, phone, email, check_in, check_out, nights, total, status, created_at, note |
| `users`      | **[เพิ่มใหม่]** username, password, role (admin/staff/guest), full_name, phone, email                   |

**สถานะการจอง:**
* `wait` และ `checkin` = ห้องไม่ว่าง (แสดงสีแดง/ติดจอง)
* `checkout` และ `cancelled` = ห้องกลับมาว่าง (แสดงสีเขียว)

---

## API ทั้งหมด

| Method | Path                 | หน้าที่                                                                 |
| ------ | -------------------- | ----------------------------------------------------------------------- |
| GET    | `/api/rooms`         | ผู้ใช้ — รายชื่อห้องพัก, รายละเอียด, ราคา, สถานะห้องว่าง                |
| POST   | `/api/book`          | ผู้ใช้ — ส่งข้อมูลการจองห้องพัก                                         |
| POST   | `/api/auth/login`    | **[เพิ่มใหม่]** ตรวจสอบสิทธิ์ Username/Password ส่งข้อมูลผู้ใช้และ Role |
| POST   | `/api/auth/register` | **[เพิ่มใหม่]** สมัครสมาชิกใหม่สำหรับ Guest บันทึกลง Excel              |
| GET    | `/api/auth/users`    | **[เพิ่มใหม่]** ดึงรายชื่อผู้ใช้ทั้งหมดในระบบ                           |
| GET    | `/api/admin/data`    | แอดมิน — ข้อมูลห้องพักทั้งหมด + ข้อมูลการจองทั้งหมด                     |
| POST   | `/api/admin/status`  | เปลี่ยนสถานะการจอง (`wait`, `checkin`, `checkout`, `cancelled`)         |
| POST   | `/api/admin/booking` | แก้ไขข้อมูลการจอง                                                       |
| POST   | `/api/admin/add`     | เพิ่มการจองห้องพักแบบ Walk-in                                           |
| POST   | `/api/admin/room`    | แก้ไขราคา/คืน และหมายเหตุของห้องพัก บันทึกลง Excel                      |
| POST   | `/api/admin/reload`  | อ่านข้อมูลจากไฟล์ Excel `data/hotel.xlsx` เข้าหน่วยความจำใหม่           |

---

### ระบบที่ทำเพิ่ม
- login system สามารถ sign-in/sign-up ได้ มีrole แยก admin, staff, user
- front-end แบบ webui กับ TUI 

## .gitignore ที่เพิ่ม

```gitignore
build/*.o
build/server
build/server.exe
build/tui
build/tui.exe
data/*.tmp
.DS_Store
```
