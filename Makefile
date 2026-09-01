# Makefile — HilbertGrandHotel

CC := gcc
CXX := g++
CFLAGS := -O2 -Iinclude -Ivendor
CXXFLAGS := -std=c++17 -O2 -pthread -Iinclude -Ivendor
BUILD_DIR := build

OBJS_COMMON := $(BUILD_DIR)/miniz.o \
               $(BUILD_DIR)/utils.o \
               $(BUILD_DIR)/hotel.o \
               $(BUILD_DIR)/reservation.o \
               $(BUILD_DIR)/user.o

OBJS_SERVER := $(OBJS_COMMON) $(BUILD_DIR)/main.o
OBJS_TUI    := $(OBJS_COMMON) $(BUILD_DIR)/console_utils.o $(BUILD_DIR)/tui.o $(BUILD_DIR)/main_tui.o

TARGET_SERVER := $(BUILD_DIR)/server
TARGET_TUI    := $(BUILD_DIR)/tui

.PHONY: all server tui run-server run-tui clean help

all: server tui

server: $(TARGET_SERVER)
tui: $(TARGET_TUI)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/miniz.o: vendor/miniz.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_SERVER): $(OBJS_SERVER)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built Web Server -> $@"

$(TARGET_TUI): $(OBJS_TUI)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built Terminal TUI -> $@"

run-server: server
	@./$(TARGET_SERVER)

run-tui: tui
	@./$(TARGET_TUI)

clean:
	@rm -rf $(BUILD_DIR)/*.o $(TARGET_SERVER) $(TARGET_TUI)
	@echo "Cleaned build artifacts."

help:
	@echo "Available commands:"
	@echo "  make all         - Build both Web Server and Terminal TUI"
	@echo "  make server      - Build Web Server only"
	@echo "  make tui         - Build Terminal TUI only"
	@echo "  make run-server  - Build and launch Web Server"
	@echo "  make run-tui     - Build and launch Terminal TUI"
	@echo "  make clean       - Remove compiled binaries and objects"
