#include "HotelManager.hpp"
#include "CsvDatabase.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

static std::string getCurrentDateString() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::ostringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-"
       << std::setw(2) << std::setfill('0') << now->tm_mday;
    return ss.str();
}

static std::string getCurrentDateTimeString() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::ostringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-"
       << std::setw(2) << std::setfill('0') << now->tm_mday << " "
       << std::setw(2) << std::setfill('0') << now->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << now->tm_min << ":"
       << std::setw(2) << std::setfill('0') << now->tm_sec;
    return ss.str();
}

HotelManager::HotelManager()
    : m_roomsPath("data/rooms.csv"),
      m_usersPath("data/users.csv"),
      m_transactionsPath("data/transactions.csv"),
      m_isLoggedIn(false) {}

HotelManager::HotelManager(const std::string& roomsPath,
                           const std::string& usersPath,
                           const std::string& transactionsPath)
    : m_roomsPath(roomsPath),
      m_usersPath(usersPath),
      m_transactionsPath(transactionsPath),
      m_isLoggedIn(false) {
    loadDatabase(m_roomsPath, m_usersPath, m_transactionsPath);
}

std::string HotelManager::generateTransactionId() {
    std::ostringstream ss;
    ss << "TXN-" << (1000 + m_transactions.size() + 1);
    return ss.str();
}

bool HotelManager::loadDatabase(const std::string& roomsPath,
                                const std::string& usersPath,
                                const std::string& transactionsPath) {
    m_roomsPath = roomsPath;
    m_usersPath = usersPath;
    m_transactionsPath = transactionsPath;

    // Load Rooms
    m_rooms.clear();
    DynamicArray<std::string> roomRows = CsvDatabase::readRows(m_roomsPath, true);
    for (size_t i = 0; i < roomRows.size(); ++i) {
        Room r = Room::fromCsvRow(roomRows[i]);
        if (r.getRoomNumber() > 0) {
            m_rooms.push_back(r);
        }
    }

    // Load Users
    m_users.clear();
    DynamicArray<std::string> userRows = CsvDatabase::readRows(m_usersPath, true);
    for (size_t i = 0; i < userRows.size(); ++i) {
        User u = User::fromCsvRow(userRows[i]);
        if (!u.getUsername().empty()) {
            m_users.push_back(u);
        }
    }

    // Ensure default admin exists if empty
    if (m_users.empty()) {
        m_users.push_back(User("admin", "admin123", UserRole::ADMIN, "Default Admin", "+1-000-0000", "admin@hotel.com"));
        m_users.push_back(User("staff", "staff123", UserRole::STAFF, "Default Staff", "+1-000-0001", "staff@hotel.com"));
    }

    // Load Transactions
    m_transactions.clear();
    DynamicArray<std::string> txnRows = CsvDatabase::readRows(m_transactionsPath, true);
    for (size_t i = 0; i < txnRows.size(); ++i) {
        Transaction t = Transaction::fromCsvRow(txnRows[i]);
        if (!t.getTransactionId().empty()) {
            m_transactions.push_back(t);
        }
    }

    return true;
}

bool HotelManager::saveRooms() {
    const std::string header = "room_number,floor,room_type,bed_type,capacity,price_per_night,amenities,status,housekeeping_status,current_guest,booked_nights,check_in_date";
    DynamicArray<std::string> rows;
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        rows.push_back(m_rooms[i].toCsvRow());
    }
    return CsvDatabase::writeRows(m_roomsPath, header, rows);
}

bool HotelManager::saveUsers() {
    const std::string header = "username,password,role,full_name,phone,email";
    DynamicArray<std::string> rows;
    for (size_t i = 0; i < m_users.size(); ++i) {
        rows.push_back(m_users[i].toCsvRow());
    }
    return CsvDatabase::writeRows(m_usersPath, header, rows);
}

bool HotelManager::saveTransactions() {
    const std::string header = "transaction_id,room_number,guest_username,nights,rate_per_night,total_amount,timestamp,status";
    DynamicArray<std::string> rows;
    for (size_t i = 0; i < m_transactions.size(); ++i) {
        rows.push_back(m_transactions[i].toCsvRow());
    }
    return CsvDatabase::writeRows(m_transactionsPath, header, rows);
}

