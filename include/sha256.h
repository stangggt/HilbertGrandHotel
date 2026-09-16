// ============================================================
//  sha256.h — SHA-256 cryptographic hash & password salting
//  Standard FIPS 180-4 compliant implementation
// ============================================================
#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace crypto {

// คำนวณ SHA-256 จากข้อมูลสตริง คืนค่าเป็น hex 64 ตัวอักษร (ตัวพิมพ์เล็ก)
std::string sha256(const std::string& input);
std::string sha256(const uint8_t* data, size_t length);

// สุ่ม salt แบบ hex ด้วย std::random_device + std::mt19937_64
std::string generateSalt(size_t length = 16);

// คำนวณ hash พร้อม salt: SHA256(salt + "$" + password)
std::string hashPasswordWithSalt(const std::string& password, const std::string& salt);

// สร้างสตริงสำหรับเก็บในฐานข้อมูล: "sha256$<salt>$<hash>"
std::string createPasswordRecord(const std::string& plainPassword);

// ตรวจสอบรหัสผ่าน: รองรับทั้ง "sha256$<salt>$<hash>" และ plaintext เดิม
// คืนค่า true หากรหัสผ่านถูกต้อง และเซ็ต outNeedsUpgrade เป็น true หากเป็น plaintext เดิม
bool verifyPasswordRecord(const std::string& plainPassword,
                          const std::string& storedRecord,
                          bool* outNeedsUpgrade = nullptr);

} // namespace crypto
