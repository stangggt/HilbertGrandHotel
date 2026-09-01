#ifndef USER_HPP
#define USER_HPP

#include <string>

enum class UserRole {
    GUEST,
    ADMIN,
    STAFF
};

class User {
private:
    std::string m_username;
    std::string m_password; // Plain/simple hash for university project
    UserRole m_role;
    std::string m_fullName;
    std::string m_phone;
    std::string m_email;

public:
    User();
    User(const std::string& username, const std::string& password, UserRole role,
         const std::string& fullName = "", const std::string& phone = "",
         const std::string& email = "");

    // Getters
    const std::string& getUsername() const noexcept { return m_username; }
    const std::string& getPassword() const noexcept { return m_password; }
    UserRole getRole() const noexcept { return m_role; }
    const std::string& getFullName() const noexcept { return m_fullName; }
    const std::string& getPhone() const noexcept { return m_phone; }
    const std::string& getEmail() const noexcept { return m_email; }

    // Setters
    void setPassword(const std::string& password) { m_password = password; }
    void setRole(UserRole role) { m_role = role; }
    void setFullName(const std::string& fullName) { m_fullName = fullName; }
    void setPhone(const std::string& phone) { m_phone = phone; }
    void setEmail(const std::string& email) { m_email = email; }

    // Helpers
    bool authenticate(const std::string& passwordAttempt) const noexcept;
    bool isAdmin() const noexcept { return m_role == UserRole::ADMIN; }
    bool isStaff() const noexcept { return m_role == UserRole::STAFF || m_role == UserRole::ADMIN; }
    bool isGuest() const noexcept { return m_role == UserRole::GUEST; }

    std::string toCsvRow() const;
    static User fromCsvRow(const std::string& row);

    static std::string roleToString(UserRole role);
    static UserRole stringToRole(const std::string& str);
};

#endif // USER_HPP
