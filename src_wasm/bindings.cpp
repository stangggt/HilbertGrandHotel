#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#endif

#include "HotelManager.hpp"
#include "Room.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include <sstream>
#include <string>

// JSON Serialization Helpers for JS Bridge
static std::string roomToJson(const Room& r) {
    std::ostringstream ss;
    ss << "{"
       << "\"roomNumber\":" << r.getRoomNumber() << ","
       << "\"floor\":" << r.getFloor() << ","
       << "\"roomType\":\"" << Room::roomTypeToString(r.getRoomType()) << "\","
       << "\"bedType\":\"" << Room::bedTypeToString(r.getBedType()) << "\","
       << "\"capacity\":" << r.getCapacity() << ","
       << "\"pricePerNight\":" << r.getPricePerNight() << ","
       << "\"amenities\":\"" << r.getAmenities() << "\","
       << "\"status\":\"" << Room::roomStatusToString(r.getStatus()) << "\","
       << "\"housekeepingStatus\":\"" << Room::housekeepingStatusToString(r.getHousekeepingStatus()) << "\","
       << "\"currentGuest\":\"" << r.getCurrentGuest() << "\","
       << "\"bookedNights\":" << r.getBookedNights() << ","
       << "\"checkInDate\":\"" << r.getCheckInDate() << "\""
       << "}";
    return ss.str();
}

static std::string roomListToJson(const DynamicArray<Room>& list) {
    std::ostringstream ss;
    ss << "[";
    for (size_t i = 0; i < list.size(); ++i) {
        ss << roomToJson(list[i]);
        if (i + 1 < list.size()) ss << ",";
    }
    ss << "]";
    return ss.str();
}

class WasmHotelEngine {
private:
    HotelManager m_hotel;

public:
    WasmHotelEngine() {
        m_hotel.loadDatabase("data/rooms.csv", "data/users.csv", "data/transactions.csv");
    }

    std::string getAllRoomsJson() {
        return roomListToJson(m_hotel.getAllRooms());
    }

    std::string getAvailableRoomsJson() {
        return roomListToJson(m_hotel.getAvailableRooms());
    }

    std::string getRoomsByFloorJson(int floor) {
        return roomListToJson(m_hotel.getRoomsByFloor(floor));
    }

    std::string getSortedByPriceJson(bool ascending) {
        return roomListToJson(m_hotel.getSortedRoomsByPrice(ascending));
    }

    bool checkInGuest(int roomNumber, const std::string& guestName, int nights, const std::string& date) {
        return m_hotel.checkIn(roomNumber, guestName, nights, date);
    }

    bool checkOutGuest(int roomNumber) {
        return m_hotel.checkOut(roomNumber);
    }

    bool setHousekeeping(int roomNumber, const std::string& statusStr) {
        HousekeepingStatus st = Room::stringToHousekeepingStatus(statusStr);
        return m_hotel.setHousekeepingStatus(roomNumber, st);
    }

    double getTotalRevenue() {
        return m_hotel.calculateTotalRevenue();
    }

    double getOccupancyRate() {
        return m_hotel.calculateOccupancyRate();
    }

    int getTotalRooms() { return m_hotel.getTotalRoomsCount(); }
    int getOccupiedRooms() { return m_hotel.getOccupiedRoomsCount(); }
    int getAvailableRooms() { return m_hotel.getAvailableRoomsCount(); }

    void loadCsvData(const std::string& roomsCsv) {
        // Parse CSV string directly into rooms
        std::istringstream stream(roomsCsv);
        std::string line;
        bool first = true;
        DynamicArray<Room> loaded;

        while (std::getline(stream, line)) {
            if (first) { first = false; continue; }
            if (line.empty() || line == "\r") continue;
            Room r = Room::fromCsvRow(line);
            if (r.getRoomNumber() > 0) {
                m_hotel.addRoom(r);
            }
        }
    }
};

#ifdef __EMSCRIPTEN__
using namespace emscripten;

EMSCRIPTEN_BINDINGS(hotel_module) {
    class_<WasmHotelEngine>("HotelEngine")
        .constructor<>()
        .function("getAllRoomsJson", &WasmHotelEngine::getAllRoomsJson)
        .function("getAvailableRoomsJson", &WasmHotelEngine::getAvailableRoomsJson)
        .function("getRoomsByFloorJson", &WasmHotelEngine::getRoomsByFloorJson)
        .function("getSortedByPriceJson", &WasmHotelEngine::getSortedByPriceJson)
        .function("checkInGuest", &WasmHotelEngine::checkInGuest)
        .function("checkOutGuest", &WasmHotelEngine::checkOutGuest)
        .function("setHousekeeping", &WasmHotelEngine::setHousekeeping)
        .function("getTotalRevenue", &WasmHotelEngine::getTotalRevenue)
        .function("getOccupancyRate", &WasmHotelEngine::getOccupancyRate)
        .function("getTotalRooms", &WasmHotelEngine::getTotalRooms)
        .function("getOccupiedRooms", &WasmHotelEngine::getOccupiedRooms)
        .function("getAvailableRooms", &WasmHotelEngine::getAvailableRooms)
        .function("loadCsvData", &WasmHotelEngine::loadCsvData);
}
#endif
