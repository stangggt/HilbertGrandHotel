#include "../include/tui.h"
#include "../include/console_utils.h"
#include "../include/utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace ConsoleUtils;

TuiApp::TuiApp() : m_currentUser(nullptr), m_running(true) {
    hotel::loadAll();
}

void TuiApp::run() {
    while (m_running) {
        if (!m_currentUser) {
            handleAuthFlow();
        } else {
            if (m_currentUser->isAdmin() || m_currentUser->isStaff()) {
                showStaffAdminMenu();
            } else {
                showGuestMenu();
            }
        }
    }

    clearScreen();
    std::cout << Color::BOLD_GREEN << "\n  ขอบคุณที่ใช้บริการระบบจัดการโรงแรม Hilbert Grand Hotel! สวัสดีครับ/ค่ะ\n\n" << Color::RESET;
}

void TuiApp::handleAuthFlow() {
    clearScreen();
    printHeader("HILBERT GRAND HOTEL", "Console & Excel Database System");

    std::cout << "\n"
              << Color::BOLD_WHITE << "  ยินดีต้อนรับสู่ระบบจัดการและจองห้องพัก Hilbert Grand Hotel\n" << Color::RESET
              << Color::DIM << "  ฐานข้อมูลไฟล์ Excel (data/hotel.xlsx) | C++ Core Engine\n\n" << Color::RESET;

    std::vector<std::string> options = {
        "1. เข้าสู่ระบบ (Sign In) — สำหรับสมาชิก, พนักงาน, ผู้ดูแลระบบ",
        "2. สมัครสมาชิกใหม่ (Sign Up) — สำหรับลูกค้าทั่วไป",
        "3. ตรวจสอบห้องว่าง (Browse Available Rooms)",
        "4. ผังห้องพักทั้งหมด (Floor Plan Matrix)",
        "5. ออกจากโปรแกรม (Exit)"
    };

    printBox("เมนูเริ่มต้น (Authentication)", options, 68);

    int choice = readInt("\nเลือกตัวเลือก [1-5]: ", 1, 5);

    switch (choice) {
        case 1: showLoginScreen(); break;
        case 2: showRegisterScreen(); break;
        case 3:
            clearScreen();
            displayRoomsTable(hotel::g_rooms, "รายการห้องพักทั้งหมด");
            pause();
            break;
        case 4:
            clearScreen();
            displayFloorMatrix();
            pause();
            break;
        case 5: m_running = false; break;
    }
}

void TuiApp::showLoginScreen() {
    clearScreen();
    printHeader("เข้าสู่ระบบ (USER LOGIN)", "Authentication");

    std::cout << Color::DIM << "\n  (บัญชีตัวอย่าง: 'admin'/'admin123', 'staff'/'staff123', 'guest'/'guest123')\n\n" << Color::RESET;

    std::string username = readLine("  ชื่อผู้ใช้ (Username): ");
    if (username.empty()) return;
    std::string password = readLine("  รหัสผ่าน (Password): ");

    User* u = user::authenticate(username, password);
    if (u) {
        m_currentUser = u;
        std::cout << Color::BOLD_GREEN << "\n  [✓] เข้าสู่ระบบสำเร็จ! ยินดีต้อนรับคุณ "
                  << u->fullName << " (สิทธิ์: " << u->role << ")\n" << Color::RESET;
        pause();
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง\n" << Color::RESET;
        pause();
    }
}

void TuiApp::showRegisterScreen() {
    clearScreen();
    printHeader("สมัครสมาชิกใหม่ (NEW GUEST REGISTRATION)", "Create Account");

    std::string username = readLine("  กำหนดชื่อผู้ใช้ (Username): ");
    if (username.empty()) return;

    if (user::exists(username)) {
        std::cout << Color::BOLD_RED << "\n  [✗] ชื่อผู้ใช้นี้ถูกใช้งานแล้ว กรุณาเลือกชื่ออื่น\n" << Color::RESET;
        pause();
        return;
    }

    std::string password = readLine("  กำหนดรหัสผ่าน (Password): ");
    std::string fullName = readLine("  ชื่อ-นามสกุล (Full Name): ");
    std::string phone    = readLine("  เบอร์โทรศัพท์ (Phone): ");
    std::string email    = readLine("  อีเมล (Email): ");

    Result r = user::registerGuest(username, password, fullName, phone, email);
    if (r.ok) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] สมัครสมาชิกสำเร็จ! ข้อมูลถูกบันทึกลง hotel.xlsx แล้ว\n" << Color::RESET;
        m_currentUser = user::find(username);
        pause();
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] " << r.error << "\n" << Color::RESET;
        pause();
    }
}

