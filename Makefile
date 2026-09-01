# Hotel Management System Makefile

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Icore -Isrc_tui
BUILD_DIR := build

.PHONY: all build run test clean wasm web help

all: build

build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && make -j$$(nproc)

run: build
	@./$(BUILD_DIR)/hotel_tui

test: build
	@./$(BUILD_DIR)/hotel_tests

web:
	@echo "============================================================"
	@echo " Starting Grand Horizon Hotel Web UI (Python Server)"
	@echo " Web Directory : web/"
	@echo " URL           : http://localhost:8000"
	@echo " Press Ctrl+C to stop the server"
	@echo "============================================================"
	@python3 -m http.server 8000 --directory web 2>/dev/null || (cd web && python3 -m http.server 8000)

wasm:
	@echo "Compiling WebAssembly module using emcc..."
	@if command -v emcc >/dev/null 2>&1; then \
		mkdir -p web/wasm; \
		emcc -std=c++17 -O3 \
			-Icore \
			core/Room.cpp \
			core/User.cpp \
			core/Transaction.cpp \
			core/CsvDatabase.cpp \
			core/HotelManager.cpp \
			src_wasm/bindings.cpp \
			-s WASM=1 \
			-s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
			-s ALLOW_MEMORY_GROWTH=1 \
			--bind \
			-o web/wasm/hotel_engine.js; \
		echo "WebAssembly compilation finished -> web/wasm/hotel_engine.js"; \
	else \
		echo "Emscripten (emcc) not found in PATH. The Web UI will run using its built-in JavaScript engine."; \
	fi

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory."

help:
	@echo "Available commands:"
	@echo "  make build   - Build hotel_core, hotel_tui, and hotel_tests"
	@echo "  make run     - Run native Terminal UI application"
	@echo "  make test    - Run automated C++ unit tests"
	@echo "  make web     - Start local Python web server for Web UI (http://localhost:8000)"
	@echo "  make wasm    - Compile C++ core to WebAssembly (requires emcc)"
	@echo "  make clean   - Remove build artifacts"
