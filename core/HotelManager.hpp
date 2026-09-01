#ifndef HOTEL_MANAGER_HPP
#define HOTEL_MANAGER_HPP

#include "DynamicArray.hpp"
#include "Room.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "Algorithms.hpp"
#include <string>

class HotelManager {
private:
    DynamicArray<Room> m_rooms;
    DynamicArray<User> m_users;
    DynamicArray<Transaction> m_transactions;

    std::string m_roomsPath;
    std::string m_usersPath;
    std::string m_transactionsPath;

    User m_currentUser;
    bool m_isLoggedIn;

    std::string generateTransactionId();

public:
    HotelManager();
    explicit HotelManager(const std::string& roomsPath,
                          const std::string& usersPath = "data/users.csv",
                          const std::string& transactionsPath = "data/transactions.csv");

    // Persistence
    bool loadDatabase(const std::string& roomsPath = "data/rooms.csv",
                      const std::string& usersPath = "data/users.csv",
                      const std::string& transactionsPath = "data/transactions.csv");
    bool saveDatabase();
    bool saveRooms();
    bool saveUsers();
    bool saveTransactions();

    // Authentication
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool registerUser(const std::string& username, const std::string& password,
                      UserRole role, const std::string& fullName,
                      const std::string& phone, const std::string& email);
    bool userExists(const std::string& username) const;
    const User& getCurrentUser() const noexcept { return m_currentUser; }
    bool isLoggedIn() const noexcept { return m_isLoggedIn; }

    // Room CRUD Operations
    bool addRoom(const Room& room);
    Room* findRoomByNumber(int roomNumber);
    const Room* findRoomByNumber(int roomNumber) const;
    bool updateRoom(const Room& updatedRoom);
    bool deleteRoom(int roomNumber);

    // Queries, Filters, Sorting
    DynamicArray<Room> getAllRooms() const { return m_rooms; }
    DynamicArray<Room> getAvailableRooms() const;
    DynamicArray<Room> filterRooms(bool filterType, RoomType type,
                                  bool availableOnly,
                                  double maxPrice = 0.0,
                                  int floor = 0) const;
    DynamicArray<Room> getSortedRoomsByPrice(bool ascending = true) const;
    DynamicArray<Room> getSortedRoomsByNumber() const;
    DynamicArray<Room> getRoomsByFloor(int floor) const;

    // Booking & Check-in / Check-out Operations
    bool checkIn(int roomNumber, const std::string& guestUsername, int nights,
                 const std::string& checkInDate = "",
                 std::string* outTxnId = nullptr,
                 double* outTotal = nullptr);

    bool checkOut(int roomNumber, double* outFinalBill = nullptr);

    DynamicArray<Room> getRoomsBookedByGuest(const std::string& guestUsername) const;
    DynamicArray<Transaction> getGuestTransactions(const std::string& guestUsername) const;

    // Housekeeping & Maintenance
    bool setHousekeepingStatus(int roomNumber, HousekeepingStatus status);
    bool setRoomStatus(int roomNumber, RoomStatus status);
    DynamicArray<Room> getRoomsNeedingCleaning() const;

    // Hotel Analytics & Statistics
    double calculateTotalRevenue() const;
    double calculateOccupancyRate() const;
    int getTotalRoomsCount() const noexcept { return static_cast<int>(m_rooms.size()); }
    int getOccupiedRoomsCount() const;
    int getAvailableRoomsCount() const;
    int getMaintenanceRoomsCount() const;
    int getCleaningRoomsCount() const;

    DynamicArray<User> getAllUsers() const { return m_users; }
    DynamicArray<Transaction> getAllTransactions() const { return m_transactions; }
};

#endif // HOTEL_MANAGER_HPP
