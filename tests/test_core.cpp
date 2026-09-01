#include "DynamicArray.hpp"
#include "Algorithms.hpp"
#include "Room.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "CsvDatabase.hpp"
#include "HotelManager.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

void testDynamicArray() {
    std::cout << "[TEST] Running DynamicArray tests...\n";
    DynamicArray<int> arr;
    assert(arr.size() == 0);
    assert(arr.empty());

    for (int i = 1; i <= 20; ++i) {
        arr.push_back(i * 10);
    }
    assert(arr.size() == 20);
    assert(arr[0] == 10);
    assert(arr[19] == 200);

    // Insert at index
    arr.insert_at(5, 999);
    assert(arr.size() == 21);
    assert(arr[5] == 999);
    assert(arr[6] == 60);

    // Remove at index
    arr.remove_at(5);
    assert(arr.size() == 20);
    assert(arr[5] == 60);

    // Copy Constructor & Assignment
    DynamicArray<int> copyArr = arr;
    assert(copyArr.size() == arr.size());
    assert(copyArr[0] == arr[0]);

    // Move
    DynamicArray<int> movedArr = std::move(copyArr);
    assert(movedArr.size() == 20);
    assert(copyArr.size() == 0);

    std::cout << "  -> DynamicArray tests PASSED!\n";
}

void testAlgorithms() {
    std::cout << "[TEST] Running Algorithms tests (QuickSort, InsertionSort, BinarySearch)...\n";
    DynamicArray<int> arr = {45, 12, 89, 23, 7, 64, 30};

    Algorithms::quickSort(arr);
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        assert(arr[i] <= arr[i + 1]);
    }
    assert(arr[0] == 7);
    assert(arr[arr.size() - 1] == 89);

    // Binary search
    int idx = Algorithms::binarySearch(arr, 23, [](int x) { return x; });
    assert(idx >= 0);
    assert(arr[idx] == 23);

    int notFound = Algorithms::binarySearch(arr, 999, [](int x) { return x; });
    assert(notFound == -1);

    // InsertionSort
    DynamicArray<int> arr2 = {50, 20, 10, 40, 30};
    Algorithms::insertionSort(arr2);
    assert(arr2[0] == 10);
    assert(arr2[4] == 50);

    std::cout << "  -> Algorithms tests PASSED!\n";
}

void testRoomCsvSerialization() {
    std::cout << "[TEST] Running Room CSV Serialization tests...\n";
    Room r(204, 2, RoomType::DELUXE, BedType::KING, 2, 95.0, "TV;AC;WiFi;Balcony;Breakfast",
           RoomStatus::AVAILABLE, HousekeepingStatus::READY);

    std::string csvRow = r.toCsvRow();
    Room parsed = Room::fromCsvRow(csvRow);

    assert(parsed.getRoomNumber() == 204);
    assert(parsed.getFloor() == 2);
    assert(parsed.getRoomType() == RoomType::DELUXE);
    assert(parsed.getBedType() == BedType::KING);
    assert(parsed.getCapacity() == 2);
    assert(std::abs(parsed.getPricePerNight() - 95.0) < 0.001);
    assert(parsed.getStatus() == RoomStatus::AVAILABLE);
    assert(parsed.getHousekeepingStatus() == HousekeepingStatus::READY);

    std::cout << "  -> Room CSV tests PASSED!\n";
}

void testHotelManagerWorkflow() {
    std::cout << "[TEST] Running HotelManager workflow (CRUD, Booking, Checkout, Bill)...\n";
    HotelManager hm;
    hm.loadDatabase("data/rooms.csv", "data/users.csv", "data/transactions.csv");

    assert(hm.getTotalRoomsCount() >= 20);

    // Filter available rooms
    DynamicArray<Room> avail = hm.getAvailableRooms();
    assert(avail.size() > 0);

    // Search room
    Room* r101 = hm.findRoomByNumber(101);
    assert(r101 != nullptr);
    assert(r101->getRoomNumber() == 101);

    // Ensure room 101 is in available/ready state for reproducible testing
    r101->setStatus(RoomStatus::AVAILABLE);
    r101->setHousekeepingStatus(HousekeepingStatus::READY);
    r101->setCurrentGuest("");
    r101->setBookedNights(0);

    // Check-in
    std::string txnId;
    double total = 0.0;
    double expectedTotal = r101->getPricePerNight() * 2;
    bool booked = hm.checkIn(101, "john_doe", 2, "2026-09-01", &txnId, &total);
    assert(booked);
    assert(!txnId.empty());
    assert(std::abs(total - expectedTotal) < 0.001);
    assert(r101->getStatus() == RoomStatus::OCCUPIED);
    assert(r101->getCurrentGuest() == "john_doe");

    // Check-out
    double bill = 0.0;
    bool checkedOut = hm.checkOut(101, &bill);
    assert(checkedOut);
    assert(std::abs(bill - expectedTotal) < 0.001);
    assert(r101->getStatus() == RoomStatus::AVAILABLE);
    assert(r101->getHousekeepingStatus() == HousekeepingStatus::CLEANING);

    // Housekeeping sets ready
    hm.setHousekeepingStatus(101, HousekeepingStatus::READY);
    assert(r101->getHousekeepingStatus() == HousekeepingStatus::READY);

    // User authentication
    bool authSuccess = hm.login("admin", "admin123");
    assert(authSuccess);
    assert(hm.getCurrentUser().isAdmin());

    bool authFail = hm.login("admin", "wrong_password");
    assert(!authFail);

    std::cout << "  -> HotelManager workflow tests PASSED!\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << " Hotel System Core Unit Test Suite      \n";
    std::cout << "========================================\n";

    testDynamicArray();
    testAlgorithms();
    testRoomCsvSerialization();
    testHotelManagerWorkflow();

    std::cout << "========================================\n";
    std::cout << " ALL TESTS COMPLETED SUCCESSFULLY! (100%)\n";
    std::cout << "========================================\n";
    return 0;
}
