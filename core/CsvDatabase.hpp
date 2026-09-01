#ifndef CSV_DATABASE_HPP
#define CSV_DATABASE_HPP

#include "DynamicArray.hpp"
#include <string>
#include <vector>

class CsvDatabase {
public:
    /**
     * @brief Resolve file path checking current dir and parent dirs (e.g., "data/rooms.csv" vs "../data/rooms.csv").
     */
    static std::string resolvePath(const std::string& relativePath);

    /**
     * @brief Read lines from a CSV file (skipping empty lines and comments).
     * @param filepath Path to the CSV file.
     * @param hasHeader If true, the first row is skipped or returned as header.
     * @param outHeader Optional pointer to store the header string.
     * @return DynamicArray of raw CSV rows.
     */
    static DynamicArray<std::string> readRows(const std::string& filepath, bool hasHeader = true, std::string* outHeader = nullptr);

    /**
     * @brief Write rows atomically to a CSV file.
     * @param filepath Path to the destination CSV file.
     * @param header The CSV header line.
     * @param rows The DynamicArray of row strings to write.
     * @return true on success, false on error.
     */
    static bool writeRows(const std::string& filepath, const std::string& header, const DynamicArray<std::string>& rows);

    /**
     * @brief Utility: Split a comma-separated row string respecting basic token rules.
     */
    static std::vector<std::string> parseRow(const std::string& row);

    /**
     * @brief Utility: Join tokens into a CSV row string.
     */
    static std::string joinRow(const std::vector<std::string>& tokens);
};

#endif // CSV_DATABASE_HPP
