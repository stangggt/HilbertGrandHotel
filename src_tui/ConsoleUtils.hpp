#ifndef CONSOLE_UTILS_HPP
#define CONSOLE_UTILS_HPP

#include <string>
#include <vector>

namespace ConsoleUtils {

    // ANSI Colors
    namespace Color {
        inline const std::string RESET       = "\033[0m";
        inline const std::string BOLD        = "\033[1m";
        inline const std::string DIM         = "\033[2m";
        inline const std::string UNDERLINE   = "\033[4m";

        inline const std::string RED         = "\033[31m";
        inline const std::string GREEN       = "\033[32m";
        inline const std::string YELLOW      = "\033[33m";
        inline const std::string BLUE        = "\033[34m";
        inline const std::string MAGENTA     = "\033[35m";
        inline const std::string CYAN        = "\033[36m";
        inline const std::string WHITE       = "\033[37m";

        inline const std::string BOLD_RED    = "\033[1;31m";
        inline const std::string BOLD_GREEN  = "\033[1;32m";
        inline const std::string BOLD_YELLOW = "\033[1;33m";
        inline const std::string BOLD_BLUE   = "\033[1;34m";
        inline const std::string BOLD_CYAN   = "\033[1;36m";
        inline const std::string BOLD_WHITE  = "\033[1;37m";

        inline const std::string BG_BLUE     = "\033[44m";
        inline const std::string BG_DARK     = "\033[40m";
    }

    void clearScreen();
    void printHeader(const std::string& title, const std::string& subtitle = "");
    void printBox(const std::string& title, const std::vector<std::string>& lines, int width = 60);
    void printTable(const std::vector<std::string>& headers,
                    const std::vector<int>& widths,
                    const std::vector<std::vector<std::string>>& rows);
    void printDivider(int width = 78, char ch = '=');

    std::string readLine(const std::string& prompt);
    int readInt(const std::string& prompt, int minVal = -999999, int maxVal = 999999);
    double readDouble(const std::string& prompt, double minVal = -999999.0, double maxVal = 999999.0);
    bool readBool(const std::string& prompt);
    void pause(const std::string& message = "Press [Enter] to continue...");

} // namespace ConsoleUtils

#endif // CONSOLE_UTILS_HPP
