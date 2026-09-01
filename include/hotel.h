// ============================================================
//  hotel.h — ห้องพัก ประเภทห้อง และการอ่านเขียนไฟล์ Excel
//
//  ข้อมูลทั้งหมดอยู่ใน data/hotel.xlsx แบ่งเป็น 3 sheet
//     rooms        ผังห้อง
//     room_types   ประเภทห้อง + สิ่งอำนวยความสะดวก
//     bookings     รายการจอง  (โครงสร้างอยู่ใน reservation.h)
//
//     PART 1  โครงสร้างข้อมูล
//     PART 2  ตัวแปรกลาง
//     PART 3  โหลดและบันทึก
//     PART 4  ค้นหาและแปลงเป็น JSON
// ============================================================
#pragma once

#include <string>
#include <vector>
#include <mutex>

// ---------- PART 1 — โครงสร้างข้อมูล ----------

struct Room {                 // sheet: rooms
    std::string id, floor, bed, tier, note;
    long price = 0;
};

struct RoomType {             // sheet: room_types
    std::string tier, bed, name;
    std::vector<std::string> amenities;
};

namespace hotel {

// ---------- PART 2 — ตัวแปรกลาง ----------

extern std::vector<Room>     g_rooms;
extern std::vector<RoomType> g_types;
extern std::mutex            g_mtx;      // ล็อกร่วมของทั้งระบบ กันจองชนกัน

extern const char* F_DATA;               // data/hotel.xlsx
extern const char* SH_ROOMS;
extern const char* SH_TYPES;
extern const char* SH_BOOK;
extern const char* SH_USERS;

// ---------- PART 3 — โหลดและบันทึก ----------

bool loadAll();      // อ่านไฟล์ Excel เข้าตัวแปรทั้ง 3 sheet
bool saveAll();      // เขียนกลับทั้งไฟล์ คืน false ถ้าเขียนไม่สำเร็จ
bool lastSaveOk();   // ผลของ saveAll() ครั้งล่าสุด

// ---------- PART 4 — ค้นหาและแปลงเป็น JSON ----------

Room*     findRoom(const std::string& id);
RoomType* findType(const std::string& tier, const std::string& bed);

// ห้อง 1 ห้องสำหรับหน้าผู้ใช้ (ไม่ส่งข้อมูลส่วนตัวของผู้จองออกไป)
std::string roomJsonPublic(const Room& m);

} // namespace hotel