void TuiApp::showGuestMenu() {
    clearScreen();
    std::string sub = "ยินดีต้อนรับคุณ " + m_currentUser->fullName + " (Guest)";
    printHeader("HILBERT GRAND HOTEL — GUEST PORTAL", sub);

    std::vector<std::string> options = {
        "1. ดูผังห้องพักและสถานะ (Floor Plan Matrix)",
        "2. ค้นหาและดูห้องพักทั้งหมด (Browse & Filter Rooms)",
        "3. จองห้องพัก (Book a Room)",
        "4. ประวัติและรายการจองของฉัน (My Bookings)",
        "5. ออกจากระบบ (Sign Out)"
    };

    printBox("เมนูลูกค้า (Guest Services)", options, 65);

    int choice = readInt("\nเลือกตัวเลือก [1-5]: ", 1, 5);

    switch (choice) {
        case 1:
            clearScreen();
            displayFloorMatrix();
            pause();
            break;
        case 2: guestBrowseRooms(); break;
        case 3: guestBookRoom(); break;
        case 4: guestViewMyBookings(); break;
        case 5:
            m_currentUser = nullptr;
            std::cout << Color::GREEN << "\n  ออกจากระบบเรียบร้อยแล้ว\n" << Color::RESET;
            pause();
            break;
    }
}

void TuiApp::showStaffAdminMenu() {
    clearScreen();
    std::string roleStr = m_currentUser->isAdmin() ? "Administrator" : "Staff Member";
    std::string sub = "ผู้ดูแลระบบ: " + m_currentUser->fullName + " (" + roleStr + ")";
    printHeader("HILBERT GRAND HOTEL — MANAGEMENT DASHBOARD", sub);

    std::vector<std::string> options = {
        "1. ดูสรุปภาพรวมโรงแรม (Dashboard & Statistics)",
        "2. ตารางผังห้องพักแบบ Real-time (Floor Matrix)",
        "3. จัดการห้องพักและดูรายการจองทั้งหมด (Rooms & Bookings Table)",
        "4. เพิ่มการจองลูกค้า Walk-in (New Walk-in Booking)",
        "5. เปลี่ยนสถานะการจอง (Check-in / Check-out / Cancel)",
        "6. แก้ไขราคาหรือหมายเหตุห้องพัก (Update Room Price / Note)",
        "7. รายชื่อผู้ใช้ทั้งหมดในระบบ (View All Users)",
        "8. โหลดไฟล์ hotel.xlsx ใหม่ (Reload Excel DB)",
        "9. ออกจากระบบ (Sign Out)"
    };

    printBox("เมนูการจัดการโรงแรม (Operations)", options, 70);

    int choice = readInt("\nเลือกตัวเลือก [1-9]: ", 1, 9);

    switch (choice) {
        case 1: adminShowDashboard(); break;
        case 2:
            clearScreen();
            displayFloorMatrix();
            pause();
            break;
        case 3: adminManageRooms(); break;
        case 4: adminWalkinBooking(); break;
        case 5: adminChangeStatus(); break;
        case 6: adminEditRoom(); break;
        case 7: adminViewUsers(); break;
        case 8: adminReloadData(); break;
        case 9:
            m_currentUser = nullptr;
            std::cout << Color::GREEN << "\n  ออกจากระบบเรียบร้อยแล้ว\n" << Color::RESET;
            pause();
            break;
    }
}

