// ============================================================
//  user.cpp — การจัดการผู้ใช้และการเข้าสู่ระบบ
// ============================================================
#include "../include/user.h"
#include "../include/utils.h"
#include "../include/hotel.h"

#include <sstream>
#include <iostream>
#include <algorithm>

namespace user {

std::vector<User> g_users;

void seedDefaults() {
    // เติมเฉพาะบัญชีที่ยังไม่มี ถ้าไฟล์ Excel มีผู้ใช้อยู่แล้วแต่ลบ admin ทิ้ง
    // ระบบจะเติม admin กลับให้เอง (เดิมเติมเฉพาะตอนไม่มีผู้ใช้เลย จึงล็อกอินไม่ได้)
    const User defaults[] = {
        {"admin", "admin123", "admin", "System Administrator", "081-000-0001", "admin@hotel.com"},
        {"staff", "staff123", "staff", "Front Desk Staff",     "081-000-0002", "staff@hotel.com"},
        {"guest", "guest123", "guest", "สมชาย ใจดี",            "081-234-5678", "somchai@gmail.com"},
    };
    for (const User& d : defaults)
        if (!find(d.username)) g_users.push_back(d);
}

User* find(const std::string& username) {
    for (auto& u : g_users) {
        if (u.username == username) return &u;
    }
    return nullptr;
}

bool exists(const std::string& username) {
    return find(username) != nullptr;
}

User* authenticate(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) return nullptr;
    User* u = find(username);
    if (u && u->password == password) {
        return u;
    }
    return nullptr;
}

Result registerGuest(const std::string& username,
                     const std::string& password,
                     const std::string& fullName,
                     const std::string& phone,
                     const std::string& email) {
    Result r;
    if (username.empty() || username.size() < 3) {
        r.ok = false;
        r.httpCode = "400 Bad Request";
        r.error = "ชื่อผู้ใช้ต้องมีความยาวอย่างน้อย 3 ตัวอักษร";
        return r;
    }
    if (password.empty() || password.size() < 4) {
        r.ok = false;
        r.httpCode = "400 Bad Request";
        r.error = "รหัสผ่านต้องมีความยาวอย่างน้อย 4 ตัวอักษร";
        return r;
    }
    if (fullName.empty()) {
        r.ok = false;
        r.httpCode = "400 Bad Request";
        r.error = "กรุณากรอกชื่อ-นามสกุล";
        return r;
    }
    if (exists(username)) {
        r.ok = false;
        r.httpCode = "409 Conflict";
        r.error = "ชื่อผู้ใช้นี้ถูกใช้งานแล้ว กรุณาเลือกชื่ออื่น";
        return r;
    }

    User u;
    u.username = username;
    u.password = password;
    u.role = "guest";
    u.fullName = fullName;
    u.phone = phone;
    u.email = email;

    g_users.push_back(u);
    hotel::saveAll();

    std::cout << "[USER] ลงทะเบียนผู้ใช้ใหม่: " << u.username << " (" << u.fullName << ")\n";

    r.ok = true;
    return r;
}

std::string toJson(const User& u) {
    using utils::q;
    std::ostringstream o;
    o << "{"
      << q("username") << ":" << q(u.username) << ","
      << q("role")     << ":" << q(u.role) << ","
      << q("fullName") << ":" << q(u.fullName) << ","
      << q("phone")    << ":" << q(u.phone) << ","
      << q("email")    << ":" << q(u.email)
      << "}";
    return o.str();
}

std::string listJson() {
    std::ostringstream o;
    o << "[";
    for (size_t i = 0; i < g_users.size(); ++i) {
        if (i) o << ",";
        o << toJson(g_users[i]);
    }
    o << "]";
    return o.str();
}

void loadFromRows(const std::vector<std::vector<std::string>>& rows) {
    using utils::at;
    g_users.clear();
    for (auto& r : rows) {
        if (at(r, 0).empty()) continue;
        User u;
        u.username = at(r, 0);
        u.password = at(r, 1);
        u.role     = at(r, 2);
        u.fullName = at(r, 3);
        u.phone    = at(r, 4);
        u.email    = at(r, 5);
        if (u.role.empty()) u.role = "guest";
        g_users.push_back(u);
    }
    seedDefaults();
}

std::vector<std::vector<std::string>> saveToRows() {
    seedDefaults();
    std::vector<std::vector<std::string>> rows;
    for (auto& u : g_users) {
        rows.push_back({u.username, u.password, u.role, u.fullName, u.phone, u.email});
    }
    return rows;
}

} // namespace user
