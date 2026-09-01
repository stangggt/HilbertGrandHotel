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
# คอมไพล์โปรแกรมทั้งหมด (ทั้ง Web Server และ Terminal TUI)
make all

# รัน Web Server (พอร์ต 8093)
make run-server

# รัน Terminal TUI
make run-tui

# ล้างไฟล์คอมไพล์
make clean
```

### วิธีที่ 2: ใช้สคริปต์

**Linux / macOS**
```bash
./build.sh
./build/server    # หรือ ./build/tui
```

**Windows**
```cmd
build\build.bat
build\server.exe   REM หรือ build\tui.exe
```
*รันในroot folder*

| หน้า / ช่องทาง                       | ที่อยู่ / คำสั่ง            |
| ------------------------------------ | --------------------------- |
| เว็บไซต์หลัก (Guest / Staff / Admin) | http://localhost:8093       |
| หน้าแอดมินเดิม                       | http://localhost:8093/admin |
| หน้าจอคอนโซล (Terminal TUI)          | `./build/tui`               |

`miniz.c` ต้อง compile ด้วย **gcc** แยกจาก C++ ถ้าเอาไปใส่ในคำสั่ง g++ ตรง ๆ จะ error

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
