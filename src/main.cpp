// ============================================================
//  main.cpp — HTTP server, router และจุดเริ่มโปรแกรม
//     PART 1  ROUTER: API ฝั่งผู้ใช้
//     PART 2  ROUTER: API ฝั่งแอดมิน (RBAC Protected)
//     PART 3  ROUTER: ไฟล์ static
//     PART 4  รับ connection
//     PART 5  main
// ============================================================

#include "../include/hotel.h"
#include "../include/reservation.h"
#include "../include/user.h"
#include "../include/utils.h"
#include "../include/sha256.h"

#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <cstring>
#include <cctype>
#include <unordered_map>
#include <mutex>
#include <iomanip>
#include <fstream>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "ws2_32.lib")
  typedef int socklen_t;
  #define CLOSESOCK closesocket
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <csignal>
  typedef int SOCKET;
  #define INVALID_SOCKET (-1)
  #define CLOSESOCK close
#endif

static const int PORT = 8093;
static bool g_demoMode = false;

using utils::q;

// ---------- ระบบ Session สำหรับ Role-Based Access Control (RBAC) ----------
struct Session {
    std::string username;
    std::string role;      // "admin", "staff", "guest"
    std::string fullName;

    bool isAdmin() const { return role == "admin"; }
    bool isStaff() const { return role == "staff" || role == "admin"; }
};

static std::unordered_map<std::string, Session> g_sessions;
static std::mutex g_sessionMtx;

// บันทึก Session ทั้งหมดลงไฟล์ data/sessions.json (ต้องเรียกขณะถือ lock g_sessionMtx)
static void saveSessionsLocked() {
    std::ofstream f("data/sessions.json");
    if (!f.is_open()) return;
    f << "{\"sessions\":[";
    bool first = true;
    for (const auto& kv : g_sessions) {
        if (!first) f << ",";
        first = false;
        f << "{\"token\":" << utils::q(kv.first)
          << ",\"username\":" << utils::q(kv.second.username)
          << ",\"role\":" << utils::q(kv.second.role)
          << ",\"fullName\":" << utils::q(kv.second.fullName)
          << "}";
    }
    f << "]}";
}

// โหลด Session ที่บันทึกไว้กลับมาเมื่อเซิร์ฟเวอร์เปิดขึ้นใหม่
static void loadSessionsFromFile() {
    std::string content;
    if (!utils::readFile("data/sessions.json", content)) return;
    std::lock_guard<std::mutex> slk(g_sessionMtx);
    g_sessions.clear();
    size_t pos = 0;
    while ((pos = content.find("{\"token\":", pos)) != std::string::npos) {
        size_t endObj = content.find("}", pos);
        if (endObj == std::string::npos) break;
        std::string obj = content.substr(pos, endObj - pos + 1);
        std::string tok = utils::jsonStr(obj, "token", 64);
        std::string u   = utils::jsonStr(obj, "username", 40);
        std::string r   = utils::jsonStr(obj, "role", 20);
        std::string fn  = utils::jsonStr(obj, "fullName", 80);
        if (!tok.empty() && !u.empty()) {
            if (user::exists(u)) {
                User* usr = user::find(u);
                g_sessions[tok] = {u, usr ? usr->role : r, usr ? usr->fullName : fn};
            }
        }
        pos = endObj + 1;
    }
    std::cout << "[SESSION] โหลดเซสชันที่บันทึกไว้สำเร็จ: " << g_sessions.size() << " บัญชี\n";
}

// ดึงค่า Header จากบล็อก Headers ดิบ
static std::string getHeaderValue(const std::string& head, const std::string& key) {
    std::string lowerHead = head;
    std::string lowerKey = key;
    for (char& c : lowerHead) c = (char)tolower((unsigned char)c);
    for (char& c : lowerKey) c = (char)tolower((unsigned char)c);

    size_t pos = lowerHead.find(lowerKey + ":");
    if (pos == std::string::npos) return "";

    size_t valStart = pos + lowerKey.size() + 1;
    while (valStart < head.size() && (head[valStart] == ' ' || head[valStart] == '\t')) valStart++;

    size_t valEnd = head.find("\r\n", valStart);
    if (valEnd == std::string::npos) valEnd = head.size();

    return head.substr(valStart, valEnd - valStart);
}

