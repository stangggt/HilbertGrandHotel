#include "TuiApp.hpp"
#include "ConsoleUtils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace ConsoleUtils;

TuiApp::TuiApp() : m_running(true) {
    m_hotel.loadDatabase("data/rooms.csv", "data/users.csv", "data/transactions.csv");
}

void TuiApp::run() {
    while (m_running) {
        if (!m_hotel.isLoggedIn()) {
            handleAuthFlow();
        } else {
            if (m_hotel.getCurrentUser().isAdmin() || m_hotel.getCurrentUser().isStaff()) {
                showStaffAdminMenu();
            } else {
                showGuestMenu();
            }
        }
    }

    clearScreen();
    std::cout << Color::BOLD_GREEN << "\n  Thank you for using Grand Hotel Management System! Goodbye.\n\n" << Color::RESET;
}

void TuiApp::handleAuthFlow() {
    clearScreen();
    printHeader("GRAND HORIZON HOTEL & RESORT", "C++ & CSV Database System");

    std::cout << "\n"
              << Color::BOLD_WHITE << "  Welcome to the Hotel Room Booking System\n" << Color::RESET
              << Color::DIM << "  Powered by custom C++ Dynamic Arrays & File-based CSV DB\n\n" << Color::RESET;

    std::vector<std::string> options = {
        "1. Sign In (Existing User / Staff / Admin)",
        "2. Sign Up (New Guest Account)",
        "3. Quick Browse Available Rooms (Guest Preview)",
        "4. Exit Application"
    };

    printBox("Authentication Menu", options, 55);

    int choice = readInt("\nSelect an option [1-4]: ", 1, 4);

    switch (choice) {
        case 1: showLoginScreen(); break;
        case 2: showRegisterScreen(); break;
        case 3:
            clearScreen();
            displayRoomsTable(m_hotel.getAvailableRooms(), "Available Rooms Preview");
            pause();
            break;
        case 4: m_running = false; break;
    }
}

void TuiApp::showLoginScreen() {
    clearScreen();
    printHeader("USER AUTHENTICATION", "Sign In");

    std::cout << Color::DIM << "\n  (Demo accounts: 'admin'/'admin123', 'staff'/'staff123', 'john_doe'/'pass123')\n\n" << Color::RESET;

    std::string username = readLine("  Username: ");
    if (username.empty()) return;
    std::string password = readLine("  Password: ");

    if (m_hotel.login(username, password)) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] Login successful! Welcome, "
                  << m_hotel.getCurrentUser().getFullName() << " ("
                  << User::roleToString(m_hotel.getCurrentUser().getRole()) << ")\n" << Color::RESET;
        pause();
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] Invalid username or password.\n" << Color::RESET;
        pause();
    }
}

void TuiApp::showRegisterScreen() {
    clearScreen();
    printHeader("NEW GUEST REGISTRATION", "Create Account");

    std::string username = readLine("  Choose Username: ");
    if (username.empty()) return;

    if (m_hotel.userExists(username)) {
        std::cout << Color::BOLD_RED << "\n  [✗] Username already taken. Please choose another.\n" << Color::RESET;
        pause();
        return;
    }

    std::string password = readLine("  Choose Password: ");
    std::string fullName = readLine("  Full Name: ");
    std::string phone = readLine("  Phone Number: ");
    std::string email = readLine("  Email Address: ");

    if (m_hotel.registerUser(username, password, UserRole::GUEST, fullName, phone, email)) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] Account created successfully! Please sign in.\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] Failed to register user.\n" << Color::RESET;
    }
    pause();
}

void TuiApp::showGuestMenu() {
    clearScreen();
    std::string subtitle = "Guest: " + m_hotel.getCurrentUser().getFullName();
    printHeader("GUEST PORTAL", subtitle);

    std::vector<std::string> menu = {
        "1. Search & Filter Hotel Rooms",
        "2. View Interactive Floor Plan Matrix",
        "3. Book a Room (Check-in)",
        "4. View My Current Bookings & History",
        "5. Sign Out"
    };

    printBox("Guest Services", menu, 55);

    int choice = readInt("\nSelect an action [1-5]: ", 1, 5);

    switch (choice) {
        case 1: guestBrowseRooms(); break;
        case 2:
            clearScreen();
            displayFloorMatrix();
            pause();
            break;
        case 3: guestBookRoom(); break;
        case 4: guestViewMyBookings(); break;
        case 5:
            m_hotel.logout();
            std::cout << Color::YELLOW << "\n  [i] You have been logged out.\n" << Color::RESET;
            pause();
            break;
    }
}

