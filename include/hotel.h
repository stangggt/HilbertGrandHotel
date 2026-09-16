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

struct AuditLog {             // sheet: audit_log
    std::string id;
    std::string timestamp;
    std::string actorUser;
    std::string actorRole;
    std::string actionType;
    std::string targetEntity;
    std::string diff;
};

namespace hotel {

// ---------- PART 2 — ตัวแปรกลาง ----------

extern std::vector<Room>     g_rooms;
extern std::vector<RoomType> g_types;
extern std::vector<AuditLog> g_audits;
extern std::mutex            g_mtx;      // ล็อกร่วมของทั้งระบบ กันจองชนกัน

extern const char* F_DATA;               // data/hotel.xlsx
extern const char* SH_ROOMS;
extern const char* SH_TYPES;
extern const char* SH_BOOK;
extern const char* SH_USERS;
extern const char* SH_AUDIT;

// ---------- PART 3 — โหลดและบันทึก ----------

bool loadAll();      // อ่านไฟล์ Excel เข้าตัวแปรทั้ง 4 sheet + audit_log
bool saveAll();      // เขียนกลับทั้งไฟล์ คืน false ถ้าเขียนไม่สำเร็จ
bool lastSaveOk();   // ผลของ saveAll() ครั้งล่าสุด

// บันทึกการสำรองฐานข้อมูล (Backup Snapshot)
bool createBackupSnapshot(std::string* outBackupPath = nullptr);

// บันทึกการเปลี่ยนแปลง (Audit Log)
void logAction(const std::string& actorUser, const std::string& actorRole,
               const std::string& actionType, const std::string& targetEntity,
               const std::string& diff);

// แปลง Audit Logs ทั้งหมดเป็น JSON
std::string auditLogsJson();

// ---------- PART 4 — ค้นหาและแปลงเป็น JSON ----------

Room*     findRoom(const std::string& id);
RoomType* findType(const std::string& tier, const std::string& bed);

// ห้อง 1 ห้องสำหรับหน้าผู้ใช้ (รวมรายการจองที่กินห้อง เพื่อค้นหาตามช่วงวันที่)
std::string roomJsonPublic(const Room& m);

} // namespace hotel