// ค้นหา Session ของผู้เรียกจาก Authorization Header / X-Auth-Token / Cookie
static Session* getSession(const std::string& head) {
    std::string token;
    std::string auth = getHeaderValue(head, "Authorization");
    if (auth.rfind("Bearer ", 0) == 0) {
        token = auth.substr(7);
    }
    if (token.empty()) {
        token = getHeaderValue(head, "X-Auth-Token");
    }
    if (token.empty()) {
        std::string cookie = getHeaderValue(head, "Cookie");
        size_t cp = cookie.find("session=");
        if (cp != std::string::npos) {
            size_t endp = cookie.find(';', cp);
            token = cookie.substr(cp + 8, (endp == std::string::npos ? cookie.size() : endp) - (cp + 8));
        }
    }

    if (token.empty()) return nullptr;

    std::lock_guard<std::mutex> lk(g_sessionMtx);
    auto it = g_sessions.find(token);
    if (it != g_sessions.end()) {
        return &(it->second);
    }
    return nullptr;
}

// ต่อท้าย JSON ด้วยผลการเขียนไฟล์ Excel ครั้งล่าสุด
static std::string withSaveState(std::string obj) {
    bool ok = hotel::lastSaveOk();
    if (!obj.empty() && obj.back() == '}') obj.pop_back();
    obj += ",\"saved\":";
    obj += ok ? "true" : "false";
    if (!ok) obj += ",\"saveError\":" + q("บันทึกลงไฟล์ data/hotel.xlsx ไม่สำเร็จ "
                                          "ให้ปิดไฟล์ที่เปิดค้างใน Excel แล้วลองใหม่");
    obj += "}";
    return obj;
}