bool HotelManager::saveDatabase() {
    bool ok1 = saveRooms();
    bool ok2 = saveUsers();
    bool ok3 = saveTransactions();
    return ok1 && ok2 && ok3;
}

bool HotelManager::login(const std::string& username, const std::string& password) {
    for (size_t i = 0; i < m_users.size(); ++i) {
        if (m_users[i].getUsername() == username && m_users[i].authenticate(password)) {
            m_currentUser = m_users[i];
            m_isLoggedIn = true;
            return true;
        }
    }
    return false;
}

void HotelManager::logout() {
    m_currentUser = User();
    m_isLoggedIn = false;
}

bool HotelManager::userExists(const std::string& username) const {
    for (size_t i = 0; i < m_users.size(); ++i) {
        if (m_users[i].getUsername() == username) {
            return true;
        }
    }
    return false;
}

bool HotelManager::registerUser(const std::string& username, const std::string& password,
                               UserRole role, const std::string& fullName,
                               const std::string& phone, const std::string& email) {
    if (username.empty() || password.empty() || userExists(username)) {
        return false;
    }

    User newUser(username, password, role, fullName, phone, email);
    m_users.push_back(newUser);
    saveUsers();
    return true;
}

bool HotelManager::addRoom(const Room& room) {
    if (findRoomByNumber(room.getRoomNumber()) != nullptr) {
        return false; // Duplicate room number
    }
    m_rooms.push_back(room);
    saveRooms();
    return true;
}

Room* HotelManager::findRoomByNumber(int roomNumber) {
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getRoomNumber() == roomNumber) {
            return &m_rooms[i];
        }
    }
    return nullptr;
}

const Room* HotelManager::findRoomByNumber(int roomNumber) const {
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getRoomNumber() == roomNumber) {
            return &m_rooms[i];
        }
    }
    return nullptr;
}

bool HotelManager::updateRoom(const Room& updatedRoom) {
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getRoomNumber() == updatedRoom.getRoomNumber()) {
            m_rooms[i] = updatedRoom;
            saveRooms();
            return true;
        }
    }
    return false;
}

bool HotelManager::deleteRoom(int roomNumber) {
    int idx = Algorithms::findIndex(m_rooms, [roomNumber](const Room& r) {
        return r.getRoomNumber() == roomNumber;
    });

    if (idx >= 0) {
        m_rooms.remove_at(static_cast<size_t>(idx));
        saveRooms();
        return true;
    }
    return false;
}

DynamicArray<Room> HotelManager::getAvailableRooms() const {
    return Algorithms::filter(m_rooms, [](const Room& r) {
        return r.isAvailableForBooking();
    });
}

DynamicArray<Room> HotelManager::filterRooms(bool filterType, RoomType type,
                                            bool availableOnly,
                                            double maxPrice,
                                            int floor) const {
    return Algorithms::filter(m_rooms, [=](const Room& r) {
        if (filterType && r.getRoomType() != type) return false;
        if (availableOnly && !r.isAvailableForBooking()) return false;
        if (maxPrice > 0.0 && r.getPricePerNight() > maxPrice) return false;
        if (floor > 0 && r.getFloor() != floor) return false;
        return true;
    });
}

DynamicArray<Room> HotelManager::getSortedRoomsByPrice(bool ascending) const {
    DynamicArray<Room> sorted = m_rooms;
    if (ascending) {
        Algorithms::quickSort(sorted, [](const Room& a, const Room& b) {
            return a.getPricePerNight() < b.getPricePerNight();
        });
    } else {
        Algorithms::quickSort(sorted, [](const Room& a, const Room& b) {
            return a.getPricePerNight() > b.getPricePerNight();
        });
    }
    return sorted;
}

DynamicArray<Room> HotelManager::getSortedRoomsByNumber() const {
    DynamicArray<Room> sorted = m_rooms;
    Algorithms::quickSort(sorted, [](const Room& a, const Room& b) {
        return a.getRoomNumber() < b.getRoomNumber();
    });
    return sorted;
}

DynamicArray<Room> HotelManager::getRoomsByFloor(int floor) const {
    return Algorithms::filter(m_rooms, [floor](const Room& r) {
        return r.getFloor() == floor;
    });
}

