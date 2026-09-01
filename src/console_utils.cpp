#include "../include/console_utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cstdint>

namespace ConsoleUtils {

    int displayWidth(const std::string& str) {
        int width = 0;
        size_t i = 0;
        size_t n = str.size();
        while (i < n) {
            // Skip ANSI escape sequence \033[...m
            if (str[i] == '\033' && i + 1 < n && str[i + 1] == '[') {
                i += 2;
                while (i < n && str[i] != 'm') ++i;
                if (i < n) ++i;
                continue;
            }

            unsigned char c = (unsigned char)str[i];
            if (c < 0x80) {
                // Standard ASCII
                if (c >= 0x20) ++width;
                ++i;
            } else if ((c & 0xE0) == 0xC0) {
                // 2-byte UTF-8
                if (i + 1 < n) {
                    ++width;
                    i += 2;
                } else {
                    ++i;
                }
            } else if ((c & 0xF0) == 0xE0) {
                // 3-byte UTF-8 (Thai characters 0x0E00 - 0x0E7F)
                if (i + 2 < n) {
                    unsigned char c1 = (unsigned char)str[i + 1];
                    unsigned char c2 = (unsigned char)str[i + 2];
                    uint32_t cp = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);

                    // Thai combining marks with ZERO display width:
                    // 0x0E31 (ั), 0x0E34 - 0x0E3A (ิ ี ึ ื ุ ู ฺ), 0x0E47 - 0x0E4E (็ ่ ้ ๊ ๋ ์ ํ ๎)
                    bool isCombining = (cp == 0x0E31) ||
                                       (cp >= 0x0E34 && cp <= 0x0E3A) ||
                                       (cp >= 0x0E47 && cp <= 0x0E4E);
                    if (!isCombining) {
                        ++width;
                    }
                    i += 3;
                } else {
                    ++width;
                    ++i;
                }
            } else if ((c & 0xF8) == 0xF0) {
                // 4-byte UTF-8 (Emoji / Wide characters)
                width += 2;
                i += 4;
            } else {
                ++i;
            }
        }
        return width;
    }

    std::string padRight(const std::string& str, int targetWidth) {
        int curW = displayWidth(str);
        int pad = targetWidth - curW;
        if (pad <= 0) return str;
        return str + std::string(pad, ' ');
    }

    void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void printDivider(int width, char ch) {
        std::cout << Color::DIM;
        for (int i = 0; i < width; ++i) {
            std::cout << ch;
        }
        std::cout << Color::RESET << "\n";
    }

    void printHeader(const std::string& title, const std::string& subtitle) {
        std::cout << "\n";
        printDivider(82, '=');
        std::cout << Color::BOLD_CYAN << "  ✦ " << title << Color::RESET;
        if (!subtitle.empty()) {
            std::cout << Color::DIM << "  |  " << subtitle << Color::RESET;
        }
        std::cout << "\n";
        printDivider(82, '=');
    }

    void printBox(const std::string& title, const std::vector<std::string>& lines, int width) {
        std::cout << Color::CYAN << "┌─ " << Color::BOLD_WHITE << title << " "
                  << Color::CYAN;
        int titleLen = displayWidth(title) + 4;
        for (int i = titleLen; i < width; ++i) std::cout << "─";
        std::cout << "┐\n" << Color::RESET;

        for (const auto& line : lines) {
            std::cout << Color::CYAN << "│ " << Color::RESET;
            std::cout << padRight(line, width - 4);
            std::cout << Color::CYAN << " │\n" << Color::RESET;
        }

        std::cout << Color::CYAN << "└";
        for (int i = 0; i < width - 2; ++i) std::cout << "─";
        std::cout << "┘\n" << Color::RESET;
    }

    void printTable(const std::vector<std::string>& headers,
                    const std::vector<int>& widths,
                    const std::vector<std::vector<std::string>>& rows) {
        if (headers.size() != widths.size()) return;

        // Top Border
        std::cout << Color::DIM << "┌";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┬";
        }
        std::cout << "┐\n" << Color::RESET;

        // Header Row
        std::cout << Color::DIM << "│" << Color::RESET;
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << " " << Color::BOLD_YELLOW
                      << padRight(headers[i], widths[i])
                      << Color::RESET << Color::DIM << " │" << Color::RESET;
        }
        std::cout << "\n";

        // Header Separator
        std::cout << Color::DIM << "├";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┼";
        }
        std::cout << "┤\n" << Color::RESET;

        // Data Rows
        for (const auto& row : rows) {
            std::cout << Color::DIM << "│" << Color::RESET;
            for (size_t i = 0; i < widths.size(); ++i) {
                std::string cell = (i < row.size()) ? row[i] : "";
                std::cout << " " << padRight(cell, widths[i])
                          << Color::DIM << " │" << Color::RESET;
            }
            std::cout << "\n";
        }

        // Bottom Border
        std::cout << Color::DIM << "└";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┴";
        }
        std::cout << "┘\n" << Color::RESET;
    }

    std::string readLine(const std::string& prompt) {
        std::cout << Color::BOLD_WHITE << prompt << Color::RESET;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int readInt(const std::string& prompt, int minVal, int maxVal) {
        while (true) {
            std::cout << Color::BOLD_WHITE << prompt << Color::RESET;
            std::string line;
            if (!std::getline(std::cin, line)) {
                return minVal;
            }
            if (line.empty()) continue;

            try {
                int val = std::stoi(line);
                if (val >= minVal && val <= maxVal) {
                    return val;
                }
            } catch (...) {}

            std::cout << Color::BOLD_RED << "  [!] กรุณาระบุตัวเลขระหว่าง "
                      << minVal << " ถึง " << maxVal << "\n" << Color::RESET;
        }
    }

    void pause() {
        std::cout << Color::DIM << "\n  กด Enter เพื่อดำเนินการต่อ..." << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

} // namespace ConsoleUtils