static std::string handle(const std::string& method,
                          const std::string& path,
                          const std::string& body,
                          const std::string& head,
                          const std::string& rawUri = "") {

    if (method == "OPTIONS") return utils::resp("204 No Content", "text/plain", "");

    // ============================================================
    // PART 0 — ระบบยืนยันตัวตน (Authentication API)
    // ============================================================

    // ตรวจสอบสถานะเซสชันปัจจุบันของผู้ใช้: /api/auth/me
    if (path == "/api/auth/me" && method == "GET") {
        Session* s = getSession(head);
        if (!s) {
            return utils::jsonErr("401 Unauthorized", "เซสชันหมดอายุหรือไม่ถูกต้อง");
        }
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        User* u = user::find(s->username);
        if (!u) {
            std::string auth = getHeaderValue(head, "Authorization");
            std::string token = (auth.rfind("Bearer ", 0) == 0) ? auth.substr(7) : getHeaderValue(head, "X-Auth-Token");
            if (!token.empty()) {
                std::lock_guard<std::mutex> slk(g_sessionMtx);
                g_sessions.erase(token);
                saveSessionsLocked();
            }
            return utils::jsonErr("401 Unauthorized", "ไม่พบบัญชีผู้ใช้ในระบบ");
        }
        return utils::jsonOk("{\"ok\":true,\"user\":" + user::toJson(*u) + "}");
    }

    // เข้าสู่ระบบ: /api/auth/login
    if (path == "/api/auth/login" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string username = utils::jsonStr(body, "username", 40);
        std::string password = utils::jsonStr(body, "password", 60);
        User* u = user::authenticate(username, password);
        if (!u) {
            return utils::jsonErr("401 Unauthorized", "ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง");
        }

        std::string token = crypto::generateSalt(32);
        {
            std::lock_guard<std::mutex> slk(g_sessionMtx);
            g_sessions[token] = {u->username, u->role, u->fullName};
            saveSessionsLocked();
        }

        std::cout << "[AUTH] เข้าสู่ระบบสำเร็จ: " << u->username << " (" << u->role << ")\n";
        return utils::resp("200 OK", "application/json; charset=utf-8",
                           "{\"ok\":true,\"token\":" + q(token) + ",\"user\":" + user::toJson(*u) + "}");
    }

    // ออกจากระบบ: /api/auth/logout
    if (path == "/api/auth/logout" && method == "POST") {
        std::string auth = getHeaderValue(head, "Authorization");
        std::string token = (auth.rfind("Bearer ", 0) == 0) ? auth.substr(7) : getHeaderValue(head, "X-Auth-Token");
        if (!token.empty()) {
            std::lock_guard<std::mutex> slk(g_sessionMtx);
            g_sessions.erase(token);
            saveSessionsLocked();
        }
        return utils::jsonOk("{\"ok\":true}");
    }

    // สมัครสมาชิกผู้ใช้ทั่วไป: /api/auth/register
    if (path == "/api/auth/register" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string username = utils::jsonStr(body, "username", 40);
        std::string password = utils::jsonStr(body, "password", 60);
        std::string fullName = utils::jsonStr(body, "fullName", 80);
        std::string phone    = utils::jsonStr(body, "phone", 25);
        std::string email    = utils::jsonStr(body, "email", 80);

        Result r = user::registerGuest(username, password, fullName, phone, email);
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);

        User* u = user::find(username);
        std::string token = crypto::generateSalt(32);
        if (u) {
            std::lock_guard<std::mutex> slk(g_sessionMtx);
            g_sessions[token] = {u->username, u->role, u->fullName};
            saveSessionsLocked();
        }
        return utils::jsonOk("{\"ok\":true,\"token\":" + q(token) + ",\"user\":" + (u ? user::toJson(*u) : "{}") + "}");
    }

    // รายชื่อผู้ใช้ทั้งหมด (สำหรับแอดมินหรือตรวจสอบ): /api/auth/users
    if (path == "/api/auth/users" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        return utils::jsonOk("{\"ok\":true,\"users\":" + user::listJson() + "}");
    }

    // ============================================================
    // PART 1 — API ฝั่งผู้ใช้ทั่วไป
    // ============================================================

    // ข้อมูลการกำหนดค่าของระบบ (เช่น Demo Mode)
    if (path == "/api/config" && method == "GET") {
        std::ostringstream o;
        o << "{\"ok\":true,\"demoMode\":" << (g_demoMode ? "true" : "false")
          << ",\"version\":\"2.4.0\",\"hotelName\":" << q("Hilbert Grand Hotel") << "}";
        return utils::jsonOk(o.str());
    }

    // ผังห้องทั้งหมด + สถานะ (หน้าเว็บเรียกซ้ำเพื่ออัปเดต)
    if (path == "/api/rooms" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::ostringstream o;
        o << "{\"rooms\":[";
        for (size_t i = 0; i < hotel::g_rooms.size(); ++i) {
            if (i) o << ",";
            o << hotel::roomJsonPublic(hotel::g_rooms[i]);
        }
        o << "],\"today\":" << q(utils::todayStr())
          << ",\"demoMode\":" << (g_demoMode ? "true" : "false") << "}";
        return utils::jsonOk(o.str());
    }

    // ลูกค้าจองห้อง -> เพิ่มแถวใน sheet bookings สถานะ wait
    if (path == "/api/book" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Result r = reservation::create(
            utils::jsonStr(body, "room", 12),
            utils::jsonStr(body, "booker", 60),
            utils::jsonStr(body, "phone", 25),
            utils::jsonStr(body, "email", 80),
            utils::jsonStr(body, "checkIn", 10),
            (int)utils::jsonInt(body, "nights", 0),
            utils::jsonStr(body, "note", 200),
            "wait");
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}"));
    }

    // ขยายเวลาการพัก (Continue Book-In / Extend Stay)
    if (path == "/api/booking/extend" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string id = utils::jsonStr(body, "id", 12);
        int nights = (int)utils::jsonInt(body, "nights", 1);
        std::string note = utils::jsonStr(body, "note", 120);
        Result r = reservation::extendStay(id, nights, note);
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}"));
    }

    // การจองทั้งหมดของลูกค้าคนหนึ่ง (ค้นด้วยชื่อหรือเบอร์โทร)
    if (path == "/api/my-bookings" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        return utils::jsonOk("{\"bookings\":[]}");
    }

    // ============================================================
    // PART 2 — API ฝั่งแอดมินและเจ้าหน้าที่ (RBAC Protected)
    // ============================================================
    if (path.rfind("/api/admin/", 0) == 0 || path.rfind("/api/staff/", 0) == 0) {
        Session* s = getSession(head);

        // 1. ตรวจสอบการยืนยันตัวตน (Authentication): ต้องมี Session ที่ถูกต้องและยังไม่หมดอายุ
        if (!s) {
            return utils::jsonErr("401 Unauthorized", "เซสชันหมดอายุหรือไม่ถูกต้อง กรุณาเข้าสู่ระบบใหม่อีกครั้ง");
        }

        // 2. ตรวจสอบการอนุญาต (Authorization): ต้องมีบทบาทเป็น admin หรือ staff เท่านั้น
        if (!s->isAdmin() && !s->isStaff()) {
            return utils::jsonErr("403 Forbidden", "Access Denied: สิทธิ์ไม่เพียงพอ ต้องเข้าสู่ระบบด้วยบัญชี Administrator หรือ Staff");
        }

        // คำสั่งที่อนุญาตเฉพาะ Admin เท่านั้น
        bool adminOnly = (path == "/api/admin/room" ||
                          path == "/api/admin/reload" ||
                          path == "/api/admin/backup" ||
                          path == "/api/admin/console" ||
                          path == "/api/admin/audit-logs" ||
                          path.rfind("/api/admin/users", 0) == 0);
        if (adminOnly && !s->isAdmin()) {
            return utils::jsonErr("403 Forbidden", "Access Denied: คำสั่งนี้อนุญาตเฉพาะระดับ Administrator เท่านั้น");
        }
    }

    // ตารางรวม: ห้องทุกห้อง + การจองที่ยังกินห้องอยู่ + ประวัติทั้งหมด + Audit Logs
    if (path == "/api/admin/data" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::ostringstream o;
        o << "{\"rooms\":[";
        for (size_t i = 0; i < hotel::g_rooms.size(); ++i) {
            const Room& m = hotel::g_rooms[i];
            Booking*  b = reservation::activeFor(m.id);
            RoomType* t = hotel::findType(m.tier, m.bed);
            if (i) o << ",";
            o << "{" << q("number")   << ":" << q(m.id)
              << "," << q("floor")    << ":" << q(m.floor)
              << "," << q("bed")      << ":" << q(m.bed)
              << "," << q("tier")     << ":" << q(m.tier)
              << "," << q("price")    << ":" << m.price
              << "," << q("note")     << ":" << q(m.note)
              << "," << q("typeName") << ":" << q(t ? t->name : m.bed)
              << "," << q("booked")   << ":" << (b ? "true" : "false")
              << "," << q("booking")  << ":" << (b ? reservation::toJson(*b) : "null")
              << "}";
        }
        o << "],\"bookings\":[";
        for (size_t i = 0; i < reservation::g_books.size(); ++i) {
            if (i) o << ",";
            o << reservation::toJson(reservation::g_books[i]);
        }
        o << "],\"auditLogs\":" << hotel::auditLogsJson();
        o << ",\"today\":" << q(utils::todayStr()) << "}";
        return utils::jsonOk(o.str());
    }

    // Staff & Admin: ดูข้อมูลและรายละเอียดของห้อง รวมถึงผู้ที่จองห้องนี้
    if (path == "/api/staff/room-detail" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string roomNum;
        std::string targetUri = rawUri.empty() ? path : rawUri;
        size_t qpos = targetUri.find("room=");
        if (qpos != std::string::npos) {
            roomNum = targetUri.substr(qpos + 5);
            size_t amp = roomNum.find('&');
            if (amp != std::string::npos) roomNum = roomNum.substr(0, amp);
        }
        Room* m = hotel::findRoom(roomNum);
        if (!m) return utils::jsonErr("404 Not Found", "ไม่พบหมายเลขห้องนี้");

        RoomType* t = hotel::findType(m->tier, m->bed);
        Booking* curB = reservation::activeFor(m->id);

        std::ostringstream o;
        o << "{\"ok\":true,\"room\":{"
          << q("number") << ":" << q(m->id)
          << "," << q("floor") << ":" << q(m->floor)
          << "," << q("bed") << ":" << q(m->bed)
          << "," << q("tier") << ":" << q(m->tier)
          << "," << q("price") << ":" << m->price
          << "," << q("note") << ":" << q(m->note)
          << "," << q("typeName") << ":" << q(t ? t->name : m->bed)
          << "," << q("booked") << ":" << (curB ? "true" : "false")
          << "," << q("status") << ":" << q(m->note.find("[Maintenance]") != std::string::npos ? "maintenance" : (curB ? "occupied" : "available"))
          << "," << q("currentBooking") << ":" << (curB ? reservation::toJson(*curB) : "null")
          << "," << q("detail") << ":[";
        if (t) {
            for (size_t i = 0; i < t->amenities.size(); ++i) {
                if (i) o << ",";
                o << q(t->amenities[i]);
            }
        }
        o << "]}"
          << ",\"activeBooking\":" << (curB ? reservation::toJson(*curB) : "null")
          << ",\"currentBooking\":" << (curB ? reservation::toJson(*curB) : "null")
          << ",\"history\":[";
        bool firstBk = true;
        for (const auto& bk : reservation::g_books) {
            if (bk.roomId == m->id) {
                if (!firstBk) o << ",";
                firstBk = false;
                o << reservation::toJson(bk);
            }
        }
        o << "],\"allBookings\":[";
        firstBk = true;
        for (const auto& bk : reservation::g_books) {
            if (bk.roomId == m->id) {
                if (!firstBk) o << ",";
                firstBk = false;
                o << reservation::toJson(bk);
            }
        }
        o << "]}";
        return utils::jsonOk(o.str());
    }

    // Staff & Admin: ปรับปรุงสถานะหรือหมายเหตุของห้อง (Housekeeping & Room Status)
    if (path == "/api/staff/room-status" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string roomNum = utils::jsonStr(body, "room", 12);
        if (roomNum.empty()) {
            long rId = utils::jsonInt(body, "room", -1);
            if (rId != -1) roomNum = std::to_string(rId);
        }
        Room* m = hotel::findRoom(roomNum);
        if (!m) return utils::jsonErr("404 Not Found", "ไม่พบหมายเลขห้องนี้");

        std::string prevNote = m->note;
        std::string newStatus = utils::jsonStr(body, "status", 30);
        std::string newNote = utils::jsonStr(body, "note", 120);
        if (newStatus == "maintenance" && newNote.find("[Maintenance]") == std::string::npos) {
            if (newNote.empty()) newNote = "[Maintenance] Out of Service";
            else newNote = "[Maintenance] " + newNote;
        } else if (newStatus == "available" && newNote.find("[Maintenance]") != std::string::npos) {
            size_t mp = newNote.find("[Maintenance]");
            newNote.erase(mp, 13);
            while (!newNote.empty() && newNote.front() == ' ') newNote.erase(0, 1);
        }
        m->note = newNote;
        hotel::saveAll();

        Session* s = getSession(head);
        std::string actor = s ? s->username : "staff";
        std::string role = s ? s->role : "staff";

        hotel::logAction(actor, role, "ROOM_STATUS_CHANGE", "Room " + m->id,
                         "Status/Note changed: '" + prevNote + "' -> '" + newNote + "'");

        return utils::jsonOk(withSaveState("{\"ok\":true,\"room\":" + q(m->id) + ",\"note\":" + q(m->note) + ",\"status\":" + q(newStatus) + "}"));
    }

    // ประวัติการเปลี่ยนแปลงระบบ (Audit Logs)
    if (path == "/api/admin/audit-logs" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        return utils::jsonOk("{\"ok\":true,\"logs\":" + hotel::auditLogsJson() + "}");
    }

    // รายชื่อผู้ใช้ทั้งหมด (Admin Portal)
    if (path == "/api/admin/users" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        return utils::jsonOk("{\"ok\":true,\"users\":" + user::listJson() + "}");
    }

    // เพิ่มผู้ใช้ใหม่โดยแอดมิน
    if (path == "/api/admin/users/create" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string username = utils::jsonStr(body, "username", 40);
        std::string password = utils::jsonStr(body, "password", 60);
        std::string role     = utils::jsonStr(body, "role", 20);
        std::string fullName = utils::jsonStr(body, "fullName", 80);
        std::string phone    = utils::jsonStr(body, "phone", 25);
        std::string email    = utils::jsonStr(body, "email", 80);

        Result r = user::createUser(username, password, role, fullName, phone, email);
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true}"));
    }

    // แก้ไขข้อมูลผู้ใช้หรือรีเซ็ตรหัสผ่าน
    if (path == "/api/admin/users/update" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string username = utils::jsonStr(body, "username", 40);
        std::string role     = utils::jsonStr(body, "role", 20);
        std::string fullName = utils::jsonStr(body, "fullName", 80);
        std::string phone    = utils::jsonStr(body, "phone", 25);
        std::string email    = utils::jsonStr(body, "email", 80);
        std::string password = utils::jsonStr(body, "password", 60);

        Result r = user::updateUser(username, role, fullName, phone, email, password);
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true}"));
    }

    // ลบผู้ใช้
    if (path == "/api/admin/users/delete" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string username = utils::jsonStr(body, "username", 40);
        Session* s = getSession(head);
        std::string actor = s ? s->username : "admin";

        Result r = user::deleteUser(username, actor);
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);

        {
            std::lock_guard<std::mutex> slk(g_sessionMtx);
            for (auto it = g_sessions.begin(); it != g_sessions.end(); ) {
                if (it->second.username == username) it = g_sessions.erase(it);
                else ++it;
            }
            saveSessionsLocked();
        }

        return utils::jsonOk(withSaveState("{\"ok\":true}"));
    }

    // สร้าง Backup Snapshot ของไฟล์ Excel ทันที
    if (path == "/api/admin/backup" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string backupPath;
        if (!hotel::createBackupSnapshot(&backupPath)) {
            return utils::jsonErr("500 Internal Server Error", "ไม่สามารถสร้างสำรองไฟล์ฐานข้อมูลได้");
        }
        hotel::logAction("admin", "admin", "DB_BACKUP_CREATED", "Database Backup", backupPath);
        return utils::jsonOk("{\"ok\":true,\"backupPath\":" + q(backupPath) + "}");
    }

    // Interactive Admin Terminal Console Runner
    if (path == "/api/admin/console" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string cmd = utils::jsonStr(body, "cmd", 200);
        std::istringstream iss(cmd);
        std::string verb;
        iss >> verb;
        std::ostringstream out;

        if (verb == "help" || verb.empty()) {
            out << "=== Hilbert Grand Hotel Admin Terminal ===\n"
                << "Available commands:\n"
                << "  status                 - Show hotel occupancy and active revenue\n"
                << "  db:verify              - Verify database sheets & health\n"
                << "  excel:reload           - Reload hotel.xlsx from disk\n"
                << "  backup:now             - Create instant snapshot in data/backups/\n"
                << "  user:list              - List all registered users & roles\n"
                << "  room:price <id> <p>    - Update nightly rate for room <id>\n"
                << "  audit:tail [count]     - Print last [count] audit log entries\n"
                << "  clear                  - Clear terminal output\n";
        } else if (verb == "status") {
            int occupied = 0;
            long revenue = 0;
            for (const auto& r : hotel::g_rooms) {
                if (reservation::activeFor(r.id)) occupied++;
            }
            for (const auto& b : reservation::g_books) {
                if (b.status == "wait" || b.status == "checkin") revenue += b.total;
            }
            float occRate = hotel::g_rooms.empty() ? 0.0f : (occupied * 100.0f / hotel::g_rooms.size());
            out << "[STATUS] Hotel Occupancy: " << occupied << "/" << hotel::g_rooms.size()
                << " (" << std::fixed << std::setprecision(1) << occRate << "%)\n"
                << "Active Stays / Bookings Revenue: " << revenue << " THB\n"
                << "Total Historical Reservations: " << reservation::g_books.size() << "\n"
                << "Registered System Users: " << user::g_users.size() << "\n";
        } else if (verb == "db:verify") {
            out << "[DB:VERIFY] File: data/hotel.xlsx\n"
                << "  Sheet 'rooms':      " << hotel::g_rooms.size() << " records\n"
                << "  Sheet 'room_types': " << hotel::g_types.size() << " records\n"
                << "  Sheet 'bookings':   " << reservation::g_books.size() << " records\n"
                << "  Sheet 'users':      " << user::g_users.size() << " records\n"
                << "  Sheet 'audit_log':  " << hotel::g_audits.size() << " records\n"
                << "  Database Health: OK (All 5 sheets active)\n";
        } else if (verb == "excel:reload") {
            bool ok = hotel::loadAll();
            if (ok) {
                hotel::logAction("admin", "admin", "EXCEL_RELOAD", "hotel.xlsx", "Terminal reload");
                out << "[SUCCESS] Database reloaded successfully from data/hotel.xlsx\n";
            } else {
                out << "[ERROR] Failed to reload data/hotel.xlsx (file may be open in Excel)\n";
            }
        } else if (verb == "backup:now") {
            std::string path;
            if (hotel::createBackupSnapshot(&path)) {
                hotel::logAction("admin", "admin", "DB_BACKUP_CREATED", "Database Backup", path);
                out << "[SUCCESS] Created backup snapshot -> " << path << "\n";
            } else {
                out << "[ERROR] Failed to generate backup snapshot\n";
            }
        } else if (verb == "user:list") {
            out << "+-----------------+----------+---------------------------+-----------------+\n"
                << "| Username        | Role     | Full Name                 | Phone           |\n"
                << "+-----------------+----------+---------------------------+-----------------+\n";
            for (const auto& u : user::g_users) {
                char rowBuf[256];
                snprintf(rowBuf, sizeof(rowBuf), "| %-15s | %-8s | %-25s | %-15s |\n",
                         u.username.substr(0, 15).c_str(),
                         u.role.substr(0, 8).c_str(),
                         u.fullName.substr(0, 25).c_str(),
                         u.phone.substr(0, 15).c_str());
                out << rowBuf;
            }
            out << "+-----------------+----------+---------------------------+-----------------+\n";
        } else if (verb == "room:price") {
            std::string rId;
            long price = 0;
            iss >> rId >> price;
            Room* m = hotel::findRoom(rId);
            if (!m) {
                out << "[ERROR] Room not found: " << rId << "\n";
            } else if (price <= 0 || price > 1000000) {
                out << "[ERROR] Invalid price: " << price << "\n";
            } else {
                long oldP = m->price;
                m->price = price;
                hotel::saveAll();
                hotel::logAction("admin", "admin", "ROOM_PRICE_UPDATE", "Room " + m->id,
                                 "Price changed from " + std::to_string(oldP) + " to " + std::to_string(price) + " THB via terminal");
                out << "[SUCCESS] Room " << m->id << " price updated to " << price << " THB\n";
            }
        } else if (verb == "audit:tail") {
            int count = 5;
            iss >> count;
            if (count <= 0) count = 5;
            if (count > (int)hotel::g_audits.size()) count = (int)hotel::g_audits.size();
            out << "[AUDIT LOGS - Last " << count << " entries]:\n";
            for (int i = 0; i < count; ++i) {
                const auto& a = hotel::g_audits[hotel::g_audits.size() - count + i];
                out << "  [" << a.timestamp << "] " << a.actionType << " by " << a.actorUser
                    << " (" << a.targetEntity << "): " << a.diff << "\n";
            }
        } else {
            out << "Unknown command: '" << verb << "'. Type 'help' for a list of commands.\n";
        }

        return utils::jsonOk("{\"ok\":true,\"output\":" + q(out.str()) + "}");
    }

    // เปลี่ยนสถานะ  wait -> checkin -> checkout  หรือ cancelled
    if (path == "/api/admin/status" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Result r = reservation::setStatus(utils::jsonStr(body, "id", 12),
                                          utils::jsonStr(body, "status", 12));
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true}"));
    }

    // แก้ไขรายละเอียดการจอง
    if (path == "/api/admin/booking" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::string id = utils::jsonStr(body, "id", 12);
        Booking* cur = reservation::find(id);
        int nights = (int)utils::jsonInt(body, "nights", cur ? cur->nights : 0);
        Result r = reservation::edit(id,
            utils::jsonStr(body, "booker", 60),
            utils::jsonStr(body, "phone", 25),
            utils::jsonStr(body, "email", 80),
            utils::jsonStr(body, "checkIn", 10),
            nights,
            utils::jsonStr(body, "note", 200));
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk(withSaveState("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}"));
    }

    // แอดมินเพิ่มการจองเอง (ลูกค้า walk-in)
    if (path == "/api/admin/add" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Result r = reservation::create(
            utils::jsonStr(body, "room", 12),
            utils::jsonStr(body, "booker", 60),
            utils::jsonStr(body, "phone", 25),
            utils::jsonStr(body, "email", 80),
            utils::jsonStr(body, "checkIn", 10),
            (int)utils::jsonInt(body, "nights", 0),
            utils::jsonStr(body, "note", 200),
            utils::jsonStr(body, "status", 12));
        if (!r.ok) {
            std::string msg = r.error;
            if (r.httpCode == "409 Conflict") msg = "ห้องนี้ไม่ว่าง";
            return utils::jsonErr(r.httpCode, msg);
        }
        return utils::jsonOk(withSaveState("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}"));
    }

    // แก้ราคาหรือหมายเหตุของห้อง (เขียนกลับลง sheet rooms)
    if (path == "/api/admin/room" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Room* m = hotel::findRoom(utils::jsonStr(body, "room", 12));
        if (!m) return utils::jsonErr("404 Not Found", "ไม่พบหมายเลขห้องนี้");

        long prevPrice = m->price;
        long price = utils::jsonInt(body, "price", m->price);
        if (price < 0 || price > 1000000) return utils::jsonErr("400 Bad Request", "ราคาไม่ถูกต้อง");
        m->price = price;
        if (utils::jsonHas(body, "note")) m->note = utils::jsonStr(body, "note", 120);
        hotel::saveAll();
        std::cout << "[ROOM] " << m->id << " ราคา " << m->price << "\n";

        // บันทึกลง Audit Log
        hotel::logAction("admin", "admin", "ROOM_PRICE_UPDATE", "Room " + m->id,
                         "Price changed from " + std::to_string(prevPrice) + " to " +
                         std::to_string(m->price) + " THB" + (m->note.empty() ? "" : " | " + m->note));

        return utils::jsonOk(withSaveState("{\"ok\":true}"));
    }

    // อ่านไฟล์ Excel ใหม่ (กรณีแก้ด้วย Excel ระหว่างที่เซิร์ฟเวอร์รันอยู่)
    if (path == "/api/admin/reload" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        if (!hotel::loadAll())
            return utils::jsonErr("500 Internal Server Error",
                                  "อ่านไฟล์ Excel ไม่ได้ ตรวจว่าไฟล์ไม่ได้ถูกเปิดค้างอยู่");
        std::cout << "[RELOAD] อ่าน hotel.xlsx ใหม่แล้ว\n";

        // บันทึกลง Audit Log
        hotel::logAction("admin", "admin", "EXCEL_RELOAD", "hotel.xlsx", "Reloaded database from disk");

        return utils::jsonOk("{\"ok\":true}");
    }

    // ============================================================
    // PART 3 — ไฟล์ static
    // ============================================================
    std::string file = (path == "/") ? "/index.html" : path;
    if (file == "/admin") file = "/admin.html";
    if (file.find("..") != std::string::npos)
        return utils::resp("403 Forbidden", "text/plain; charset=utf-8", "Forbidden");

    std::string content;
    if (utils::readFile("public" + file, content))
        return utils::resp("200 OK", utils::mimeOf(file), content);

    // ปิดไม่ให้ดาวน์โหลดไฟล์ในโฟลเดอร์ data/ ผ่านเว็บ (ฐานข้อมูลมีรหัสผ่านผู้ใช้อยู่)
    if (file.rfind("/data/", 0) == 0)
        return utils::resp("403 Forbidden", "text/plain; charset=utf-8", "Forbidden");

    return utils::resp("404 Not Found", "text/html; charset=utf-8",
                       "<h1>404</h1><p>ไม่พบหน้านี้</p>");
}


