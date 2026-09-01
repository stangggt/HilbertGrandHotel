// ============================================================
//  utils.h — ตัวช่วยกลางที่โมดูลอื่นเรียกใช้ร่วมกัน
//     PART 1  JSON: escape และดึงค่าจาก body
//     PART 2  วันที่และเวลา
//     PART 3  HTTP: สร้าง response, mime type, อ่านไฟล์
// ============================================================
#pragma once

#include <string>
#include <vector>

namespace utils {

// ---------- PART 1 — JSON ----------

// แปลงอักขระพิเศษให้ปลอดภัยสำหรับ JSON
std::string esc(const std::string& s);

// ครอบด้วยเครื่องหมายคำพูดพร้อม escape ให้เลย
std::string q(const std::string& s);

// ดึงค่าตัวเลขจาก body  {"nights":3} -> 3
long jsonInt(const std::string& body, const std::string& key, long def = 0);

// ดึงค่าข้อความจาก body  {"booker":"สมชาย"} -> สมชาย
std::string jsonStr(const std::string& body, const std::string& key, size_t maxLen = 120);

// มี key นี้อยู่ใน body หรือไม่ (ใช้แยก "ไม่ได้ส่งมา" ออกจาก "ส่งมาเป็นค่าว่าง")
bool jsonHas(const std::string& body, const std::string& key);

// อ่านค่าในช่องที่ i ถ้าแถวสั้นกว่าก็คืนค่าว่าง
std::string at(const std::vector<std::string>& row, size_t i);


// ---------- PART 2 — วันที่และเวลา ----------

std::string todayStr();                                   // 2026-09-01
std::string nowStr();                                     // 2026-09-01 14:30:00
std::string addDays(const std::string& ymd, int days);    // บวกวัน


// ---------- PART 3 — HTTP ----------

std::string mimeOf(const std::string& path);
std::string resp(const std::string& status, const std::string& mime, const std::string& body);
std::string jsonOk(const std::string& body);
std::string jsonErr(const std::string& code, const std::string& msg);
bool readFile(const std::string& path, std::string& out);

} // namespace utils