void TuiApp::showStaffAdminMenu() {
    clearScreen();
    std::string roleStr = User::roleToString(m_hotel.getCurrentUser().getRole());
    std::string subtitle = roleStr + " Console: " + m_hotel.getCurrentUser().getFullName();
    printHeader("MANAGEMENT & OPERATIONS PORTAL", subtitle);

    // Quick Stats Bar
    std::cout << Color::CYAN << "  ✦ Quick Stats: "
              << Color::BOLD_WHITE << "Total Rooms: " << m_hotel.getTotalRoomsCount() << " | "
              << Color::BOLD_GREEN << "Available: " << m_hotel.getAvailableRoomsCount() << " | "
              << Color::BOLD_YELLOW << "Occupied: " << m_hotel.getOccupiedRoomsCount() << " | "
              << Color::BOLD_RED << "Maintenance: " << m_hotel.getMaintenanceRoomsCount() << " | "
              << Color::BOLD_CYAN << "Occupancy: " << std::fixed << std::setprecision(1) << m_hotel.calculateOccupancyRate() << "%\n"
              << Color::RESET;

    std::vector<std::string> menu = {
        "1. Hotel Performance & Revenue Dashboard",
        "2. Room Management (Add / Edit / Delete)",
        "3. Process Guest Check-Out & Settle Bill",
        "4. Housekeeping & Room Cleanliness Control",
        "5. Interactive Floor Matrix Overview",
        "6. Financial Transactions & Booking Audit Log",
        "7. Sign Out"
    };

    printBox("Management Actions", menu, 60);

    int choice = readInt("\nSelect an action [1-7]: ", 1, 7);

    switch (choice) {
        case 1: adminShowDashboard(); break;
        case 2: adminManageRooms(); break;
        case 3: adminProcessCheckout(); break;
        case 4: adminHousekeepingControl(); break;
        case 5:
            clearScreen();
            displayFloorMatrix();
            pause();
            break;
        case 6: adminViewTransactions(); break;
        case 7:
            m_hotel.logout();
            std::cout << Color::YELLOW << "\n  [i] You have been logged out.\n" << Color::RESET;
            pause();
            break;
    }
}

void TuiApp::guestBrowseRooms() {
    clearScreen();
    printHeader("SEARCH & FILTER ROOMS", "Browse Catalog");

    std::cout << "  Filter Options:\n"
              << "  1. Show All Available Rooms\n"
              << "  2. Filter by Room Type (Standard, Deluxe, VIP)\n"
              << "  3. Sort by Price (Low to High)\n"
              << "  4. Sort by Price (High to Low)\n"
              << "  5. Search Specific Room Number\n"
              << "  6. Back to Guest Menu\n\n";

    int filterOpt = readInt("Select filter mode [1-6]: ", 1, 6);

    switch (filterOpt) {
        case 1: {
            clearScreen();
            displayRoomsTable(m_hotel.getAvailableRooms(), "Available Rooms");
            pause();
            break;
        }
        case 2: {
            std::cout << "\n  Select Room Type:\n"
                      << "  1. Standard\n  2. Deluxe\n  3. VIP\n";
            int tChoice = readInt("Type [1-3]: ", 1, 3);
            RoomType rt = (tChoice == 1) ? RoomType::STANDARD : (tChoice == 2) ? RoomType::DELUXE : RoomType::VIP;
            clearScreen();
            DynamicArray<Room> filtered = m_hotel.filterRooms(true, rt, true);
            displayRoomsTable(filtered, Room::roomTypeToString(rt) + " Rooms (Available)");
            pause();
            break;
        }
        case 3: {
            clearScreen();
            displayRoomsTable(m_hotel.getSortedRoomsByPrice(true), "Rooms Sorted by Price (Ascending)");
            pause();
            break;
        }
        case 4: {
            clearScreen();
            displayRoomsTable(m_hotel.getSortedRoomsByPrice(false), "Rooms Sorted by Price (Descending)");
            pause();
            break;
        }
        case 5: {
            int rNum = readInt("\nEnter Room Number to search (e.g. 101, 204): ", 100, 999);
            Room* r = m_hotel.findRoomByNumber(rNum);
            clearScreen();
            if (r) {
                DynamicArray<Room> single;
                single.push_back(*r);
                displayRoomsTable(single, "Room Search Result");
            } else {
                std::cout << Color::BOLD_RED << "\n  [✗] Room " << rNum << " was not found in the hotel system.\n" << Color::RESET;
            }
            pause();
            break;
        }
        case 6: return;
    }
}

