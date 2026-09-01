#include "TuiApp.hpp"
#include <iostream>

int main() {
    try {
        TuiApp app;
        app.run();
    } catch (const std::exception& ex) {
        std::cerr << "\n[Fatal Error]: " << ex.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n[Fatal Error]: Unknown error occurred.\n";
        return 1;
    }
    return 0;
}
