// ============================================================
//  user.h — ผู้ใช้และระบบยืนยันตัวตน (Authentication & RBAC)
//     PART 1  โครงสร้างข้อมูลผู้ใช้
//     PART 2  ตัวแปรกลางและฟังก์ชันตรวจสอบสิทธิ์
// ============================================================
#pragma once

#include <string>
#include <vector>
#include "reservation.h"

// ---------- PART 1 — โครงสร้างข้อมูลผู้ใช้ ----------

enum class UserRole {
    ADMIN,
    STAFF,
    GUEST
};

struct User {
    std::string username;
    std::string password;
    std::string role;      // "admin", "staff", "guest"
    std::string fullName;
    std::string phone;
    std::string email;

    bool isAdmin() const { return role == "admin"; }
    bool isStaff() const { return role == "staff" || role == "admin"; }
    bool isGuest() const { return role == "guest"; }
};

namespace user {

// ---------- PART 2 — ตัวแปรกลางและฟังก์ชัน ----------

extern std::vector<User> g_users;

void seedDefaults();
User* find(const std::string& username);
bool exists(const std::string& username);
User* authenticate(const std::string& username, const std::string& password);

Result registerGuest(const std::string& username,
                     const std::string& password,
                     const std::string& fullName,
                     const std::string& phone,
                     const std::string& email);

std::string toJson(const User& u);
std::string listJson();

void loadFromRows(const std::vector<std::vector<std::string>>& rows);
std::vector<std::vector<std::string>> saveToRows();

} // namespace user
