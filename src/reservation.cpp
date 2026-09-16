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

bool datesOverlap(const std::string& s1, const std::string& e1,
                  const std::string& s2, const std::string& e2) {
    if (s1.empty() || e1.empty() || s2.empty() || e2.empty()) return false;
    return (std::max(s1, s2) < std::min(e1, e2));
}

Booking* collisionFor(const std::string& roomId, const std::string& checkIn,
                      int nights, const std::string& excludeBookingId) {
    std::string checkOut = utils::addDays(checkIn, nights);
    for (auto& b : g_books) {
        if (b.roomId != roomId) continue;
        if (!holdsRoom(b.status)) continue;
        if (!excludeBookingId.empty() && b.id == excludeBookingId) continue;
        if (datesOverlap(checkIn, checkOut, b.checkIn, b.checkOut))
            return &b;
    }
    return nullptr;
}

Booking* activeFor(const std::string& roomId) {
    std::string today = utils::todayStr();
    // ลำดับ 1: แขกที่กำลังพักอยู่จริง (checkin)
    for (auto& b : g_books)
        if (b.roomId == roomId && b.status == "checkin") return &b;

    // ลำดับ 2: แขกที่มีการจองครอบคลุมวันนี้
    for (auto& b : g_books)
        if (b.roomId == roomId && holdsRoom(b.status) && b.checkIn <= today && today < b.checkOut)
            return &b;

    // ลำดับ 3: แขกที่กำลังจะเข้าพักเร็วที่สุดในอนาคต
    Booking* earliest = nullptr;
    for (auto& b : g_books) {
        if (b.roomId == roomId && holdsRoom(b.status) && b.checkIn >= today) {
            if (!earliest || b.checkIn < earliest->checkIn) earliest = &b;
        }
    }
    if (earliest) return earliest;

    // ลำดับ 4: รายการจองใดๆ ที่ยังกินห้องอยู่
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

    // ตรวจสอบการทับซ้อนของช่วงวันที่ (Date-Interval Collision Check)
    Booking* col = collisionFor(roomId, checkIn, nights);
    if (col) {
        return fail("409 Conflict", "ห้อง " + roomId + " ไม่ว่างในช่วงวันที่ " +
                                    col->checkIn + " ถึง " + col->checkOut +
                                    " (ติดรายการจอง " + col->id + " ของคุณ " + col->booker + ")");
    }

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

    // บันทึกลง Audit Log
    hotel::logAction(booker, (status == "checkin" ? "staff" : "guest"),
                     "BOOKING_CREATED", "Booking " + b.id,
                     "Room " + b.roomId + ", " + b.checkIn + " -> " + b.checkOut +
                     " (" + std::to_string(b.nights) + " nights, " + std::to_string(b.total) + " THB)");

    Result r; r.ok = true; r.booking = b;
    return r;
}

