// ============================================================
//  reservation.h — รายการจองและตรรกะการจอง
//     PART 1  โครงสร้างข้อมูล
//     PART 2  ตัวแปรกลาง
//     PART 3  ค้นหาและตรวจสถานะ
//     PART 4  สร้าง แก้ไข เปลี่ยนสถานะ
//     PART 5  แปลงเป็น JSON
//
//  ทุกฟังก์ชันในไฟล์นี้ถือว่าผู้เรียกล็อก hotel::g_mtx ไว้แล้ว
// ============================================================
#pragma once

#include <string>
#include <vector>

// ---------- PART 1 — โครงสร้างข้อมูล ----------

struct Booking {              // sheet: bookings
    std::string id, roomId, booker, phone, email;
    std::string checkIn, checkOut, status, createdAt, note;
    int  nights = 0;
    long total  = 0;
};

// ผลลัพธ์ของการทำงาน ใช้ส่งข้อความผิดพลาดภาษาไทยกลับไปให้หน้าเว็บ
struct Result {
    bool ok = false;
    std::string error;      // ว่างถ้าสำเร็จ
    std::string httpCode;   // เช่น "409 Conflict"
    Booking booking;        // มีค่าเมื่อสำเร็จ
};

namespace reservation {

// ---------- PART 2 — ตัวแปรกลาง ----------

extern std::vector<Booking> g_books;
const int MAX_NIGHTS = 30;

// ---------- PART 3 — ค้นหาและตรวจสถานะ ----------

Booking* find(const std::string& id);

// สถานะที่ยัง "กินห้อง" อยู่ = wait หรือ checkin
bool holdsRoom(const std::string& status);

// การจองที่ยังกินห้องนี้อยู่ ถ้าไม่มีแปลว่าห้องว่าง
Booking* activeFor(const std::string& roomId);

std::string nextId();

// ---------- PART 4 — สร้าง แก้ไข เปลี่ยนสถานะ ----------

// ลูกค้าจองจากหน้าเว็บ หรือแอดมินเพิ่มให้ลูกค้า walk-in
Result create(const std::string& roomId, const std::string& booker,
              const std::string& phone,  const std::string& email,
              const std::string& checkIn, int nights,
              const std::string& note, const std::string& status);

// แก้ไขรายละเอียดการจอง คำนวณวันเช็คเอาท์และยอดรวมใหม่ให้
Result edit(const std::string& id, const std::string& booker,
            const std::string& phone, const std::string& email,
            const std::string& checkIn, int nights, const std::string& note);

// wait -> checkin -> checkout หรือ cancelled
Result setStatus(const std::string& id, const std::string& status);

// ---------- PART 5 — แปลงเป็น JSON ----------

std::string toJson(const Booking& b);

} // namespace reservation