void TuiApp::displayFloorMatrix() {
    printHeader("ผังห้องพักตามชั้น (FLOOR PLAN MATRIX)");

    std::cout << "\n  " << Color::BG_GREEN << Color::BOLD_WHITE << " [ว่าง (Available)] " << Color::RESET
              << "   " << Color::RED << "[จองแล้ว / ไม่ว่าง (Booked)]" << Color::RESET
              << "   " << Color::BOLD_YELLOW << "* VIP Room" << Color::RESET << "\n\n";

    for (int fl = 3; fl >= 1; --fl) {
        std::cout << Color::BOLD_WHITE << "  ชั้น " << fl << ": " << Color::RESET;
        for (const auto& r : hotel::g_rooms) {
            if (r.floor == std::to_string(fl)) {
                Booking* b = reservation::activeFor(r.id);
                bool isBooked = (b != nullptr);

                std::string label = " ห้อง " + r.id + " ";
                if (r.tier == "vip") label = "*" + label;

                if (isBooked) {
                    std::cout << Color::RED << "[" << label << "]" << Color::RESET << " ";
                } else {
                    std::cout << Color::GREEN << "[" << label << "]" << Color::RESET << " ";
                }
            }
        }
        std::cout << "\n\n";
    }
}

void TuiApp::displayRoomsTable(const std::vector<Room>& rooms, const std::string& tableTitle) {
    std::cout << Color::BOLD_CYAN << "\n  ✦ " << tableTitle << " (จำนวน " << rooms.size() << " ห้อง)\n" << Color::RESET;

    std::vector<std::string> headers = {"ห้อง", "ชั้น", "ประเภทเตียง", "ระดับห้อง", "ราคา/คืน (บาท)", "สถานะ", "ผู้เข้าพัก/จอง"};
    std::vector<int> widths = {8, 6, 14, 12, 16, 14, 20};

    std::vector<std::vector<std::string>> rows;
    for (const auto& r : rooms) {
        Booking* b = reservation::activeFor(r.id);
        std::string statusStr = b ? (b->status == "checkin" ? "เช็คอินแล้ว" : "รอเช็คอิน") : "ว่าง";
        std::string guest = b ? (b->booker + " (" + b->id + ")") : "-";

        rows.push_back({
            r.id,
            "ชั้น " + r.floor,
            r.bed == "twin" ? "เตียงเดี่ยว 2" : "เตียงใหญ่ 1",
            r.tier == "vip" ? "★ VIP" : "มาตรฐาน",
            std::to_string(r.price),
            statusStr,
            guest
        });
    }

    printTable(headers, widths, rows);
}

void TuiApp::guestBrowseRooms() {
    clearScreen();
    displayRoomsTable(hotel::g_rooms, "รายการห้องพักทั้งหมดของโรงแรม");

    std::cout << "\n"
              << "  [1] กรองเฉพาะห้องว่าง  [2] กรองเฉพาะห้อง VIP  [3] กลับเมนูหลัก\n";
    int f = readInt("เลือกตัวเลือก [1-3]: ", 1, 3);

    if (f == 1) {
        std::vector<Room> freeRooms;
        for (const auto& r : hotel::g_rooms) {
            if (!reservation::activeFor(r.id)) freeRooms.push_back(r);
        }
        clearScreen();
        displayRoomsTable(freeRooms, "ห้องว่างพร้อมให้บริการ");
        pause();
    } else if (f == 2) {
        std::vector<Room> vipRooms;
        for (const auto& r : hotel::g_rooms) {
            if (r.tier == "vip") vipRooms.push_back(r);
        }
        clearScreen();
        displayRoomsTable(vipRooms, "ห้อง VIP ทั้งหมด");
        pause();
    }
}