void TuiApp::guestBookRoom() {
    clearScreen();
    printHeader("ROOM RESERVATION & CHECK-IN", "Book a Room");

    displayRoomsTable(m_hotel.getAvailableRooms(), "Available Rooms Ready for Booking");

    int roomNum = readInt("\nEnter Room Number you wish to book (0 to cancel): ", 0, 999);
    if (roomNum == 0) return;

    Room* room = m_hotel.findRoomByNumber(roomNum);
    if (!room) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " does not exist.\n" << Color::RESET;
        pause();
        return;
    }

    if (!room->isAvailableForBooking()) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " is currently not available for booking.\n" << Color::RESET;
        pause();
        return;
    }

    int nights = readInt("Enter number of nights to stay: ", 1, 60);

    double totalAmount = room->calculateTotalPrice(nights);

    // Price Breakdown
    std::cout << "\n" << Color::CYAN << "┌────────────────────────────────────────┐\n"
              << "│            BOOKING SUMMARY             │\n"
              << "├────────────────────────────────────────┤\n"
              << "│ Room Number : " << std::left << std::setw(24) << room->getRoomNumber() << " │\n"
              << "│ Room Type   : " << std::left << std::setw(24) << Room::roomTypeToString(room->getRoomType()) << " │\n"
              << "│ Nightly Rate: $" << std::fixed << std::setprecision(2) << std::left << std::setw(23) << room->getPricePerNight() << " │\n"
              << "│ Stay Length : " << std::left << std::setw(2) << nights << " night(s)" << std::setw(14) << " " << " │\n"
              << "│ Total Cost  : $" << std::fixed << std::setprecision(2) << std::left << std::setw(23) << totalAmount << " │\n"
              << "└────────────────────────────────────────┘\n" << Color::RESET;

    bool confirm = readBool("\nConfirm and proceed with booking?");
    if (!confirm) {
        std::cout << Color::YELLOW << "\n  [i] Booking cancelled.\n" << Color::RESET;
        pause();
        return;
    }

    std::string txnId;
    double finalTotal = 0.0;
    if (m_hotel.checkIn(roomNum, m_hotel.getCurrentUser().getUsername(), nights, "", &txnId, &finalTotal)) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] Booking Confirmed! Transaction ID: " << txnId << "\n"
                  << "  Enjoy your stay in Room " << roomNum << "!\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] An error occurred while booking the room.\n" << Color::RESET;
    }
    pause();
}

void TuiApp::guestViewMyBookings() {
    clearScreen();
    printHeader("MY ACTIVE BOOKINGS", m_hotel.getCurrentUser().getFullName());

    DynamicArray<Room> myRooms = m_hotel.getRoomsBookedByGuest(m_hotel.getCurrentUser().getUsername());
    DynamicArray<Transaction> myTxns = m_hotel.getGuestTransactions(m_hotel.getCurrentUser().getUsername());

    if (myRooms.empty() && myTxns.empty()) {
        std::cout << Color::YELLOW << "\n  You currently have no active room reservations or past transactions.\n" << Color::RESET;
    } else {
        if (!myRooms.empty()) {
            displayRoomsTable(myRooms, "Currently Booked Rooms");
        }

        std::cout << "\n";
        std::vector<std::string> headers = {"Txn ID", "Room", "Nights", "Rate/Night", "Total ($)", "Date/Time", "Status"};
        std::vector<int> widths = {10, 6, 8, 12, 11, 20, 11};
        std::vector<std::vector<std::string>> rows;

        for (size_t i = 0; i < myTxns.size(); ++i) {
            std::ostringstream ssRate, ssTot;
            ssRate << "$" << std::fixed << std::setprecision(2) << myTxns[i].getRatePerNight();
            ssTot << "$" << std::fixed << std::setprecision(2) << myTxns[i].getTotalAmount();

            rows.push_back({
                myTxns[i].getTransactionId(),
                std::to_string(myTxns[i].getRoomNumber()),
                std::to_string(myTxns[i].getNights()),
                ssRate.str(),
                ssTot.str(),
                myTxns[i].getTimestamp(),
                Transaction::statusToString(myTxns[i].getStatus())
            });
        }
        printTable(headers, widths, rows);
    }
    pause();
}

