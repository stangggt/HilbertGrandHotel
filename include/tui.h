#pragma once

#include "hotel.h"
#include "reservation.h"
#include "user.h"
#include <string>
#include <vector>

class TuiApp {
private:
    User* m_currentUser;
    bool m_running;

    // Navigation & Menus
    void handleAuthFlow();
    void showLoginScreen();
    void showRegisterScreen();

    void showGuestMenu();
    void showStaffAdminMenu();

    // Guest Actions
    void guestBrowseRooms();
    void guestBookRoom();
    void guestViewMyBookings();

    // Admin / Staff Actions
    void adminShowDashboard();
    void adminManageRooms();
    void adminWalkinBooking();
    void adminChangeStatus();
    void adminEditRoom();
    void adminReloadData();
    void adminViewUsers();

    // Shared Views
    void displayFloorMatrix();
    void displayRoomsTable(const std::vector<Room>& rooms, const std::string& tableTitle = "Hilbert Grand Hotel Rooms");

public:
    TuiApp();
    void run();
};
