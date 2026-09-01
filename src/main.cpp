// ============================================================
//  main.cpp — HTTP server, router และจุดเริ่มโปรแกรม
//     PART 1  ROUTER: API ฝั่งผู้ใช้
//     PART 2  ROUTER: API ฝั่งแอดมิน
//     PART 3  ROUTER: ไฟล์ static
//     PART 4  รับ connection
//     PART 5  main
//
//  build : ดู build.bat หรือ build.sh
// ============================================================

#include "../include/hotel.h"
#include "../include/reservation.h"
#include "../include/utils.h"

#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <cstring>
#include <cctype>

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

using utils::q;

static std::string handle(const std::string& method,
                          const std::string& path,
                          const std::string& body) {

    if (method == "OPTIONS") return utils::resp("204 No Content", "text/plain", "");

    // ============================================================
    // PART 1 — API ฝั่งผู้ใช้
    // ============================================================

    // ผังห้องทั้งหมด + สถานะ (หน้าเว็บเรียกซ้ำทุก 2 วินาที)
    if (path == "/api/rooms" && method == "GET") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        std::ostringstream o;
        o << "{\"rooms\":[";
        for (size_t i = 0; i < hotel::g_rooms.size(); ++i) {
            if (i) o << ",";
            o << hotel::roomJsonPublic(hotel::g_rooms[i]);
        }
        o << "],\"today\":" << q(utils::todayStr()) << "}";
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
        return utils::jsonOk("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}");
    }

    // ============================================================
    // PART 2 — API ฝั่งแอดมิน
    // ============================================================

    // ตารางรวม: ห้องทุกห้อง + การจองที่ยังกินห้องอยู่ + ประวัติทั้งหมด
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
              << "," << q("booking")  << ":" << (b ? reservation::toJson(*b) : "null")
              << "}";
        }
        o << "],\"bookings\":[";
        for (size_t i = 0; i < reservation::g_books.size(); ++i) {
            if (i) o << ",";
            o << reservation::toJson(reservation::g_books[i]);
        }
        o << "],\"today\":" << q(utils::todayStr()) << "}";
        return utils::jsonOk(o.str());
    }

    // เปลี่ยนสถานะ  wait -> checkin -> checkout  หรือ cancelled
    if (path == "/api/admin/status" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Result r = reservation::setStatus(utils::jsonStr(body, "id", 12),
                                          utils::jsonStr(body, "status", 12));
        if (!r.ok) return utils::jsonErr(r.httpCode, r.error);
        return utils::jsonOk("{\"ok\":true}");
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
        return utils::jsonOk("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}");
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
        return utils::jsonOk("{\"ok\":true,\"booking\":" + reservation::toJson(r.booking) + "}");
    }

    // แก้ราคาหรือหมายเหตุของห้อง (เขียนกลับลง sheet rooms)
    if (path == "/api/admin/room" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Room* m = hotel::findRoom(utils::jsonStr(body, "room", 12));
        if (!m) return utils::jsonErr("404 Not Found", "ไม่พบหมายเลขห้องนี้");

        long price = utils::jsonInt(body, "price", m->price);
        if (price < 0 || price > 1000000) return utils::jsonErr("400 Bad Request", "ราคาไม่ถูกต้อง");
        m->price = price;
        m->note  = utils::jsonStr(body, "note", 120);
        hotel::saveAll();
        std::cout << "[ROOM] " << m->id << " ราคา " << m->price << "\n";
        return utils::jsonOk("{\"ok\":true}");
    }

    // อ่านไฟล์ Excel ใหม่ (กรณีแก้ด้วย Excel ระหว่างที่เซิร์ฟเวอร์รันอยู่)
    if (path == "/api/admin/reload" && method == "POST") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        if (!hotel::loadAll())
            return utils::jsonErr("500 Internal Server Error",
                                  "อ่านไฟล์ Excel ไม่ได้ ตรวจว่าไฟล์ไม่ได้ถูกเปิดค้างอยู่");
        std::cout << "[RELOAD] อ่าน hotel.xlsx ใหม่แล้ว\n";
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

    // เปิดให้ดาวน์โหลดไฟล์ Excel ดิบจากหน้าแอดมิน
    if (file.rfind("/data/", 0) == 0 && utils::readFile(file.substr(1), content))
        return utils::resp("200 OK", utils::mimeOf(file), content);

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
    std::string method, path, ver;
    ls >> method >> path >> ver;
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

    sendAll(c, handle(method, path, body));
    CLOSESOCK(c);
}


// ============================================================
// PART 5 — main
// ============================================================
int main() {
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
    std::cout << " ห้อง " << hotel::g_rooms.size()
              << " ห้อง  การจอง " << reservation::g_books.size() << " รายการ\n";
    std::cout << " หน้าผู้ใช้  http://localhost:" << PORT << "\n";
    std::cout << " หน้าแอดมิน http://localhost:" << PORT << "/admin\n";
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
