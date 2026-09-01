#pragma once

#include <string>
#include <vector>

namespace ConsoleUtils {

    namespace Color {
        const std::string RESET       = "\033[0m";
        const std::string BOLD        = "\033[1m";
        const std::string DIM         = "\033[2m";
        const std::string RED         = "\033[31m";
        const std::string GREEN       = "\033[32m";
        const std::string YELLOW      = "\033[33m";
        const std::string BLUE        = "\033[34m";
        const std::string MAGENTA     = "\033[35m";
        const std::string CYAN        = "\033[36m";
        const std::string WHITE       = "\033[37m";

        const std::string BOLD_RED    = "\033[1;31m";
        const std::string BOLD_GREEN  = "\033[1;32m";
        const std::string BOLD_YELLOW = "\033[1;33m";
        const std::string BOLD_BLUE   = "\033[1;34m";
        const std::string BOLD_CYAN   = "\033[1;36m";
        const std::string BOLD_WHITE  = "\033[1;37m";

        const std::string BG_BLUE     = "\033[44m";
        const std::string BG_GREEN    = "\033[42m";
    }

    int displayWidth(const std::string& str);
    std::string padRight(const std::string& str, int width);

    void clearScreen();
    void printDivider(int width = 78, char ch = '-');
    void printHeader(const std::string& title, const std::string& subtitle = "");
    void printBox(const std::string& title, const std::vector<std::string>& lines, int width = 70);
    void printTable(const std::vector<std::string>& headers,
                    const std::vector<int>& widths,
                    const std::vector<std::vector<std::string>>& rows);

    std::string readLine(const std::string& prompt);
    int readInt(const std::string& prompt, int minVal, int maxVal);
    void pause();

} // namespace ConsoleUtils
