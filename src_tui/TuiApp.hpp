#ifndef TUI_APP_HPP
#define TUI_APP_HPP

#include "HotelManager.hpp"
#include <string>

class TuiApp {
private:
    HotelManager m_hotel;
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
    void adminAddRoom();
    void adminEditRoom();
    void adminDeleteRoom();
    void adminProcessCheckout();
    void adminHousekeepingControl();
    void adminViewTransactions();

    // Shared Views
    void displayFloorMatrix();
    void displayRoomsTable(const DynamicArray<Room>& rooms, const std::string& tableTitle = "Hotel Rooms");

public:
    TuiApp();
    void run();
};

#endif // TUI_APP_HPP