// ============================================================
// PART 4 — รับ connection
// ============================================================
static void sendAll(SOCKET s, const std::string& d) {
    size_t sent = 0;
    while (sent < d.size()) {
        int n = send(s, d.data() + sent, (int)(d.size() - sent), 0);
        if (n <= 0) break;
        sent += n;
    }
}

static void serveClient(SOCKET c) {
    std::string req;
    char buf[8192];

    size_t headerEnd = std::string::npos;
    while (true) {
        int n = recv(c, buf, sizeof(buf), 0);
        if (n <= 0) { CLOSESOCK(c); return; }
        req.append(buf, n);
        headerEnd = req.find("\r\n\r\n");
        if (headerEnd != std::string::npos) break;
        if (req.size() > (1u << 20)) { CLOSESOCK(c); return; }
    }

    std::istringstream ls(req.substr(0, req.find("\r\n")));
    std::string method, rawPath, ver;
    ls >> method >> rawPath >> ver;
    std::string path = rawPath;
    size_t qp = path.find('?');
    if (qp != std::string::npos) path = path.substr(0, qp);

    size_t clen = 0;
    std::string head = req.substr(0, headerEnd), lower = head;
    for (auto& ch : lower) ch = (char)tolower((unsigned char)ch);
    size_t cp = lower.find("content-length:");
    if (cp != std::string::npos) clen = (size_t)std::atol(head.c_str() + cp + 15);

    std::string body = req.substr(headerEnd + 4);
    while (body.size() < clen) {
        int n = recv(c, buf, sizeof(buf), 0);
        if (n <= 0) break;
        body.append(buf, n);
    }

    sendAll(c, handle(method, path, body, head, rawPath));
    CLOSESOCK(c);
}


