#include "Room.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

Room::Room()
    : m_roomNumber(0), m_floor(1), m_roomType(RoomType::STANDARD),
      m_bedType(BedType::SINGLE), m_capacity(1), m_pricePerNight(0.0),
      m_amenities(""), m_status(RoomStatus::AVAILABLE),
      m_housekeepingStatus(HousekeepingStatus::READY),
      m_currentGuest(""), m_bookedNights(0), m_checkInDate("") {}

Room::Room(int roomNumber, int floor, RoomType roomType, BedType bedType, int capacity,
           double pricePerNight, const std::string& amenities,
           RoomStatus status, HousekeepingStatus housekeepingStatus,
           const std::string& currentGuest, int bookedNights,
           const std::string& checkInDate)
    : m_roomNumber(roomNumber), m_floor(floor), m_roomType(roomType),
      m_bedType(bedType), m_capacity(capacity), m_pricePerNight(pricePerNight),
      m_amenities(amenities), m_status(status),
      m_housekeepingStatus(housekeepingStatus),
      m_currentGuest(currentGuest), m_bookedNights(bookedNights),
      m_checkInDate(checkInDate) {}

double Room::calculateTotalPrice(int nights) const noexcept {
    if (nights <= 0) return 0.0;
    return m_pricePerNight * nights;
}

bool Room::isAvailableForBooking() const noexcept {
    return (m_status == RoomStatus::AVAILABLE) && (m_housekeepingStatus == HousekeepingStatus::READY);
}

void Room::book(const std::string& guestName, int nights, const std::string& date) {
    m_status = RoomStatus::OCCUPIED;
    m_currentGuest = guestName;
    m_bookedNights = nights;
    m_checkInDate = date;
}

void Room::checkOut() {
    m_status = RoomStatus::AVAILABLE;
    m_housekeepingStatus = HousekeepingStatus::CLEANING; // Mark for cleaning upon checkout
    m_currentGuest = "";
    m_bookedNights = 0;
    m_checkInDate = "";
}

std::string Room::roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::STANDARD: return "STANDARD";
        case RoomType::DELUXE:   return "DELUXE";
        case RoomType::VIP:      return "VIP";
        default:                 return "STANDARD";
    }
}

RoomType Room::stringToRoomType(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "DELUXE") return RoomType::DELUXE;
    if (s == "VIP") return RoomType::VIP;
    return RoomType::STANDARD;
}

std::string Room::bedTypeToString(BedType type) {
    switch (type) {
        case BedType::SINGLE: return "SINGLE";
        case BedType::DOUBLE: return "DOUBLE";
        case BedType::KING:   return "KING";
        default:              return "SINGLE";
    }
}

BedType Room::stringToBedType(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "DOUBLE") return BedType::DOUBLE;
    if (s == "KING") return BedType::KING;
    return BedType::SINGLE;
}

std::string Room::roomStatusToString(RoomStatus status) {
    switch (status) {
        case RoomStatus::AVAILABLE:   return "AVAILABLE";
        case RoomStatus::OCCUPIED:    return "OCCUPIED";
        case RoomStatus::MAINTENANCE: return "MAINTENANCE";
        default:                      return "AVAILABLE";
    }
}

RoomStatus Room::stringToRoomStatus(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "OCCUPIED") return RoomStatus::OCCUPIED;
    if (s == "MAINTENANCE") return RoomStatus::MAINTENANCE;
    return RoomStatus::AVAILABLE;
}

std::string Room::housekeepingStatusToString(HousekeepingStatus status) {
    switch (status) {
        case HousekeepingStatus::READY:            return "READY";
        case HousekeepingStatus::CLEANING:         return "CLEANING";
        case HousekeepingStatus::NEEDS_INSPECTION: return "NEEDS_INSPECTION";
        default:                                   return "READY";
    }
}

HousekeepingStatus Room::stringToHousekeepingStatus(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "CLEANING") return HousekeepingStatus::CLEANING;
    if (s == "NEEDS_INSPECTION") return HousekeepingStatus::NEEDS_INSPECTION;
    return HousekeepingStatus::READY;
}

std::string Room::toCsvRow() const {
    std::ostringstream ss;
    ss << m_roomNumber << ","
       << m_floor << ","
       << roomTypeToString(m_roomType) << ","
       << bedTypeToString(m_bedType) << ","
       << m_capacity << ","
       << std::fixed << std::setprecision(2) << m_pricePerNight << ","
       << m_amenities << ","
       << roomStatusToString(m_status) << ","
       << housekeepingStatusToString(m_housekeepingStatus) << ","
       << m_currentGuest << ","
       << m_bookedNights << ","
       << m_checkInDate;
    return ss.str();
}

Room Room::fromCsvRow(const std::string& row) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(row);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 9) {
        return Room();
    }

    int roomNum = std::stoi(tokens[0]);
    int floor = std::stoi(tokens[1]);
    RoomType rType = stringToRoomType(tokens[2]);
    BedType bType = stringToBedType(tokens[3]);
    int cap = std::stoi(tokens[4]);
    double price = std::stod(tokens[5]);
    std::string amenities = tokens[6];
    RoomStatus status = stringToRoomStatus(tokens[7]);
    HousekeepingStatus hkStatus = stringToHousekeepingStatus(tokens[8]);
    std::string guest = tokens.size() > 9 ? tokens[9] : "";
    int nights = (tokens.size() > 10 && !tokens[10].empty()) ? std::stoi(tokens[10]) : 0;
    std::string date = tokens.size() > 11 ? tokens[11] : "";

    return Room(roomNum, floor, rType, bType, cap, price, amenities, status, hkStatus, guest, nights, date);
}
