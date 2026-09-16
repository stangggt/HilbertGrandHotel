// ============================================================
//  test_suite.cpp — Automated Regression & Unit Testing Suite
// ============================================================
#include "../include/sha256.h"
#include "../include/user.h"
#include "../include/reservation.h"
#include "../include/hotel.h"
#include "../include/utils.h"
#include "../include/xlsx.h"
#include "../include/console_utils.h"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <filesystem>

static int g_testsPassed = 0;
static int g_testsFailed = 0;

#define TEST_CASE(name) static void name(); \
    struct Runner_##name { Runner_##name() { \
        std::cout << "  [RUN] " << #name << " ... "; \
        try { \
            name(); \
            std::cout << "\033[32mPASSED\033[0m\n"; \
            g_testsPassed++; \
        } catch (const std::exception& e) { \
            std::cout << "\033[31mFAILED: " << e.what() << "\033[0m\n"; \
            g_testsFailed++; \
        } catch (...) { \
            std::cout << "\033[31mFAILED (Unknown exception)\033[0m\n"; \
            g_testsFailed++; \
        } \
    } };

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        throw std::runtime_error("Assertion failed: " #cond " at line " + std::to_string(__LINE__)); \
    } \
} while (0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

#define ASSERT_EQ(a, b) do { \
    if ((a) != (b)) { \
        throw std::runtime_error("Assertion failed: " #a " == " #b " at line " + std::to_string(__LINE__)); \
    } \
} while (0)

// ------------------------------------------------------------
// TEST 1: SHA-256 Known Vectors, Salting & Legacy Migration
// ------------------------------------------------------------
void testSha256AndSalting() {
    // Known NIST / FIPS 180-4 test vectors
    ASSERT_EQ(crypto::sha256(""),
              "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    ASSERT_EQ(crypto::sha256("abc"),
              "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    ASSERT_EQ(crypto::sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
              "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");

    // Salt generation
    std::string salt1 = crypto::generateSalt(16);
    std::string salt2 = crypto::generateSalt(16);
    ASSERT_EQ(salt1.size(), 16u);
    ASSERT_EQ(salt2.size(), 16u);
    ASSERT_TRUE(salt1 != salt2);

    // Password record creation & verification
    std::string record = crypto::createPasswordRecord("Secret1234");
    ASSERT_TRUE(record.rfind("sha256$", 0) == 0);

    bool needsUpgrade = false;
    ASSERT_TRUE(crypto::verifyPasswordRecord("Secret1234", record, &needsUpgrade));
    ASSERT_FALSE(needsUpgrade);
    ASSERT_FALSE(crypto::verifyPasswordRecord("WrongPassword", record, nullptr));

    // Legacy plaintext migration check
    bool legacyUpgrade = false;
    ASSERT_TRUE(crypto::verifyPasswordRecord("legacyPlain123", "legacyPlain123", &legacyUpgrade));
    ASSERT_TRUE(legacyUpgrade);
    ASSERT_FALSE(crypto::verifyPasswordRecord("wrong", "legacyPlain123", nullptr));
}

// ------------------------------------------------------------
// TEST 2: User RBAC, Creation, Update & Authentication
// ------------------------------------------------------------
void testUserAuthenticationAndRbac() {
    user::g_users.clear();
    user::seedDefaults();

    User* admin = user::find("admin");
    ASSERT_TRUE(admin != nullptr);
    ASSERT_TRUE(admin->isAdmin());
    ASSERT_TRUE(admin->isStaff());
    ASSERT_FALSE(admin->isGuest());

    User* staff = user::find("staff");
    ASSERT_TRUE(staff != nullptr);
    ASSERT_FALSE(staff->isAdmin());
    ASSERT_TRUE(staff->isStaff());

    User* guest = user::find("guest");
    ASSERT_TRUE(guest != nullptr);
    ASSERT_FALSE(guest->isAdmin());
    ASSERT_TRUE(guest->isGuest());

    // Authentication test
    User* authUser = user::authenticate("admin", "admin123");
    ASSERT_TRUE(authUser != nullptr);
    ASSERT_EQ(authUser->username, "admin");

    User* failAuth = user::authenticate("admin", "wrongpass");
    ASSERT_TRUE(failAuth == nullptr);

    // User creation test
    Result r1 = user::createUser("newmanager", "pass1234", "staff", "Manager Test", "081-999-9999", "mgr@test.com");
    ASSERT_TRUE(r1.ok);
    User* created = user::find("newmanager");
    ASSERT_TRUE(created != nullptr);
    ASSERT_EQ(created->role, "staff");
    ASSERT_TRUE(created->password.rfind("sha256$", 0) == 0);

    // Duplicate username test
    Result rDup = user::createUser("newmanager", "pass1234", "guest", "Dup", "081-000-0000", "dup@test.com");
    ASSERT_FALSE(rDup.ok);

    // Update user role and password
    Result rUpd = user::updateUser("newmanager", "admin", "Manager Promoted", "081-888-8888", "mgr2@test.com", "newpass99");
    ASSERT_TRUE(rUpd.ok);
    User* updated = user::find("newmanager");
    ASSERT_EQ(updated->role, "admin");
    ASSERT_EQ(updated->fullName, "Manager Promoted");
    ASSERT_TRUE(user::authenticate("newmanager", "newpass99") != nullptr);

    // Delete user test
    Result rDel = user::deleteUser("newmanager", "admin");
    ASSERT_TRUE(rDel.ok);
    ASSERT_TRUE(user::find("newmanager") == nullptr);
    hotel::loadAll();
}

// ------------------------------------------------------------
// TEST 3: Date-Interval Collision Algorithm
// ------------------------------------------------------------
void testDateCollisionAlgorithm() {
    // Formula: max(S1, S2) < min(E1, E2)
    // Scenario 1: Same-day turnover (Guest A checks out 2026-10-04, Guest B checks in 2026-10-04)
    ASSERT_FALSE(reservation::datesOverlap("2026-10-01", "2026-10-04", "2026-10-04", "2026-10-07"));

    // Scenario 2: Overlapping by 1 day
    ASSERT_TRUE(reservation::datesOverlap("2026-10-01", "2026-10-04", "2026-10-03", "2026-10-06"));

    // Scenario 3: Complete subset
    ASSERT_TRUE(reservation::datesOverlap("2026-10-01", "2026-10-10", "2026-10-03", "2026-10-05"));

    // Scenario 4: Superset
    ASSERT_TRUE(reservation::datesOverlap("2026-10-03", "2026-10-05", "2026-10-01", "2026-10-10"));

    // Scenario 5: Distant non-overlapping dates
    ASSERT_FALSE(reservation::datesOverlap("2026-10-01", "2026-10-03", "2026-11-01", "2026-11-05"));
}

// ------------------------------------------------------------
// TEST 4: OpenXML Excel Multi-Sheet Roundtrip Integrity
// ------------------------------------------------------------
void testOpenXmlMultiSheetRoundtrip() {
    const std::string testFile = "data/test_roundtrip.xlsx";

    xlsx::Book book;

    // Sheet 1: rooms
    xlsx::Sheet s1;
    s1.name = "rooms";
    s1.header = {"id", "floor", "bed", "tier", "price", "note"};
    s1.rows.push_back({"101", "1", "twin", "normal", "1450", "City View"});
    s1.rows.push_back({"201", "2", "king", "deluxe", "2400", "Ocean View"});
    book.push_back(s1);

    // Sheet 2: users
    xlsx::Sheet s2;
    s2.name = "users";
    s2.header = {"username", "password", "role", "fullName", "phone", "email"};
    s2.rows.push_back({"admin", "sha256$test$hash", "admin", "Admin Test", "081-000", "admin@test.com"});
    book.push_back(s2);

    // Sheet 3: audit_log
    xlsx::Sheet s3;
    s3.name = "audit_log";
    s3.header = {"id", "timestamp", "actorUser", "actorRole", "actionType", "targetEntity", "diff"};
    s3.rows.push_back({"LOG-0001", "2026-09-15 12:00:00", "admin", "admin", "TEST", "Entity", "Test diff"});
    book.push_back(s3);

    // Write workbook
    ASSERT_TRUE(xlsx::write(testFile, book));

    // Read back workbook
    xlsx::Book readBook;
    ASSERT_TRUE(xlsx::read(testFile, readBook));

    ASSERT_EQ(readBook.size(), 3u);
    const xlsx::Sheet* rRooms = xlsx::find(readBook, "rooms");
    ASSERT_TRUE(rRooms != nullptr);
    ASSERT_EQ(rRooms->rows.size(), 2u);
    ASSERT_EQ(rRooms->rows[0][0], "101");
    ASSERT_EQ(rRooms->rows[1][4], "2400");

    const xlsx::Sheet* rUsers = xlsx::find(readBook, "users");
    ASSERT_TRUE(rUsers != nullptr);
    ASSERT_EQ(rUsers->rows[0][0], "admin");
    ASSERT_EQ(rUsers->rows[0][2], "admin");

    const xlsx::Sheet* rAudit = xlsx::find(readBook, "audit_log");
    ASSERT_TRUE(rAudit != nullptr);
    ASSERT_EQ(rAudit->rows[0][0], "LOG-0001");

    // Clean up test file
    std::filesystem::remove(testFile);
}

// ------------------------------------------------------------
// TEST 5: Thai Unicode Display Width Calculation
// ------------------------------------------------------------
void testThaiUnicodeDisplayWidth() {
    // Pure ASCII
    ASSERT_EQ(ConsoleUtils::displayWidth("Hello"), 5);
    ASSERT_EQ(ConsoleUtils::displayWidth("1234567890"), 10);

    // Thai characters with combining vowel & tone marks:
    // "สมชาย" -> ส (1) + ม (1) + ช (1) + า (1) + ย (1) = 5
    ASSERT_EQ(ConsoleUtils::displayWidth("สมชาย"), 5);

    // "น้ำ" -> น (1) + ้ (0, tone mark) + ำ (1 or 2 depending on unicode normalization)
    // Verify width > 0
    ASSERT_TRUE(ConsoleUtils::displayWidth("น้ำ") >= 2);
}

// ------------------------------------------------------------
// TEST 6: Automated Database Backup Snapshot
// ------------------------------------------------------------
void testDatabaseBackupCreation() {
    std::string backupPath;
    bool ok = hotel::createBackupSnapshot(&backupPath);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(std::filesystem::exists(backupPath));
    ASSERT_TRUE(backupPath.find("data/backups/hotel_") != std::string::npos);
}

int main() {
    std::cout << "\n==================================================\n";
    std::cout << " HILBERT GRAND HOTEL — AUTOMATED TEST SUITE\n";
    std::cout << "==================================================\n\n";

    // Load initial hotel database so rooms and types are populated
    hotel::loadAll();

    std::cout << "Running test suite...\n";

    #define RUN_TEST(fn) do { \
        std::cout << "  [TEST] " << #fn << " ... "; \
        try { \
            fn(); \
            std::cout << "\033[32mPASSED\033[0m\n"; \
            g_testsPassed++; \
        } catch (const std::exception& e) { \
            std::cout << "\033[31mFAILED: " << e.what() << "\033[0m\n"; \
            g_testsFailed++; \
        } catch (...) { \
            std::cout << "\033[31mFAILED (Unknown exception)\033[0m\n"; \
            g_testsFailed++; \
        } \
    } while(0)

    RUN_TEST(testSha256AndSalting);
    RUN_TEST(testUserAuthenticationAndRbac);
    RUN_TEST(testDateCollisionAlgorithm);
    RUN_TEST(testOpenXmlMultiSheetRoundtrip);
    RUN_TEST(testThaiUnicodeDisplayWidth);
    RUN_TEST(testDatabaseBackupCreation);

    std::cout << "\n--------------------------------------------------\n";
    std::cout << " Results: " << g_testsPassed << " passed, " << g_testsFailed << " failed.\n";
    std::cout << "==================================================\n\n";

    return (g_testsFailed == 0) ? 0 : 1;
}
