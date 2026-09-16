// ============================================================
//  hotel.cpp — ดูสารบัญที่ include/hotel.h
// ============================================================
#include "../include/hotel.h"
#include "../include/reservation.h"
#include "../include/user.h"
#include "../include/utils.h"
#include "../include/xlsx.h"

#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <ctime>

namespace hotel {

// ============================================================
// PART 2 — ตัวแปรกลาง
// ============================================================
std::vector<Room>     g_rooms;
std::vector<RoomType> g_types;
std::vector<AuditLog> g_audits;
std::mutex            g_mtx;

const char* F_DATA   = "data/hotel.xlsx";
const char* SH_ROOMS = "rooms";
const char* SH_TYPES = "room_types";
const char* SH_BOOK  = "bookings";
const char* SH_USERS = "users";
const char* SH_AUDIT = "audit_log";

static const std::vector<std::string> H_ROOMS =
    {"room_id","floor","bed_type","tier","price","note"};
static const std::vector<std::string> H_TYPES =
    {"tier","bed_type","display_name","amenities"};
static const std::vector<std::string> H_BOOK =
    {"booking_id","room_id","booker","phone","email",
     "check_in","check_out","nights","total","status","created_at","note"};
static const std::vector<std::string> H_USERS =
    {"username","password","role","full_name","phone","email"};
static const std::vector<std::string> H_AUDIT =
    {"log_id","timestamp","actor_user","actor_role","action_type","target_entity","diff"};


// ============================================================
// PART 3 — โหลดและบันทึก
// ============================================================
bool loadAll() {
    using utils::at;
    g_rooms.clear();
    g_types.clear();
    g_audits.clear();
    reservation::g_books.clear();

    xlsx::Book book;
    if (!xlsx::read(F_DATA, book)) return false;

    if (const xlsx::Sheet* sh = xlsx::find(book, SH_ROOMS)) {
        for (auto& r : sh->rows) {
            if (at(r,0).empty()) continue;
            Room m;
            m.id    = at(r,0);
            m.floor = at(r,1);
            m.bed   = at(r,2);
            m.tier  = at(r,3);
            m.price = std::atol(at(r,4).c_str());
            m.note  = at(r,5);
            g_rooms.push_back(m);
        }
    }

    if (const xlsx::Sheet* sh = xlsx::find(book, SH_TYPES)) {
        for (auto& r : sh->rows) {
            if (at(r,0).empty()) continue;
            RoomType t;
            t.tier = at(r,0);
            t.bed  = at(r,1);
            t.name = at(r,2);
            std::string a = at(r,3), cur;
            for (char c : a) {
                if (c == '|') { if (!cur.empty()) t.amenities.push_back(cur); cur.clear(); }
                else cur += c;
            }
            if (!cur.empty()) t.amenities.push_back(cur);
            g_types.push_back(t);
        }
    }

    if (const xlsx::Sheet* sh = xlsx::find(book, SH_BOOK)) {
        for (auto& r : sh->rows) {
            if (at(r,0).empty()) continue;
            Booking b;
            b.id        = at(r,0);
            b.roomId    = at(r,1);
            b.booker    = at(r,2);
            b.phone     = at(r,3);
            b.email     = at(r,4);
            b.checkIn   = at(r,5);
            b.checkOut  = at(r,6);
            b.nights    = std::atoi(at(r,7).c_str());
            b.total     = std::atol(at(r,8).c_str());
            b.status    = at(r,9);
            b.createdAt = at(r,10);
            b.note      = at(r,11);
            reservation::g_books.push_back(b);
        }
    }

    if (const xlsx::Sheet* sh = xlsx::find(book, SH_USERS)) {
        user::loadFromRows(sh->rows);
    } else {
        user::seedDefaults();
    }

    if (const xlsx::Sheet* sh = xlsx::find(book, SH_AUDIT)) {
        for (auto& r : sh->rows) {
            if (at(r,0).empty()) continue;
            AuditLog al;
            al.id           = at(r,0);
            al.timestamp    = at(r,1);
            al.actorUser    = at(r,2);
            al.actorRole    = at(r,3);
            al.actionType   = at(r,4);
            al.targetEntity = at(r,5);
            al.diff         = at(r,6);
            g_audits.push_back(al);
        }
    }

    bool ok = !g_rooms.empty();
    if (ok) {
        std::string backupPath;
        createBackupSnapshot(&backupPath);
    }
    return ok;
}

bool createBackupSnapshot(std::string* outBackupPath) {
    namespace fs = std::filesystem;
    try {
        fs::create_directories("data/backups");
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        char buf[64];
        std::strftime(buf, sizeof(buf), "data/backups/hotel_%Y%m%d_%H%M%S.xlsx", &tm);
        std::string backupFile = buf;

        if (fs::exists(F_DATA)) {
            fs::copy_file(F_DATA, backupFile, fs::copy_options::overwrite_existing);
            if (outBackupPath) *outBackupPath = backupFile;
            std::cout << "[BACKUP] สร้างสำรองฐานข้อมูลสำเร็จ: " << backupFile << "\n";
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "[BACKUP ERROR] " << e.what() << "\n";
    }
    return false;
}

static bool g_lastSaveOk = true;
bool lastSaveOk() { return g_lastSaveOk; }

bool saveAll() {
    xlsx::Book book;

    xlsx::Sheet sr; sr.name = SH_ROOMS; sr.header = H_ROOMS;
    for (auto& m : g_rooms)
        sr.rows.push_back({m.id, m.floor, m.bed, m.tier, std::to_string(m.price), m.note});
    book.push_back(sr);

    xlsx::Sheet st; st.name = SH_TYPES; st.header = H_TYPES;
    for (auto& t : g_types) {
        std::string a;
        for (size_t i = 0; i < t.amenities.size(); ++i) { if (i) a += "|"; a += t.amenities[i]; }
        st.rows.push_back({t.tier, t.bed, t.name, a});
    }
    book.push_back(st);

    xlsx::Sheet sb; sb.name = SH_BOOK; sb.header = H_BOOK;
    for (auto& b : reservation::g_books)
        sb.rows.push_back({b.id, b.roomId, b.booker, b.phone, b.email,
                           b.checkIn, b.checkOut, std::to_string(b.nights),
                           std::to_string(b.total), b.status, b.createdAt, b.note});
    book.push_back(sb);

    xlsx::Sheet su; su.name = SH_USERS; su.header = H_USERS;
    su.rows = user::saveToRows();
    book.push_back(su);

    xlsx::Sheet sa; sa.name = SH_AUDIT; sa.header = H_AUDIT;
    for (auto& al : g_audits)
        sa.rows.push_back({al.id, al.timestamp, al.actorUser, al.actorRole,
                           al.actionType, al.targetEntity, al.diff});
    book.push_back(sa);

    // Staging write & lock retry loop (retry up to 3 attempts with 300ms delay)
    g_lastSaveOk = false;
    for (int attempt = 1; attempt <= 3; ++attempt) {
        g_lastSaveOk = xlsx::write(F_DATA, book);
        if (g_lastSaveOk) break;
        std::cerr << "[WARN] เขียน " << F_DATA << " ไม่สำเร็จ (พยายามครั้งที่ " << attempt << "/3)...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    if (!g_lastSaveOk)
        std::cerr << "[ERROR] เขียน " << F_DATA << " ล้มเหลวครบ 3 ครั้ง (ไฟล์อาจถูกเปิดค้างใน Excel)\n";
    return g_lastSaveOk;
}

void logAction(const std::string& actorUser, const std::string& actorRole,
               const std::string& actionType, const std::string& targetEntity,
               const std::string& diff) {
    AuditLog al;
    char buf[24];
    snprintf(buf, sizeof(buf), "LOG-%04zu", g_audits.size() + 1);
    al.id           = buf;
    al.timestamp    = utils::nowStr();
    al.actorUser    = actorUser.empty() ? "system" : actorUser;
    al.actorRole    = actorRole.empty() ? "system" : actorRole;
    al.actionType   = actionType;
    al.targetEntity = targetEntity;
    al.diff         = diff;
    g_audits.push_back(al);
}

std::string auditLogsJson() {
    using utils::q;
    std::ostringstream o;
    o << "[";
    for (size_t i = 0; i < g_audits.size(); ++i) {
        if (i) o << ",";
        // แสดงรายการจากล่าสุดไปเก่าสุด
        const auto& a = g_audits[g_audits.size() - 1 - i];
        o << "{" << q("id")           << ":" << q(a.id)
          << "," << q("timestamp")    << ":" << q(a.timestamp)
          << "," << q("actorUser")    << ":" << q(a.actorUser)
          << "," << q("actorRole")    << ":" << q(a.actorRole)
          << "," << q("actionType")   << ":" << q(a.actionType)
          << "," << q("targetEntity") << ":" << q(a.targetEntity)
          << "," << q("diff")         << ":" << q(a.diff)
          << "}";
    }
    o << "]";
    return o.str();
}


// ============================================================
// PART 4 — ค้นหาและแปลงเป็น JSON
// ============================================================
Room* findRoom(const std::string& id) {
    for (auto& r : g_rooms) if (r.id == id) return &r;
    return nullptr;
}

RoomType* findType(const std::string& tier, const std::string& bed) {
    for (auto& t : g_types) if (t.tier == tier && t.bed == bed) return &t;
    return nullptr;
}

std::string roomJsonPublic(const Room& m) {
    using utils::q;
    RoomType* t = findType(m.tier, m.bed);
    Booking*  b = reservation::activeFor(m.id);

    std::ostringstream o;
    o << "{" << q("number")   << ":" << q(m.id)
      << "," << q("floor")    << ":" << q(m.floor)
      << "," << q("bed")      << ":" << q(m.bed)
      << "," << q("tier")     << ":" << q(m.tier)
      << "," << q("price")    << ":" << m.price
      << "," << q("note")     << ":" << q(m.note)
      << "," << q("typeName") << ":" << q(t ? t->name : m.bed)
      << "," << q("booked")   << ":" << (b ? "true" : "false")
      << "," << q("booking")  << ":";
    // หน้าผู้ใช้ทั่วไปเห็นแค่สถานะและช่วงวันที่ ไม่เห็นชื่อ/เบอร์ของผู้จองคนอื่น
    if (b) o << "{" << q("status")   << ":" << q(b->status)
             << "," << q("checkIn")  << ":" << q(b->checkIn)
             << "," << q("checkOut") << ":" << q(b->checkOut) << "}";
    else   o << "null";
    o       << "," << q("detail")   << ":[";
    if (t) for (size_t i = 0; i < t->amenities.size(); ++i) {
        if (i) o << ",";
        o << q(t->amenities[i]);
    }
    o << "]";

    // ส่งช่วงวันที่ที่ถูกจองไปทั้งหมด เพื่อให้หน้าเว็บใช้กรองค้นหาตามช่วงวันที่ได้ทันที
    o << "," << q("activeBookings") << ":[";
    bool firstB = true;
    for (const auto& bk : reservation::g_books) {
        if (bk.roomId == m.id && reservation::holdsRoom(bk.status)) {
            if (!firstB) o << ",";
            firstB = false;
            o << "{" << q("id")       << ":" << q(bk.id)
              << "," << q("checkIn")  << ":" << q(bk.checkIn)
              << "," << q("checkOut") << ":" << q(bk.checkOut)
              << "," << q("status")   << ":" << q(bk.status)
              << "}";
        }
    }
    o << "]}";
    return o.str();
}

} // namespace hotel
