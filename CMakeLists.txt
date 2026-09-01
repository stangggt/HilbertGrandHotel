cmake_minimum_required(VERSION 3.16)
project(HotelBookingSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(core src_tui)

# Core library
set(CORE_SOURCES
    core/Room.cpp
    core/User.cpp
    core/Transaction.cpp
    core/CsvDatabase.cpp
    core/HotelManager.cpp
)

set(CORE_HEADERS
    core/DynamicArray.hpp
    core/Algorithms.hpp
    core/Room.hpp
    core/User.hpp
    core/Transaction.hpp
    core/CsvDatabase.hpp
    core/HotelManager.hpp
)

add_library(hotel_core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

# Unit Tests Executable
add_executable(hotel_tests tests/test_core.cpp)
target_link_libraries(hotel_tests PRIVATE hotel_core)

# TUI Executable
set(TUI_SOURCES
    src_tui/ConsoleUtils.cpp
    src_tui/TuiApp.cpp
    src_tui/main_tui.cpp
)

add_executable(hotel_tui ${TUI_SOURCES})
target_link_libraries(hotel_tui PRIVATE hotel_core)
