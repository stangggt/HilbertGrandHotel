#include "User.hpp"
#include <sstream>
#include <vector>
#include <algorithm>

User::User()
    : m_username(""), m_password(""), m_role(UserRole::GUEST),
      m_fullName(""), m_phone(""), m_email("") {}

User::User(const std::string& username, const std::string& password, UserRole role,
           const std::string& fullName, const std::string& phone,
           const std::string& email)
    : m_username(username), m_password(password), m_role(role),
      m_fullName(fullName), m_phone(phone), m_email(email) {}

bool User::authenticate(const std::string& passwordAttempt) const noexcept {
    return !m_username.empty() && (m_password == passwordAttempt);
}

std::string User::roleToString(UserRole role) {
    switch (role) {
        case UserRole::ADMIN: return "ADMIN";
        case UserRole::STAFF: return "STAFF";
        case UserRole::GUEST: return "GUEST";
        default:              return "GUEST";
    }
}

UserRole User::stringToRole(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "ADMIN") return UserRole::ADMIN;
    if (s == "STAFF" || s == "HOUSEKEEPER") return UserRole::STAFF;
    return UserRole::GUEST;
}

std::string User::toCsvRow() const {
    std::ostringstream ss;
    ss << m_username << ","
       << m_password << ","
       << roleToString(m_role) << ","
       << m_fullName << ","
       << m_phone << ","
       << m_email;
    return ss.str();
}

User User::fromCsvRow(const std::string& row) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(row);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 3) {
        return User();
    }

    std::string username = tokens[0];
    std::string password = tokens[1];
    UserRole role = stringToRole(tokens[2]);
    std::string fullName = tokens.size() > 3 ? tokens[3] : "";
    std::string phone = tokens.size() > 4 ? tokens[4] : "";
    std::string email = tokens.size() > 5 ? tokens[5] : "";

    return User(username, password, role, fullName, phone, email);
}
