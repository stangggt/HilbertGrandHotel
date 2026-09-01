#include "CsvDatabase.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>

static bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string CsvDatabase::resolvePath(const std::string& relativePath) {
    // 1. Direct path
    if (fileExists(relativePath)) {
        return relativePath;
    }
    // 2. Parent directory (e.g. if running inside build/ folder)
    std::string parentPath = "../" + relativePath;
    if (fileExists(parentPath)) {
        return parentPath;
    }
    // 3. Two levels up
    std::string grandParentPath = "../../" + relativePath;
    if (fileExists(grandParentPath)) {
        return grandParentPath;
    }
    // Fallback to direct path
    return relativePath;
}

DynamicArray<std::string> CsvDatabase::readRows(const std::string& filepath, bool hasHeader, std::string* outHeader) {
    DynamicArray<std::string> rows;
    std::string actualPath = resolvePath(filepath);
    std::ifstream file(actualPath);

    if (!file.is_open()) {
        std::cerr << "[CsvDatabase] Warning: Could not open file for reading: " << actualPath << "\n";
        return rows;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        // Strip trailing \r if any (Windows/DOS line endings)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Skip blank lines
        if (line.empty()) {
            continue;
        }

        if (isFirstLine && hasHeader) {
            if (outHeader) {
                *outHeader = line;
            }
            isFirstLine = false;
            continue;
        }

        rows.push_back(line);
        isFirstLine = false;
    }

    file.close();
    return rows;
}

bool CsvDatabase::writeRows(const std::string& filepath, const std::string& header, const DynamicArray<std::string>& rows) {
    std::string actualPath = resolvePath(filepath);
    std::string tempPath = actualPath + ".tmp";

    std::ofstream file(tempPath);
    if (!file.is_open()) {
        std::cerr << "[CsvDatabase] Error: Could not open temp file for writing: " << tempPath << "\n";
        return false;
    }

    if (!header.empty()) {
        file << header << "\n";
    }

    for (size_t i = 0; i < rows.size(); ++i) {
        file << rows[i] << "\n";
    }

    file.close();

    // Atomic replacement
    if (std::rename(tempPath.c_str(), actualPath.c_str()) != 0) {
        // If rename fails (e.g. cross-device), attempt manual overwrite
        std::ifstream src(tempPath, std::ios::binary);
        std::ofstream dst(actualPath, std::ios::binary);
        if (src.is_open() && dst.is_open()) {
            dst << src.rdbuf();
            src.close();
            dst.close();
            std::remove(tempPath.c_str());
            return true;
        }
        std::cerr << "[CsvDatabase] Error: Failed to commit write to " << actualPath << "\n";
        return false;
    }

    return true;
}

std::vector<std::string> CsvDatabase::parseRow(const std::string& row) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(row);
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string CsvDatabase::joinRow(const std::vector<std::string>& tokens) {
    std::ostringstream ss;
    for (size_t i = 0; i < tokens.size(); ++i) {
        ss << tokens[i];
        if (i + 1 < tokens.size()) {
            ss << ",";
        }
    }
    return ss.str();
}