void TuiApp::guestBookRoom() {
    clearScreen();
    printHeader("จองห้องพัก (BOOK A ROOM)", "Hilbert Grand Hotel");

    std::vector<Room> freeRooms;
    for (const auto& r : hotel::g_rooms) {
        if (!reservation::activeFor(r.id)) freeRooms.push_back(r);
    }
    displayRoomsTable(freeRooms, "ห้องว่างที่สามารถจองได้");

    std::cout << "\n";
    std::string roomId = readLine("  ระบุหมายเลขห้องที่ต้องการจอง (หรือเว้นว่างเพื่อยกเลิก): ");
    if (roomId.empty()) return;

    Room* m = hotel::findRoom(roomId);
    if (!m) {
        std::cout << Color::BOLD_RED << "\n  [!] ไม่พบหมายเลขห้องนี้\n" << Color::RESET;
        pause();
        return;
    }

    if (reservation::activeFor(roomId)) {
        std::cout << Color::BOLD_RED << "\n  [!] ขออภัย ห้องนี้มีผู้จองแล้ว\n" << Color::RESET;
        pause();
        return;
    }

    std::string today = utils::todayStr();
    std::string checkIn = readLine("  วันที่เช็คอิน [YYYY-MM-DD] (กด Enter เพื่อใช้วันนี้: " + today + "): ");
    if (checkIn.empty()) checkIn = today;

    int nights = readInt("  จำนวนคืนที่เข้าพัก (1 - 30): ", 1, 30);
    std::string note = readLine("  หมายเหตุเพิ่มเติม (ถ้ามี): ");

    long total = (long)nights * m->price;
    std::cout << Color::BOLD_YELLOW << "\n  สรุปการจอง: ห้อง " << m->id << " (" << m->tier << ") | "
              << nights << " คืน | ยอดรวม " << total << " บาท\n" << Color::RESET;

    std::string confirm = readLine("  ยืนยันการจอง? (y/n): ");
    if (confirm == "y" || confirm == "Y") {
        std::lock_guard<std::mutex> lk(hotel::g_mtx);
        Result r = reservation::create(roomId, m_currentUser->fullName, m_currentUser->phone,
                                       m_currentUser->email, checkIn, nights, note, "wait");
        if (r.ok) {
            std::cout << Color::BOLD_GREEN << "\n  [✓] การจองสำเร็จ! รหัสการจอง: " << r.booking.id << "\n" << Color::RESET;
        } else {
            std::cout << Color::BOLD_RED << "\n  [✗] ไม่สามารถจองได้: " << r.error << "\n" << Color::RESET;
        }
    } else {
        std::cout << Color::YELLOW << "\n  ยกเลิกการจอง\n" << Color::RESET;
    }
    pause();
}

void TuiApp::guestViewMyBookings() {
    clearScreen();
    printHeader("รายการจองของฉัน (MY BOOKINGS)", m_currentUser->fullName);

    std::vector<Booking> myBooks;
    for (const auto& b : reservation::g_books) {
        if (b.booker == m_currentUser->fullName || b.phone == m_currentUser->phone || b.email == m_currentUser->email) {
            myBooks.push_back(b);
        }
    }

    if (myBooks.empty()) {
        std::cout << Color::DIM << "\n  ไม่พบประวัติการจองในระบบสำหรับคุณ " << m_currentUser->fullName << "\n" << Color::RESET;
    } else {
        std::vector<std::string> headers = {"รหัสจอง", "ห้อง", "เช็คอิน", "เช็คเอาท์", "คืน", "ยอดรวม (บาท)", "สถานะ"};
        std::vector<int> widths = {10, 8, 12, 12, 6, 16, 14};
        std::vector<std::vector<std::string>> rows;

        for (const auto& b : myBooks) {
            std::string st = b.status;
            if (st == "wait") st = "รอเช็คอิน";
            else if (st == "checkin") st = "เช็คอินแล้ว";
            else if (st == "checkout") st = "เช็คเอาท์แล้ว";
            else if (st == "cancelled") st = "ยกเลิก";

            rows.push_back({
                b.id, b.roomId, b.checkIn, b.checkOut,
                std::to_string(b.nights), std::to_string(b.total), st
            });
        }
        printTable(headers, widths, rows);
    }
    pause();
}

