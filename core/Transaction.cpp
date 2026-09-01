#include "Transaction.hpp"
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

Transaction::Transaction()
    : m_transactionId(""), m_roomNumber(0), m_guestUsername(""),
      m_nights(0), m_ratePerNight(0.0), m_totalAmount(0.0),
      m_timestamp(""), m_status(TransactionStatus::ACTIVE) {}

Transaction::Transaction(const std::string& transactionId, int roomNumber,
                         const std::string& guestUsername, int nights,
                         double ratePerNight, double totalAmount,
                         const std::string& timestamp,
                         TransactionStatus status)
    : m_transactionId(transactionId), m_roomNumber(roomNumber),
      m_guestUsername(guestUsername), m_nights(nights),
      m_ratePerNight(ratePerNight), m_totalAmount(totalAmount),
      m_timestamp(timestamp), m_status(status) {}

std::string Transaction::statusToString(TransactionStatus status) {
    switch (status) {
        case TransactionStatus::ACTIVE:    return "ACTIVE";
        case TransactionStatus::COMPLETED: return "COMPLETED";
        case TransactionStatus::CANCELLED: return "CANCELLED";
        default:                           return "ACTIVE";
    }
}

TransactionStatus Transaction::stringToStatus(const std::string& str) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s == "COMPLETED") return TransactionStatus::COMPLETED;
    if (s == "CANCELLED") return TransactionStatus::CANCELLED;
    return TransactionStatus::ACTIVE;
}

std::string Transaction::toCsvRow() const {
    std::ostringstream ss;
    ss << m_transactionId << ","
       << m_roomNumber << ","
       << m_guestUsername << ","
       << m_nights << ","
       << std::fixed << std::setprecision(2) << m_ratePerNight << ","
       << std::fixed << std::setprecision(2) << m_totalAmount << ","
       << m_timestamp << ","
       << statusToString(m_status);
    return ss.str();
}

Transaction Transaction::fromCsvRow(const std::string& row) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(row);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 8) {
        return Transaction();
    }

    std::string id = tokens[0];
    int roomNum = std::stoi(tokens[1]);
    std::string guest = tokens[2];
    int nights = std::stoi(tokens[3]);
    double rate = std::stod(tokens[4]);
    double total = std::stod(tokens[5]);
    std::string timestamp = tokens[6];
    TransactionStatus status = stringToStatus(tokens[7]);

    return Transaction(id, roomNum, guest, nights, rate, total, timestamp, status);
}
