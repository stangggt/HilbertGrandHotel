# ระบบจองโรงแรม — วางตามโครง include / src

```
โปรเจกต์/
├── .github/
├── build/
│   ├── .gitkeep
│   ├── build.bat          ← Windows
│   └── (ไฟล์ .o และ server ถูกสร้างที่นี่)
├── build.sh               ← Linux / macOS  (เพิ่มใหม่ที่ root)
├── data/
│   ├── .gitkeep
│   └── hotel.xlsx         ← ฐานข้อมูล 3 sheet
├── include/
│   ├── hotel.h            ← มีอยู่แล้ว เขียนทับ
│   ├── reservation.h      ← มีอยู่แล้ว เขียนทับ
│   ├── utils.h            ← มีอยู่แล้ว เขียนทับ
│   └── xlsx.h             ← เพิ่มใหม่
├── public/                ← เพิ่มใหม่ทั้งโฟลเดอร์ (frontend)
│   ├── index.html
│   ├── admin.html
│   ├── style.css
│   ├── app.js
│   └── admin.js
├── src/
│   ├── hotel.cpp          ← มีอยู่แล้ว เขียนทับ
│   ├── main.cpp           ← มีอยู่แล้ว เขียนทับ
│   ├── reservation.cpp    ← มีอยู่แล้ว เขียนทับ
│   └── utils.cpp          ← มีอยู่แล้ว เขียนทับ
├── test/
│   └── .gitkeep
└── vendor/                ← เพิ่มใหม่ทั้งโฟลเดอร์
    ├── miniz.c
    └── miniz.h
```

## build และรัน

**Linux / macOS**
```bash
./build.sh
./build/server
```

**Windows**
```
build\build.bat
build\server.exe
```

ต้องรันจาก root ของโปรเจกต์ เพราะโปรแกรมอ่าน `data/hotel.xlsx` และ `public/` จากตำแหน่งที่รัน

| หน้า | ที่อยู่ |
|---|---|
| ผู้ใช้ | http://localhost:8080 |
| แอดมิน | http://localhost:8080/admin |

`miniz.c` ต้อง compile ด้วย **gcc** แยกจาก C++ ถ้าเอาไปใส่ในคำสั่ง g++ ตรง ๆ จะ error

## แต่ละไฟล์ทำอะไร

| ไฟล์ | หน้าที่ | PART |
|---|---|---|
| `include/utils.h` · `src/utils.cpp` | JSON escape/parse · วันที่ · HTTP response · mime · อ่านไฟล์ | 3 |
| `include/hotel.h` · `src/hotel.cpp` | Room, RoomType · โหลด/บันทึก hotel.xlsx · ค้นหาห้อง · JSON ของห้อง | 4 |
| `include/reservation.h` · `src/reservation.cpp` | Booking · สร้าง แก้ไข เปลี่ยนสถานะ · ตรวจห้องว่าง | 5 |
| `include/xlsx.h` | อ่าน/เขียน .xlsx หลาย sheet (header-only) | 5 |
| `src/main.cpp` | HTTP server · router ทั้ง API ผู้ใช้และแอดมิน · static | 5 |
| `vendor/miniz.*` | บีบอัด zip สำหรับ .xlsx (public domain) | – |

## ลำดับการพึ่งพา

```
main.cpp
  ├── hotel.h ────► xlsx.h ──► vendor/miniz.h
  ├── reservation.h
  └── utils.h
```

`hotel` กับ `reservation` เรียกหากันได้สองทาง — `hotel::saveAll()` เขียน sheet bookings จาก `reservation::g_books` และ `reservation` เรียก `hotel::findRoom()` เพื่อเอาราคา ตัวแปร mutex กลางอยู่ที่ `hotel::g_mtx` ทุกฟังก์ชันใน reservation ถือว่าผู้เรียกล็อกไว้แล้ว

## data/hotel.xlsx — 3 sheet

| sheet | คอลัมน์ |
|---|---|
| `rooms` | room_id, floor, bed_type (twin/double), tier (normal/vip), price, note |
| `room_types` | tier, bed_type, display_name, amenities (คั่นด้วย `\|`) |
| `bookings` | booking_id, room_id, booker, phone, email, check_in, check_out, nights, total, status, created_at, note |

สถานะ: `wait` และ `checkin` = ห้องไม่ว่าง (สีแดงในหน้าผู้ใช้) · `checkout` และ `cancelled` = ห้องกลับมาว่าง

## API

| Method | Path | ใช้ที่ |
|---|---|---|
| GET | `/api/rooms` | ผู้ใช้ — ผังห้อง + สถานะ |
| POST | `/api/book` | ผู้ใช้ — จองห้อง |
| GET | `/api/admin/data` | แอดมิน — ห้อง + การจองทั้งหมด |
| POST | `/api/admin/status` | เปลี่ยนสถานะ |
| POST | `/api/admin/booking` | แก้ไขการจอง |
| POST | `/api/admin/add` | เพิ่มการจอง walk-in |
| POST | `/api/admin/room` | แก้ราคา/หมายเหตุห้อง |
| POST | `/api/admin/reload` | อ่านไฟล์ Excel ใหม่ |

## .gitignore ที่ควรเพิ่ม

```
build/*.o
build/server
build/server.exe
data/*.tmp
```

## ยังไม่มี

- ระบบล็อกอินหน้าแอดมิน ใครเข้า `/admin` ก็ใช้ได้
- การเทียบช่วงวันที่ทับกัน ยังจองล่วงหน้าหลายช่วงในห้องเดียวไม่ได้
