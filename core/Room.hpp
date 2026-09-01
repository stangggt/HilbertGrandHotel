#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <iostream>

enum class RoomType {
    STANDARD,
    DELUXE,
    VIP
};

enum class BedType {
    SINGLE,
    DOUBLE,
    KING
};

enum class RoomStatus {
    AVAILABLE,
    OCCUPIED,
    MAINTENANCE
};

enum class HousekeepingStatus {
    READY,
    CLEANING,
    NEEDS_INSPECTION
};

class Room {
private:
    int m_roomNumber;
    int m_floor;
    RoomType m_roomType;
    BedType m_bedType;
    int m_capacity;
    double m_pricePerNight;
    std::string m_amenities; // Semicolon-delimited, e.g., "TV;AC;WiFi;Breakfast"
    RoomStatus m_status;
    HousekeepingStatus m_housekeepingStatus;
    std::string m_currentGuest;
    int m_bookedNights;
    std::string m_checkInDate;

public:
    Room();
    Room(int roomNumber, int floor, RoomType roomType, BedType bedType, int capacity,
         double pricePerNight, const std::string& amenities,
         RoomStatus status = RoomStatus::AVAILABLE,
         HousekeepingStatus housekeepingStatus = HousekeepingStatus::READY,
         const std::string& currentGuest = "", int bookedNights = 0,
         const std::string& checkInDate = "");

    // Getters
    int getRoomNumber() const noexcept { return m_roomNumber; }
    int getFloor() const noexcept { return m_floor; }
    RoomType getRoomType() const noexcept { return m_roomType; }
    BedType getBedType() const noexcept { return m_bedType; }
    int getCapacity() const noexcept { return m_capacity; }
    double getPricePerNight() const noexcept { return m_pricePerNight; }
    const std::string& getAmenities() const noexcept { return m_amenities; }
    RoomStatus getStatus() const noexcept { return m_status; }
    HousekeepingStatus getHousekeepingStatus() const noexcept { return m_housekeepingStatus; }
    const std::string& getCurrentGuest() const noexcept { return m_currentGuest; }
    int getBookedNights() const noexcept { return m_bookedNights; }
    const std::string& getCheckInDate() const noexcept { return m_checkInDate; }

    // Setters
    void setRoomNumber(int roomNumber) { m_roomNumber = roomNumber; }
    void setFloor(int floor) { m_floor = floor; }
    void setRoomType(RoomType roomType) { m_roomType = roomType; }
    void setBedType(BedType bedType) { m_bedType = bedType; }
    void setCapacity(int capacity) { m_capacity = capacity; }
    void setPricePerNight(double price) { m_pricePerNight = price; }
    void setAmenities(const std::string& amenities) { m_amenities = amenities; }
    void setStatus(RoomStatus status) { m_status = status; }
    void setHousekeepingStatus(HousekeepingStatus status) { m_housekeepingStatus = status; }
    void setCurrentGuest(const std::string& guest) { m_currentGuest = guest; }
    void setBookedNights(int nights) { m_bookedNights = nights; }
    void setCheckInDate(const std::string& date) { m_checkInDate = date; }

    // Operations
    double calculateTotalPrice(int nights) const noexcept;
    bool isAvailableForBooking() const noexcept;
    void book(const std::string& guestName, int nights, const std::string& date);
    void checkOut();

    // String / CSV Helpers
    std::string toCsvRow() const;
    static Room fromCsvRow(const std::string& row);

    static std::string roomTypeToString(RoomType type);
    static RoomType stringToRoomType(const std::string& str);

    static std::string bedTypeToString(BedType type);
    static BedType stringToBedType(const std::string& str);

    static std::string roomStatusToString(RoomStatus status);
    static RoomStatus stringToRoomStatus(const std::string& str);

    static std::string housekeepingStatusToString(HousekeepingStatus status);
    static HousekeepingStatus stringToHousekeepingStatus(const std::string& str);
};

#endif // ROOM_HPP
