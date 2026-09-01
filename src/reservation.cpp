// ============================================================
//  reservation.cpp — ดูสารบัญที่ include/reservation.h
// ============================================================
#include "../include/reservation.h"
#include "../include/hotel.h"
#include "../include/utils.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdio>

namespace reservation {

// ============================================================
// PART 2 — ตัวแปรกลาง
// ============================================================
std::vector<Booking> g_books;


// ============================================================
// PART 3 — ค้นหาและตรวจสถานะ
// ============================================================
Booking* find(const std::string& id) {
    for (auto& b : g_books) if (b.id == id) return &b;
    return nullptr;
}

bool holdsRoom(const std::string& s) { return s == "wait" || s == "checkin"; }

Booking* activeFor(const std::string& roomId) {
    for (auto& b : g_books)
        if (b.roomId == roomId && holdsRoom(b.status)) return &b;
    return nullptr;
}

std::string nextId() {
    long mx = 0;
    for (auto& b : g_books)
        if (b.id.size() > 1 && b.id[0] == 'B') mx = std::max(mx, std::atol(b.id.c_str() + 1));
    char buf[24];
    snprintf(buf, sizeof(buf), "B%04ld", (long)(mx + 1) % 1000000);
    return buf;
}


// ============================================================
// PART 4 — สร้าง แก้ไข เปลี่ยนสถานะ
// ============================================================
static Result fail(const std::string& code, const std::string& msg) {
    Result r; r.ok = false; r.httpCode = code; r.error = msg;
    return r;
}

Result create(const std::string& roomId, const std::string& booker,
              const std::string& phone,  const std::string& email,
              const std::string& checkIn, int nights,
              const std::string& note, const std::string& status) {

    Room* m = hotel::findRoom(roomId);
    if (!m)                              return fail("404 Not Found",   "ไม่พบหมายเลขห้องนี้");
    if (booker.empty())                  return fail("400 Bad Request", "กรอกชื่อผู้จอง");
    if (phone.empty())                   return fail("400 Bad Request", "กรอกเบอร์โทรติดต่อ");
    if (nights < 1 || nights > MAX_NIGHTS)
        return fail("400 Bad Request", "จำนวนคืนต้องอยู่ระหว่าง 1 ถึง " + std::to_string(MAX_NIGHTS));
    if (checkIn.size() < 10)             return fail("400 Bad Request", "เลือกวันเช็คอิน");
    if (activeFor(roomId))               return fail("409 Conflict",    "ห้องนี้เพิ่งถูกจองไปแล้ว เลือกห้องอื่นได้เลย");

    Booking b;
    b.id        = nextId();
    b.roomId    = roomId;
    b.booker    = booker;
    b.phone     = phone;
    b.email     = email;
    b.checkIn   = checkIn;
    b.checkOut  = utils::addDays(checkIn, nights);
    b.nights    = nights;
    b.total     = (long)nights * m->price;
    b.status    = (status == "checkin") ? "checkin" : "wait";
    b.createdAt = utils::nowStr();
    b.note      = note;

    g_books.push_back(b);
    hotel::saveAll();
    std::cout << "[BOOK] " << b.id << " ห้อง " << b.roomId << " " << b.nights
              << " คืน = " << b.total << " บาท (" << b.booker << ")\n";

    Result r; r.ok = true; r.booking = b;
    return r;
}

Result edit(const std::string& id, const std::string& booker,
            const std::string& phone, const std::string& email,
            const std::string& checkIn, int nights, const std::string& note) {

    Booking* b = find(id);
    if (!b)             return fail("404 Not Found",   "ไม่พบรายการจองนี้");
    if (booker.empty()) return fail("400 Bad Request", "กรอกชื่อผู้จอง");
    if (nights < 1 || nights > MAX_NIGHTS)
        return fail("400 Bad Request", "จำนวนคืนต้องอยู่ระหว่าง 1 ถึง " + std::to_string(MAX_NIGHTS));

    Room* m = hotel::findRoom(b->roomId);
    b->booker = booker;
    b->phone  = phone;
    b->email  = email;
    b->note   = note;
    b->nights = nights;
    if (checkIn.size() >= 10) b->checkIn = checkIn;
    b->checkOut = utils::addDays(b->checkIn, nights);
    b->total    = (long)nights * (m ? m->price : 0);

    hotel::saveAll();
    std::cout << "[EDIT] " << b->id << "\n";

    Result r; r.ok = true; r.booking = *b;
    return r;
}

Result setStatus(const std::string& id, const std::string& status) {
    if (status != "wait" && status != "checkin" && status != "checkout" && status != "cancelled")
        return fail("400 Bad Request", "สถานะไม่ถูกต้อง");

    Booking* b = find(id);
    if (!b) return fail("404 Not Found", "ไม่พบรายการจองนี้");

    // ถ้าจะย้ายกลับมาเป็นสถานะที่กินห้อง ต้องไม่มีรายการอื่นกินห้องนั้นอยู่
    if (holdsRoom(status) && !holdsRoom(b->status)) {
        Booking* other = activeFor(b->roomId);
        if (other && other->id != b->id)
            return fail("409 Conflict", "ห้องนี้มีรายการจองที่ใช้งานอยู่แล้ว");
    }

    b->status = status;
    hotel::saveAll();
    std::cout << "[STATUS] " << b->id << " -> " << status << "\n";

    Result r; r.ok = true; r.booking = *b;
    return r;
}


// ============================================================
// PART 5 — แปลงเป็น JSON
// ============================================================
std::string toJson(const Booking& b) {
    using utils::q;
    Room* m = hotel::findRoom(b.roomId);
    std::ostringstream o;
    o << "{" << q("id")        << ":" << q(b.id)
      << "," << q("room")      << ":" << q(b.roomId)
      << "," << q("booker")    << ":" << q(b.booker)
      << "," << q("phone")     << ":" << q(b.phone)
      << "," << q("email")     << ":" << q(b.email)
      << "," << q("checkIn")   << ":" << q(b.checkIn)
      << "," << q("checkOut")  << ":" << q(b.checkOut)
      << "," << q("nights")    << ":" << b.nights
      << "," << q("total")     << ":" << b.total
      << "," << q("status")    << ":" << q(b.status)
      << "," << q("createdAt") << ":" << q(b.createdAt)
      << "," << q("note")      << ":" << q(b.note)
      << "," << q("tier")      << ":" << q(m ? m->tier : "")
      << "," << q("bed")       << ":" << q(m ? m->bed  : "")
      << "}";
    return o.str();
}

} // namespace reservation