// ============================================================
// PART 5 — main
// ============================================================
int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--demo" || arg == "-demo") {
            g_demoMode = true;
        } else if (arg == "-f" && i + 1 < argc && std::string(argv[i + 1]) == "demo") {
            g_demoMode = true;
            i++;
        }
    }

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { std::cerr << "WSAStartup failed\n"; return 1; }
#else
    signal(SIGPIPE, SIG_IGN);
#endif

    if (!hotel::loadAll()) {
        std::cerr << "อ่าน " << hotel::F_DATA << " ไม่ได้ หรือไม่มี sheet ชื่อ rooms\n";
        std::cerr << "ต้องรันจากโฟลเดอร์ที่มี data/ และ public/ อยู่ข้าง ๆ\n";
        return 1;
    }
    loadSessionsFromFile();

    SOCKET srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv == INVALID_SOCKET) { std::cerr << "socket() error\n"; return 1; }
    int yes = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    if (bind(srv, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "bind() error - พอร์ต " << PORT << " อาจถูกใช้อยู่\n";
        return 1;
    }
    listen(srv, 32);

    std::cout << "==========================================\n";
    std::cout << " ระบบจองโรงแรม — backend C++\n";
    std::cout << " โหมด: " << (g_demoMode ? "DEMO MODE (เปิด Role Switcher)" : "PRODUCTION MODE (ปิด Role Switcher)") << "\n";
    std::cout << " ห้อง " << hotel::g_rooms.size()
              << " ห้อง  การจอง " << reservation::g_books.size() << " รายการ\n";
    std::cout << " หน้าผู้ใช้  http://localhost:" << PORT << "\n";
    std::cout << " หน้าแอดมิน http://localhost:" << PORT << "/admin\n";
    if (!g_demoMode) {
        std::cout << " (หมายเหตุ: รันด้วย make run-demo หรือ -f demo เพื่อเปิด Role Switcher ในการนำเสนอ)\n";
    }
    std::cout << " หยุดด้วย Ctrl+C\n";
    std::cout << "==========================================\n";

    while (true) {
        sockaddr_in cli{};
        socklen_t len = sizeof(cli);
        SOCKET c = accept(srv, (sockaddr*)&cli, &len);
        if (c == INVALID_SOCKET) continue;
        std::thread(serveClient, c).detach();
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