void TuiApp::adminShowDashboard() {
    clearScreen();
    printHeader("HOTEL ANALYTICS & REVENUE DASHBOARD", "Manager Overview");

    int totalRooms = m_hotel.getTotalRoomsCount();
    int occupied = m_hotel.getOccupiedRoomsCount();
    int available = m_hotel.getAvailableRoomsCount();
    int maintenance = m_hotel.getMaintenanceRoomsCount();
    int cleaning = m_hotel.getCleaningRoomsCount();
    double occupancyRate = m_hotel.calculateOccupancyRate();
    double totalRevenue = m_hotel.calculateTotalRevenue();

    std::cout << "\n"
              << Color::BOLD_WHITE << "  ┌────────────────────────────────────────────────────────────┐\n"
              << "  │                    KEY PERFORMANCE METRICS                 │\n"
              << "  ├───────────────────────────────┬────────────────────────────┤\n"
              << "  │ Total Hotel Rooms             │ " << std::setw(26) << std::left << totalRooms << " │\n"
              << "  │ Currently Occupied            │ " << Color::BOLD_YELLOW << std::setw(26) << std::left << occupied << Color::BOLD_WHITE << " │\n"
              << "  │ Available & Ready             │ " << Color::BOLD_GREEN << std::setw(26) << std::left << available << Color::BOLD_WHITE << " │\n"
              << "  │ Under Housekeeping / Cleaning │ " << Color::CYAN << std::setw(26) << std::left << cleaning << Color::BOLD_WHITE << " │\n"
              << "  │ Under Maintenance             │ " << Color::BOLD_RED << std::setw(26) << std::left << maintenance << Color::BOLD_WHITE << " │\n"
              << "  ├───────────────────────────────┼────────────────────────────┤\n"
              << "  │ Hotel Occupancy Rate          │ " << Color::BOLD_CYAN << std::fixed << std::setprecision(1) << std::setw(25) << std::left << (std::to_string(occupancyRate).substr(0, 5) + " %") << Color::BOLD_WHITE << " │\n"
              << "  │ Cumulative Hotel Revenue      │ " << Color::BOLD_GREEN << "$" << std::fixed << std::setprecision(2) << std::setw(25) << std::left << totalRevenue << Color::BOLD_WHITE << " │\n"
              << "  └───────────────────────────────┴────────────────────────────┘\n"
              << Color::RESET;

    pause();
}

void TuiApp::adminManageRooms() {
    clearScreen();
    printHeader("ROOM MANAGEMENT (CRUD)", "Inventory Operations");

    std::cout << "  1. View All Rooms Inventory\n"
              << "  2. Add New Room [INSERT]\n"
              << "  3. Edit Room (Price, Type, Status) [UPDATE]\n"
              << "  4. Delete / Decommission Room [DELETE]\n"
              << "  5. Back to Management Menu\n\n";

    int choice = readInt("Select action [1-5]: ", 1, 5);

    switch (choice) {
        case 1:
            clearScreen();
            displayRoomsTable(m_hotel.getSortedRoomsByNumber(), "All Hotel Rooms");
            pause();
            break;
        case 2: adminAddRoom(); break;
        case 3: adminEditRoom(); break;
        case 4: adminDeleteRoom(); break;
        case 5: return;
    }
}