void TuiApp::adminShowDashboard() {
    clearScreen();
    printHeader("แดชบอร์ดสรุปภาพรวม (HOTEL DASHBOARD)");

    int totalRooms = (int)hotel::g_rooms.size();
    int occupied = 0;
    int wait = 0;
    long activeRev = 0;

    for (const auto& r : hotel::g_rooms) {
        Booking* b = reservation::activeFor(r.id);
        if (b) {
            if (b->status == "checkin") ++occupied;
            else if (b->status == "wait") ++wait;
            activeRev += b->total;
        }
    }
    int freeRooms = totalRooms - (occupied + wait);
    double occRate = totalRooms > 0 ? (double)(occupied + wait) / totalRooms * 100.0 : 0.0;

    std::vector<std::string> stats = {
        "จำนวนห้องพักทั้งหมด:     " + std::to_string(totalRooms) + " ห้อง",
        "ห้องว่างพร้อมให้บริการ:  " + std::to_string(freeRooms) + " ห้อง",
        "รอเช็คอิน (Reserved):    " + std::to_string(wait) + " ห้อง",
        "เช็คอินเข้าพักแล้ว:      " + std::to_string(occupied) + " ห้อง",
        "อัตราการเข้าพักรวม:      " + std::to_string((int)occRate) + "%",
        "ยอดเงินจากการจองปัจจุบัน: " + std::to_string(activeRev) + " บาท",
        "ประวัติการจองทั้งหมด:    " + std::to_string(reservation::g_books.size()) + " รายการ"
    };

    printBox("สรุปสถานะปัจจุบัน (Real-time Overview)", stats, 55);
    pause();
}

void TuiApp::adminManageRooms() {
    clearScreen();
    displayRoomsTable(hotel::g_rooms, "จัดการห้องพักและรายการจอง");

    std::cout << "\n  ประวัติการจองล่าสุด:\n";
    std::vector<std::string> headers = {"รหัส", "ห้อง", "ผู้จอง", "เบอร์โทร", "เช็คอิน - ออก", "ยอด", "สถานะ"};
    std::vector<int> widths = {8, 6, 18, 14, 24, 12, 14};
    std::vector<std::vector<std::string>> rows;

    size_t start = reservation::g_books.size() > 10 ? reservation::g_books.size() - 10 : 0;
    for (size_t i = reservation::g_books.size(); i > start; --i) {
        const auto& b = reservation::g_books[i - 1];
        rows.push_back({
            b.id, b.roomId, b.booker, b.phone,
            b.checkIn + " -> " + b.checkOut,
            std::to_string(b.total), b.status
        });
    }
    printTable(headers, widths, rows);
    pause();
}

