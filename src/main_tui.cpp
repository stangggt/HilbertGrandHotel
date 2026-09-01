#include "../include/tui.h"
#include <iostream>

int main() {
    try {
        TuiApp app;
        app.run();
    } catch (const std::exception& ex) {
        std::cerr << "\n[Fatal Error]: " << ex.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n[Fatal Error]: เกิดข้อผิดพลาดที่ไม่ทราบสาเหตุ\n";
        return 1;
    }
    return 0;
}
