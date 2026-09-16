# Makefile — HilbertGrandHotel

CC := gcc
CXX := g++
CFLAGS := -O2 -Iinclude -Ivendor
CXXFLAGS := -std=c++17 -O2 -pthread -Iinclude -Ivendor
BUILD_DIR := build

OBJS_COMMON := $(BUILD_DIR)/miniz.o \
               $(BUILD_DIR)/sha256.o \
               $(BUILD_DIR)/utils.o \
               $(BUILD_DIR)/hotel.o \
               $(BUILD_DIR)/reservation.o \
               $(BUILD_DIR)/user.o

OBJS_SERVER := $(OBJS_COMMON) $(BUILD_DIR)/main.o
OBJS_TUI    := $(OBJS_COMMON) $(BUILD_DIR)/console_utils.o $(BUILD_DIR)/tui.o $(BUILD_DIR)/main_tui.o
OBJS_TEST   := $(OBJS_COMMON) $(BUILD_DIR)/console_utils.o $(BUILD_DIR)/test_suite.o

TARGET_SERVER    := $(BUILD_DIR)/server
TARGET_TUI       := $(BUILD_DIR)/tui
TARGET_TEST      := $(BUILD_DIR)/test_suite
TARGET_BENCHMARK := $(BUILD_DIR)/benchmark_dsa

.PHONY: all server tui test benchmark run-server run-demo run-tui clean help

all: server tui

server: $(TARGET_SERVER)
tui: $(TARGET_TUI)
test: $(TARGET_TEST)
	@./$(TARGET_TEST)

benchmark: $(TARGET_BENCHMARK)
	@./$(TARGET_BENCHMARK)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/miniz.o: vendor/miniz.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_suite.o: test/test_suite.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/benchmark_dsa.o: test/benchmark_dsa.cpp include/algorithms.h include/dynamic_array.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_SERVER): $(OBJS_SERVER)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built Web Server -> $@"

$(TARGET_TUI): $(OBJS_TUI)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built Terminal TUI -> $@"

$(TARGET_TEST): $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built Automated Test Suite -> $@"

$(TARGET_BENCHMARK): $(BUILD_DIR)/benchmark_dsa.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[OK] Built DSA Benchmark Suite -> $@"

ARGS ?=

run-server: server
	@./$(TARGET_SERVER) $(ARGS)

run-demo: server
	@./$(TARGET_SERVER) -f demo

run-tui: tui
	@./$(TARGET_TUI)

clean:
	@rm -rf $(BUILD_DIR)/*.o $(TARGET_SERVER) $(TARGET_TUI) $(TARGET_TEST) $(TARGET_BENCHMARK)
	@echo "Cleaned build artifacts."

help:
	@echo "Available commands:"
	@echo "  make all         - Build both Web Server and Terminal TUI"
	@echo "  make server      - Build Web Server only"
	@echo "  make tui         - Build Terminal TUI only"
	@echo "  make test        - Build and run automated unit & regression tests"
	@echo "  make benchmark   - Build and run Academic DSA Benchmark Suite (100k records)"
	@echo "  make run-server  - Build and launch Web Server (pass ARGS='-f demo' for demo mode)"
	@echo "  make run-demo    - Build and launch Web Server with Demo Role Switcher"
	@echo "  make run-tui     - Build and launch Terminal TUI"
	@echo "  make clean       - Remove compiled binaries and objects"