void TuiApp::adminAddRoom() {
    clearScreen();
    printHeader("ADD NEW HOTEL ROOM", "Insert into Array & CSV");

    int roomNum = readInt("  Enter Room Number (e.g. 109, 305): ", 100, 999);
    if (m_hotel.findRoomByNumber(roomNum) != nullptr) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " already exists!\n" << Color::RESET;
        pause();
        return;
    }

    int floor = roomNum / 100;
    std::cout << "  Floor automatically calculated: " << floor << "\n";

    std::cout << "\n  Select Room Type:\n  1. Standard\n  2. Deluxe\n  3. VIP\n";
    int typeOpt = readInt("  Type [1-3]: ", 1, 3);
    RoomType rType = (typeOpt == 1) ? RoomType::STANDARD : (typeOpt == 2) ? RoomType::DELUXE : RoomType::VIP;

    std::cout << "\n  Select Bed Type:\n  1. Single\n  2. Double\n  3. King\n";
    int bedOpt = readInt("  Bed [1-3]: ", 1, 3);
    BedType bType = (bedOpt == 1) ? BedType::SINGLE : (bedOpt == 2) ? BedType::DOUBLE : BedType::KING;

    int capacity = readInt("  Guest Capacity (1-10): ", 1, 10);
    double price = readDouble("  Price Per Night ($): ", 1.0, 5000.0);
    std::string amenities = readLine("  Amenities (semicolon-separated, e.g. TV;AC;WiFi;Breakfast): ");

    Room newRoom(roomNum, floor, rType, bType, capacity, price, amenities, RoomStatus::AVAILABLE, HousekeepingStatus::READY);

    if (m_hotel.addRoom(newRoom)) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] Room " << roomNum << " created and saved to CSV database successfully!\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] Failed to add room.\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminEditRoom() {
    clearScreen();
    printHeader("EDIT ROOM DETAILS", "Update Array & CSV");

    int roomNum = readInt("  Enter Room Number to edit: ", 100, 999);
    Room* room = m_hotel.findRoomByNumber(roomNum);

    if (!room) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " does not exist.\n" << Color::RESET;
        pause();
        return;
    }

    std::cout << "\n  Current Price: $" << room->getPricePerNight() << "\n";
    if (readBool("  Update price?")) {
        double newPrice = readDouble("  New Price Per Night ($): ", 1.0, 5000.0);
        room->setPricePerNight(newPrice);
    }

    std::cout << "\n  Current Status: " << Room::roomStatusToString(room->getStatus()) << "\n";
    if (readBool("  Update room status?")) {
        std::cout << "  1. AVAILABLE\n  2. OCCUPIED\n  3. MAINTENANCE\n";
        int stChoice = readInt("  Select status [1-3]: ", 1, 3);
        RoomStatus newStatus = (stChoice == 1) ? RoomStatus::AVAILABLE :
                               (stChoice == 2) ? RoomStatus::OCCUPIED : RoomStatus::MAINTENANCE;
        room->setStatus(newStatus);
    }

    m_hotel.updateRoom(*room);
    std::cout << Color::BOLD_GREEN << "\n  [✓] Room " << roomNum << " updated successfully!\n" << Color::RESET;
    pause();
}