Result extendStay(const std::string& id, int additionalNights, const std::string& note) {
    Booking* b = find(id);
    if (!b) return fail("404 Not Found", "ไม่พบรายการจองนี้");
    if (!holdsRoom(b->status))
        return fail("400 Bad Request", "สามารถขยายเวลาพักได้เฉพาะรายการที่กำลังพักอยู่ (checkin) หรือรอเข้าพัก (wait)");
    if (additionalNights < 1 || additionalNights > MAX_NIGHTS)
        return fail("400 Bad Request", "จำนวนคืนที่ขอพักต่อต้องอยู่ระหว่าง 1 ถึง " + std::to_string(MAX_NIGHTS));
    if (b->nights + additionalNights > 90)
        return fail("400 Bad Request", "ยอดรวมการพักติดต่อกันสูงสุดไม่เกิน 90 คืน");

    std::string newCheckOut = utils::addDays(b->checkOut, additionalNights);

    // ตรวจสอบว่าช่วงวันที่จะขอพักต่อ [b->checkOut, newCheckOut) มีใครจองไว้หรือไม่
    Booking* col = collisionFor(b->roomId, b->checkOut, additionalNights, b->id);
    if (col) {
        return fail("409 Conflict", "ไม่สามารถพักต่อได้ เนื่องจากห้อง " + b->roomId +
                                    " มีผู้จองต่อไว้แล้วในวันที่ " + col->checkIn + " ถึง " + col->checkOut +
                                    " (" + col->id + ")");
    }

    Room* m = hotel::findRoom(b->roomId);
    int prevNights = b->nights;
    long prevTotal = b->total;
    std::string prevOut = b->checkOut;

    b->nights += additionalNights;
    b->checkOut = newCheckOut;
    b->total = (long)b->nights * (m ? m->price : 0);
    if (!note.empty()) {
        if (!b->note.empty()) b->note += " | ";
        b->note += note;
    }

    hotel::saveAll();
    std::cout << "[EXTEND] " << b->id << " +" << additionalNights << " คืน (รวม " << b->nights
              << " คืน = " << b->total << " บาท)\n";

    // บันทึกลง Audit Log
    hotel::logAction("system", "staff", "STAY_EXTENDED", "Booking " + b->id,
                     "Extended +" + std::to_string(additionalNights) + " nights (" +
                     prevOut + " -> " + b->checkOut + ", " +
                     std::to_string(prevNights) + " -> " + std::to_string(b->nights) + " nights, " +
                     std::to_string(prevTotal) + " -> " + std::to_string(b->total) + " THB)");

    Result r; r.ok = true; r.booking = *b;
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

    std::string targetCheckIn = (checkIn.size() >= 10) ? checkIn : b->checkIn;

    // ตรวจสอบการชนของช่วงวันที่ใหม่
    Booking* col = collisionFor(b->roomId, targetCheckIn, nights, b->id);
    if (col) {
        return fail("409 Conflict", "ช่วงวันที่แก้ไขชนกับรายการจอง " + col->id +
                                    " (" + col->checkIn + " ถึง " + col->checkOut + ")");
    }

    Room* m = hotel::findRoom(b->roomId);
    b->booker = booker;
    b->phone  = phone;
    b->email  = email;
    b->note   = note;
    b->nights = nights;
    b->checkIn = targetCheckIn;
    b->checkOut = utils::addDays(b->checkIn, nights);
    b->total    = (long)nights * (m ? m->price : 0);

    hotel::saveAll();
    std::cout << "[EDIT] " << b->id << "\n";

    // บันทึกลง Audit Log
    hotel::logAction("admin", "admin", "BOOKING_EDITED", "Booking " + b->id,
                     "Updated details (" + b->booker + ", " + b->checkIn + "->" + b->checkOut + ", " +
                     std::to_string(b->nights) + " nights, " + std::to_string(b->total) + " THB)");

    Result r; r.ok = true; r.booking = *b;
    return r;
}

Result setStatus(const std::string& id, const std::string& status) {
    if (status != "wait" && status != "checkin" && status != "checkout" && status != "cancelled")
        return fail("400 Bad Request", "สถานะไม่ถูกต้อง");

    Booking* b = find(id);
    if (!b) return fail("404 Not Found", "ไม่พบรายการจองนี้");

    // ถ้าจะย้ายกลับมาเป็นสถานะที่กินห้อง ต้องไม่ชนกับรายการอื่นที่กินห้องในช่วงเวลาเดียวกัน
    if (holdsRoom(status) && !holdsRoom(b->status)) {
        Booking* col = collisionFor(b->roomId, b->checkIn, b->nights, b->id);
        if (col) {
            return fail("409 Conflict", "ห้องนี้ไม่ว่างในช่วงดังกล่าวเนื่องจากชนกับรายการ " + col->id);
        }
    }

    std::string prevStatus = b->status;
    b->status = status;
    hotel::saveAll();
    std::cout << "[STATUS] " << b->id << " -> " << status << "\n";

    // บันทึกลง Audit Log
    hotel::logAction("staff", "staff", "STATUS_CHANGED", "Booking " + b->id,
                     prevStatus + " -> " + status + " (Room " + b->roomId + ")");

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
