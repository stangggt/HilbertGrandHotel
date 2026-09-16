// ============================================================
//  user.cpp — การจัดการผู้ใช้และการเข้าสู่ระบบ
// ============================================================
#include "../include/user.h"
#include "../include/utils.h"
#include "../include/hotel.h"
#include "../include/sha256.h"

#include <sstream>
#include <iostream>
#include <algorithm>

namespace user {

std::vector<User> g_users;

void seedDefaults() {
    // เติมเฉพาะบัญชีที่ยังไม่มี ถ้าไฟล์ Excel มีผู้ใช้อยู่แล้วแต่ลบ admin ทิ้ง
    // ระบบจะเติม admin กลับให้เอง พร้อมเข้ารหัส salted SHA-256
    const struct {
        const char* username;
        const char* plainPass;
        const char* role;
        const char* fullName;
        const char* phone;
        const char* email;
    } defaults[] = {
        {"admin", "admin123", "admin", "System Administrator", "081-000-0001", "admin@hotel.com"},
        {"staff", "staff123", "staff", "Front Desk Staff",     "081-000-0002", "staff@hotel.com"},
        {"guest", "guest123", "guest", "สมชาย ใจดี",            "081-234-5678", "somchai@gmail.com"},
    };
    for (const auto& d : defaults) {
        if (!find(d.username)) {
            User u;
            u.username = d.username;
            u.password = crypto::createPasswordRecord(d.plainPass);
            u.role     = d.role;
            u.fullName = d.fullName;
            u.phone    = d.phone;
            u.email    = d.email;
            g_users.push_back(u);
        }
    }
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
    if (!u) return nullptr;

    bool needsUpgrade = false;
    if (crypto::verifyPasswordRecord(password, u->password, &needsUpgrade)) {
        if (needsUpgrade) {
            // Auto-upgrade legacy plaintext password to cryptographic salted SHA-256
            u->password = crypto::createPasswordRecord(password);
            hotel::saveAll();
            hotel::logAction("system", "security", "PASSWORD_MIGRATED",
                             "User " + u->username, "Upgraded legacy password to Salted SHA-256");
            std::cout << "[SECURITY] อัปเกรดรหัสผ่านของผู้ใช้ " << u->username << " เป็น Salted SHA-256 สำเร็จ\n";
        }
        return u;
    }

    return nullptr;
}

Result registerGuest(const std::string& username,
                     const std::string& password,
                     const std::string& fullName,
                     const std::string& phone,
                     const std::string& email) {
    return createUser(username, password, "guest", fullName, phone, email);
}

Result createUser(const std::string& username,
                  const std::string& password,
                  const std::string& role,
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

    std::string safeRole = role;
    if (safeRole != "admin" && safeRole != "staff" && safeRole != "guest") {
        safeRole = "guest";
    }

    User u;
    u.username = username;
    u.password = crypto::createPasswordRecord(password);
    u.role = safeRole;
    u.fullName = fullName;
    u.phone = phone;
    u.email = email;

    g_users.push_back(u);
    hotel::saveAll();

    hotel::logAction("admin", "admin", "USER_CREATED",
                     "User " + u.username, "Role: " + u.role + ", Name: " + u.fullName);

    std::cout << "[USER] สร้างผู้ใช้ใหม่: " << u.username << " (" << u.role << ", " << u.fullName << ")\n";

    r.ok = true;
    return r;
}

Result updateUser(const std::string& username,
                  const std::string& role,
                  const std::string& fullName,
                  const std::string& phone,
                  const std::string& email,
                  const std::string& newPassword) {
    Result r;
    User* u = find(username);
    if (!u) {
        r.ok = false;
        r.httpCode = "404 Not Found";
        r.error = "ไม่พบบัญชีผู้ใช้ " + username;
        return r;
    }

    std::string safeRole = role.empty() ? u->role : role;
    if (safeRole != "admin" && safeRole != "staff" && safeRole != "guest") {
        safeRole = u->role;
    }

    // ป้องกันการปลด admin คนสุดท้ายออกจากระบบ
    if (u->role == "admin" && safeRole != "admin") {
        int adminCount = 0;
        for (const auto& usr : g_users) {
            if (usr.role == "admin") adminCount++;
        }
        if (adminCount <= 1) {
            r.ok = false;
            r.httpCode = "400 Bad Request";
            r.error = "ไม่สามารถเปลี่ยนบทบาทได้ เนื่องจากเป็นผู้ดูแลระบบ (Admin) คนสุดท้ายในระบบ";
            return r;
        }
    }

    std::string diff = "Role: " + u->role + "->" + safeRole;
    u->role = safeRole;
    if (!fullName.empty()) { diff += ", Name: " + fullName; u->fullName = fullName; }
    if (!phone.empty())    { diff += ", Phone: " + phone; u->phone = phone; }
    if (!email.empty())    { diff += ", Email: " + email; u->email = email; }

    if (!newPassword.empty()) {
        if (newPassword.size() < 4) {
            r.ok = false;
            r.httpCode = "400 Bad Request";
            r.error = "รหัสผ่านใหม่ต้องมีความยาวอย่างน้อย 4 ตัวอักษร";
            return r;
        }
        u->password = crypto::createPasswordRecord(newPassword);
        diff += ", Password reset to new Salted SHA-256";
    }

    hotel::saveAll();
    hotel::logAction("admin", "admin", "USER_UPDATED", "User " + u->username, diff);

    r.ok = true;
    return r;
}

Result deleteUser(const std::string& username, const std::string& actorUsername) {
    Result r;
    if (username == actorUsername) {
        r.ok = false;
        r.httpCode = "400 Bad Request";
        r.error = "ไม่สามารถลบบัญชีของตนเองที่กำลังเข้าสู่ระบบอยู่ได้";
        return r;
    }

    auto it = std::find_if(g_users.begin(), g_users.end(),
                           [&](const User& u) { return u.username == username; });
    if (it == g_users.end()) {
        r.ok = false;
        r.httpCode = "404 Not Found";
        r.error = "ไม่พบบัญชีผู้ใช้ " + username;
        return r;
    }

    // ห้ามลบ admin คนสุดท้าย
    if (it->role == "admin") {
        int adminCount = 0;
        for (const auto& usr : g_users) {
            if (usr.role == "admin") adminCount++;
        }
        if (adminCount <= 1) {
            r.ok = false;
            r.httpCode = "400 Bad Request";
            r.error = "ไม่สามารถลบบัญชีผู้ดูแลระบบคนสุดท้ายได้";
            return r;
        }
    }

    std::string deletedRole = it->role;
    std::string deletedName = it->fullName;
    g_users.erase(it);

    hotel::saveAll();
    hotel::logAction(actorUsername.empty() ? "admin" : actorUsername, "admin",
                     "USER_DELETED", "User " + username, "Deleted user (" + deletedRole + ", " + deletedName + ")");

    std::cout << "[USER] ลบผู้ใช้: " << username << "\n";

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