void TuiApp::adminDeleteRoom() {
    clearScreen();
    printHeader("DELETE / DECOMMISSION ROOM", "Remove from Array & CSV");

    int roomNum = readInt("  Enter Room Number to permanently remove: ", 100, 999);
    Room* room = m_hotel.findRoomByNumber(roomNum);

    if (!room) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " not found.\n" << Color::RESET;
        pause();
        return;
    }

    if (room->getStatus() == RoomStatus::OCCUPIED) {
        std::cout << Color::BOLD_RED << "\n  [✗] Cannot delete room while occupied by guest: "
                  << room->getCurrentGuest() << ". Please check-out guest first.\n" << Color::RESET;
        pause();
        return;
    }

    bool confirm = readBool("  Are you sure you want to delete Room " + std::to_string(roomNum) + "?");
    if (confirm) {
        if (m_hotel.deleteRoom(roomNum)) {
            std::cout << Color::BOLD_GREEN << "\n  [✓] Room " << roomNum << " deleted from system and CSV!\n" << Color::RESET;
        } else {
            std::cout << Color::BOLD_RED << "\n  [✗] Failed to delete room.\n" << Color::RESET;
        }
    } else {
        std::cout << Color::YELLOW << "\n  [i] Deletion cancelled.\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminProcessCheckout() {
    clearScreen();
    printHeader("GUEST CHECK-OUT & BILL SETTLEMENT", "Front Desk");

    DynamicArray<Room> occupied = Algorithms::filter(m_hotel.getAllRooms(), [](const Room& r) {
        return r.getStatus() == RoomStatus::OCCUPIED;
    });

    if (occupied.empty()) {
        std::cout << Color::YELLOW << "\n  No rooms are currently occupied.\n" << Color::RESET;
        pause();
        return;
    }

    displayRoomsTable(occupied, "Currently Occupied Rooms");

    int roomNum = readInt("\nEnter Room Number for Check-Out (0 to cancel): ", 0, 999);
    if (roomNum == 0) return;

    Room* room = m_hotel.findRoomByNumber(roomNum);
    if (!room || room->getStatus() != RoomStatus::OCCUPIED) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " is not currently occupied.\n" << Color::RESET;
        pause();
        return;
    }

    double finalBill = 0.0;
    std::string guest = room->getCurrentGuest();
    int nights = room->getBookedNights();

    if (m_hotel.checkOut(roomNum, &finalBill)) {
        std::cout << "\n" << Color::BOLD_GREEN
                  << "┌────────────────────────────────────────┐\n"
                  << "│          CHECK-OUT SUCCESSFUL          │\n"
                  << "├────────────────────────────────────────┤\n"
                  << "│ Guest Name   : " << std::left << std::setw(23) << guest << " │\n"
                  << "│ Room Number  : " << std::left << std::setw(23) << roomNum << " │\n"
                  << "│ Total Nights : " << std::left << std::setw(23) << nights << " │\n"
                  << "│ Final Bill   : $" << std::fixed << std::setprecision(2) << std::left << std::setw(22) << finalBill << " │\n"
                  << "│ Status       : Set to CLEANING         │\n"
                  << "└────────────────────────────────────────┘\n"
                  << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "\n  [✗] Check-out failed.\n" << Color::RESET;
    }
    pause();
}

void TuiApp::adminHousekeepingControl() {
    clearScreen();
    printHeader("HOUSEKEEPING & ROOM CLEANLINESS", "Staff Operations");

    DynamicArray<Room> cleaningRooms = m_hotel.getRoomsNeedingCleaning();

    if (cleaningRooms.empty()) {
        std::cout << Color::BOLD_GREEN << "\n  [✓] All rooms are clean and READY for guests!\n" << Color::RESET;
    } else {
        displayRoomsTable(cleaningRooms, "Rooms Requiring Cleaning / Inspection");
    }

    std::cout << "\n  1. Mark a Room as CLEAN & READY\n"
              << "  2. Mark a Room as CLEANING / IN PROGRESS\n"
              << "  3. Mark a Room as NEEDS_INSPECTION\n"
              << "  4. Back to Menu\n\n";

    int choice = readInt("Select action [1-4]: ", 1, 4);
    if (choice == 4) return;

    int roomNum = readInt("Enter Room Number: ", 100, 999);
    Room* r = m_hotel.findRoomByNumber(roomNum);
    if (!r) {
        std::cout << Color::BOLD_RED << "\n  [✗] Room " << roomNum << " not found.\n" << Color::RESET;
        pause();
        return;
    }

    HousekeepingStatus hk = (choice == 1) ? HousekeepingStatus::READY :
                            (choice == 2) ? HousekeepingStatus::CLEANING : HousekeepingStatus::NEEDS_INSPECTION;

    m_hotel.setHousekeepingStatus(roomNum, hk);
    std::cout << Color::BOLD_GREEN << "\n  [✓] Room " << roomNum << " housekeeping status updated to "
              << Room::housekeepingStatusToString(hk) << "!\n" << Color::RESET;
    pause();
}

void TuiApp::adminViewTransactions() {
    clearScreen();
    printHeader("FINANCIAL AUDIT & TRANSACTION LOGS", "Ledger from CSV");

    DynamicArray<Transaction> txns = m_hotel.getAllTransactions();

    if (txns.empty()) {
        std::cout << Color::YELLOW << "\n  No transactions recorded in database.\n" << Color::RESET;
    } else {
        std::vector<std::string> headers = {"Txn ID", "Room", "Guest User", "Nights", "Rate/Night", "Total ($)", "Timestamp", "Status"};
        std::vector<int> widths = {10, 6, 12, 7, 11, 10, 20, 10};
        std::vector<std::vector<std::string>> rows;

        for (size_t i = 0; i < txns.size(); ++i) {
            std::ostringstream ssRate, ssTot;
            ssRate << "$" << std::fixed << std::setprecision(2) << txns[i].getRatePerNight();
            ssTot << "$" << std::fixed << std::setprecision(2) << txns[i].getTotalAmount();

            rows.push_back({
                txns[i].getTransactionId(),
                std::to_string(txns[i].getRoomNumber()),
                txns[i].getGuestUsername(),
                std::to_string(txns[i].getNights()),
                ssRate.str(),
                ssTot.str(),
                txns[i].getTimestamp(),
                Transaction::statusToString(txns[i].getStatus())
            });
        }
        printTable(headers, widths, rows);
    }
    pause();
}