bool HotelManager::checkIn(int roomNumber, const std::string& guestUsername, int nights,
                           const std::string& checkInDate,
                           std::string* outTxnId,
                           double* outTotal) {
    Room* room = findRoomByNumber(roomNumber);
    if (!room) return false;
    if (!room->isAvailableForBooking()) return false;
    if (nights <= 0) return false;

    std::string date = checkInDate.empty() ? getCurrentDateString() : checkInDate;
    room->book(guestUsername, nights, date);

    double total = room->calculateTotalPrice(nights);
    std::string txnId = generateTransactionId();
    std::string timestamp = getCurrentDateTimeString();

    Transaction txn(txnId, roomNumber, guestUsername, nights, room->getPricePerNight(), total, timestamp, TransactionStatus::ACTIVE);
    m_transactions.push_back(txn);

    if (outTxnId) *outTxnId = txnId;
    if (outTotal) *outTotal = total;

    saveRooms();
    saveTransactions();
    return true;
}

bool HotelManager::checkOut(int roomNumber, double* outFinalBill) {
    Room* room = findRoomByNumber(roomNumber);
    if (!room || room->getStatus() != RoomStatus::OCCUPIED) {
        return false;
    }

    double finalBill = room->calculateTotalPrice(room->getBookedNights());
    if (outFinalBill) {
        *outFinalBill = finalBill;
    }

    // Mark associated transaction as COMPLETED
    for (size_t i = 0; i < m_transactions.size(); ++i) {
        if (m_transactions[i].getRoomNumber() == roomNumber &&
            m_transactions[i].getStatus() == TransactionStatus::ACTIVE) {
            m_transactions[i].setStatus(TransactionStatus::COMPLETED);
            break;
        }
    }

    room->checkOut();
    saveRooms();
    saveTransactions();
    return true;
}

DynamicArray<Room> HotelManager::getRoomsBookedByGuest(const std::string& guestUsername) const {
    return Algorithms::filter(m_rooms, [&guestUsername](const Room& r) {
        return r.getStatus() == RoomStatus::OCCUPIED && r.getCurrentGuest() == guestUsername;
    });
}

DynamicArray<Transaction> HotelManager::getGuestTransactions(const std::string& guestUsername) const {
    return Algorithms::filter(m_transactions, [&guestUsername](const Transaction& t) {
        return t.getGuestUsername() == guestUsername;
    });
}

bool HotelManager::setHousekeepingStatus(int roomNumber, HousekeepingStatus status) {
    Room* room = findRoomByNumber(roomNumber);
    if (!room) return false;
    room->setHousekeepingStatus(status);
    saveRooms();
    return true;
}

bool HotelManager::setRoomStatus(int roomNumber, RoomStatus status) {
    Room* room = findRoomByNumber(roomNumber);
    if (!room) return false;
    room->setStatus(status);
    saveRooms();
    return true;
}

DynamicArray<Room> HotelManager::getRoomsNeedingCleaning() const {
    return Algorithms::filter(m_rooms, [](const Room& r) {
        return r.getHousekeepingStatus() == HousekeepingStatus::CLEANING ||
               r.getHousekeepingStatus() == HousekeepingStatus::NEEDS_INSPECTION;
    });
}

double HotelManager::calculateTotalRevenue() const {
    double total = 0.0;
    for (size_t i = 0; i < m_transactions.size(); ++i) {
        if (m_transactions[i].getStatus() != TransactionStatus::CANCELLED) {
            total += m_transactions[i].getTotalAmount();
        }
    }
    return total;
}

double HotelManager::calculateOccupancyRate() const {
    if (m_rooms.empty()) return 0.0;
    int occupied = getOccupiedRoomsCount();
    return (static_cast<double>(occupied) / static_cast<double>(m_rooms.size())) * 100.0;
}

int HotelManager::getOccupiedRoomsCount() const {
    int count = 0;
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getStatus() == RoomStatus::OCCUPIED) ++count;
    }
    return count;
}

int HotelManager::getAvailableRoomsCount() const {
    int count = 0;
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].isAvailableForBooking()) ++count;
    }
    return count;
}

int HotelManager::getMaintenanceRoomsCount() const {
    int count = 0;
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getStatus() == RoomStatus::MAINTENANCE) ++count;
    }
    return count;
}

int HotelManager::getCleaningRoomsCount() const {
    int count = 0;
    for (size_t i = 0; i < m_rooms.size(); ++i) {
        if (m_rooms[i].getHousekeepingStatus() == HousekeepingStatus::CLEANING) ++count;
    }
    return count;
}