void TuiApp::adminWalkinBooking() {
    clearScreen();
    printHeader("เพิ่มการจองลูกค้า WALK-IN", "Front Desk Operation");

    std::string roomId = readLine("  หมายเลขห้อง: ");
    Room* m = hotel::findRoom(roomId);
    if (!m) {
        std::cout << Color::BOLD_RED << "\n  [!] ไม่พบห้องนี้\n" << Color::RESET;
        pause();
        return;
    }
    if (reservation::activeFor(roomId)) {
        std::cout << Color::BOLD_RED << "\n  [!] ห้องนี้ไม่ว่าง\n" << Color::RESET;
        pause();
        return;
    }

    std::string booker = readLine("  ชื่อลูกค้า: ");
    std::string phone  = readLine("  เบอร์โทร: ");
    std::string email  = readLine("  อีเมล: ");
    std::string checkIn = readLine("  วันที่เช็คอิน [YYYY-MM-DD] (Enter = วันนี้): ");
    if (checkIn.empty()) checkIn = utils::todayStr();
    int nights = readInt("  จำนวนคืน: ", 1, 30);
    std::string note = readLine("  หมายเหตุ: ");

    std::cout << "\n  สถานะเริ่มต้น: [1] เช็คอินทันที (checkin)  [2] จองล่วงหน้า (wait)\n";
    int stChoice = readInt("เลือก [1-2]: ", 1, 2);
    std::string st = (stChoice == 1) ? "checkin" : "wait";

    std::lock_guard<std::mutex> lk(hotel::g_mtx);
    Result r = reservation::create(roomId, booker, phone, email, checkIn, nights, note, st);
    if (r.ok) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] บันทึกการจองสำเร็จ! รหัส: " << r.booking.id << "\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] " << r.error << "\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminChangeStatus() {
    clearScreen();
    printHeader("เปลี่ยนสถานะการจอง", "Check-in / Check-out / Cancel");

    std::string bookId = readLine("  ระบุรหัสการจอง (เช่น B0001): ");
    Booking* b = reservation::find(bookId);
    if (!b) {
        std::cout << Color::BOLD_RED << "\n  [!] ไม่พบรหัสการจองนี้\n" << Color::RESET;
        pause();
        return;
    }

    std::cout << "\n  ข้อมูลการจอง: " << b->id << " | ห้อง " << b->roomId << " | " << b->booker
              << " | สถานะปัจจุบัน: " << Color::BOLD_YELLOW << b->status << Color::RESET << "\n\n";

    std::cout << "  เลือกสถานะใหม่:\n"
              << "  [1] เช็คอินแล้ว (checkin)\n"
              << "  [2] เช็คเอาท์เรียบร้อย (checkout)\n"
              << "  [3] รอเช็คอิน (wait)\n"
              << "  [4] ยกเลิกการจอง (cancelled)\n"
              << "  [5] ยกเลิกไม่เปลี่ยน\n";

    int ch = readInt("เลือก [1-5]: ", 1, 5);
    std::string newStatus;
    if (ch == 1) newStatus = "checkin";
    else if (ch == 2) newStatus = "checkout";
    else if (ch == 3) newStatus = "wait";
    else if (ch == 4) newStatus = "cancelled";
    else return;

    std::lock_guard<std::mutex> lk(hotel::g_mtx);
    Result r = reservation::setStatus(bookId, newStatus);
    if (r.ok) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] เปลี่ยนสถานะเป็น " << newStatus << " เรียบร้อยแล้ว\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] " << r.error << "\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminEditRoom() {
    clearScreen();
    printHeader("แก้ไขราคาและหมายเหตุห้องพัก", "Room Management");

    std::string roomId = readLine("  หมายเลขห้อง: ");
    Room* m = hotel::findRoom(roomId);
    if (!m) {
        std::cout << Color::BOLD_RED << "\n  [!] ไม่พบห้องนี้\n" << Color::RESET;
        pause();
        return;
    }

    std::cout << "\n  ห้อง " << m->id << " | ราคาปัจจุบัน: " << m->price << " บาท | หมายเหตุ: " << m->note << "\n\n";

    std::string priceStr = readLine("  กำหนดราคาใหม่ (Enter เพื่อคงราคาเดิม): ");
    std::string note = readLine("  กำหนดหมายเหตุใหม่: ");

    std::lock_guard<std::mutex> lk(hotel::g_mtx);
    if (!priceStr.empty()) {
        try {
            m->price = std::stol(priceStr);
        } catch (...) {}
    }
    if (!note.empty()) {
        m->note = note;
    }
    hotel::saveAll();
    std::cout << Color::BOLD_GREEN << "\n  [✓] บันทึกข้อมูลห้องพักลง hotel.xlsx เรียบร้อยแล้ว\n" << Color::RESET;
    pause();
}

void TuiApp::adminReloadData() {
    std::lock_guard<std::mutex> lk(hotel::g_mtx);
    if (hotel::loadAll()) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] โหลดข้อมูลจาก data/hotel.xlsx สำเร็จแล้ว\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] ไม่สามารถอ่านไฟล์ Excel ได้ (ตรวจสอบว่าไม่ได้เปิดค้างไว้)\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminViewUsers() {
    clearScreen();
    printHeader("รายชื่อผู้ใช้ทั้งหมดในระบบ (USER ACCOUNTS)");

    std::vector<std::string> headers = {"ชื่อผู้ใช้ (Username)", "สิทธิ์ (Role)", "ชื่อ-นามสกุล", "เบอร์โทร", "อีเมล"};
    std::vector<int> widths = {22, 12, 24, 16, 26};
    std::vector<std::vector<std::string>> rows;

    for (const auto& u : user::g_users) {
        rows.push_back({u.username, u.role, u.fullName, u.phone, u.email});
    }

    printTable(headers, widths, rows);
    pause();
}