void TuiApp::displayFloorMatrix() {
    printHeader("INTERACTIVE HOTEL FLOOR PLAN MATRIX", "Visual Status Map");

    std::cout << "  Legend: "
              << Color::BOLD_GREEN << "[ 101:AVL ]" << Color::RESET << " Available  "
              << Color::BOLD_YELLOW << "[ 102:OCC ]" << Color::RESET << " Occupied  "
              << Color::CYAN << "[ 104:CLN ]" << Color::RESET << " Cleaning  "
              << Color::BOLD_RED << "[ 107:MNT ]" << Color::RESET << " Maintenance\n\n";

    for (int floor = 3; floor >= 1; --floor) {
        DynamicArray<Room> floorRooms = m_hotel.getRoomsByFloor(floor);
        Algorithms::quickSort(floorRooms, [](const Room& a, const Room& b) {
            return a.getRoomNumber() < b.getRoomNumber();
        });

        std::cout << Color::BOLD_WHITE << "  Floor " << floor << ": " << Color::RESET;

        if (floorRooms.empty()) {
            std::cout << Color::DIM << "(No rooms configured on this floor)\n" << Color::RESET;
            continue;
        }

        for (size_t i = 0; i < floorRooms.size(); ++i) {
            const Room& r = floorRooms[i];
            std::string code = "AVL";
            std::string col = Color::BOLD_GREEN;

            if (r.getStatus() == RoomStatus::OCCUPIED) {
                code = "OCC";
                col = Color::BOLD_YELLOW;
            } else if (r.getStatus() == RoomStatus::MAINTENANCE) {
                code = "MNT";
                col = Color::BOLD_RED;
            } else if (r.getHousekeepingStatus() == HousekeepingStatus::CLEANING) {
                code = "CLN";
                col = Color::CYAN;
            }

            std::cout << col << "[" << r.getRoomNumber() << ":" << code << "] " << Color::RESET;
        }
        std::cout << "\n\n";
    }
}

void TuiApp::displayRoomsTable(const DynamicArray<Room>& rooms, const std::string& tableTitle) {
    std::cout << Color::BOLD_CYAN << "  ✦ " << tableTitle << " (" << rooms.size() << " rooms)\n" << Color::RESET;

    if (rooms.empty()) {
        std::cout << Color::YELLOW << "  No rooms match the criteria.\n\n" << Color::RESET;
        return;
    }

    std::vector<std::string> headers = {"Room", "Floor", "Type", "Bed", "Cap", "Price/Night", "Status", "Housekeeping", "Guest"};
    std::vector<int> widths = {6, 6, 9, 7, 4, 12, 12, 13, 12};
    std::vector<std::vector<std::string>> rows;

    for (size_t i = 0; i < rooms.size(); ++i) {
        const Room& r = rooms[i];
        std::ostringstream ssPrice;
        ssPrice << "$" << std::fixed << std::setprecision(2) << r.getPricePerNight();

        std::string statusStr = Room::roomStatusToString(r.getStatus());
        std::string hkStr = Room::housekeepingStatusToString(r.getHousekeepingStatus());
        std::string guest = r.getCurrentGuest().empty() ? "-" : r.getCurrentGuest();

        rows.push_back({
            std::to_string(r.getRoomNumber()),
            std::to_string(r.getFloor()),
            Room::roomTypeToString(r.getRoomType()),
            Room::bedTypeToString(r.getBedType()),
            std::to_string(r.getCapacity()),
            ssPrice.str(),
            statusStr,
            hkStr,
            guest
        });
    }

    printTable(headers, widths, rows);
    std::cout << "\n";
}
