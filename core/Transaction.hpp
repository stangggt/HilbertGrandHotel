#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

enum class TransactionStatus {
    ACTIVE,
    COMPLETED,
    CANCELLED
};

class Transaction {
private:
    std::string m_transactionId;
    int m_roomNumber;
    std::string m_guestUsername;
    int m_nights;
    double m_ratePerNight;
    double m_totalAmount;
    std::string m_timestamp;
    TransactionStatus m_status;

public:
    Transaction();
    Transaction(const std::string& transactionId, int roomNumber,
                const std::string& guestUsername, int nights,
                double ratePerNight, double totalAmount,
                const std::string& timestamp,
                TransactionStatus status = TransactionStatus::ACTIVE);

    // Getters
    const std::string& getTransactionId() const noexcept { return m_transactionId; }
    int getRoomNumber() const noexcept { return m_roomNumber; }
    const std::string& getGuestUsername() const noexcept { return m_guestUsername; }
    int getNights() const noexcept { return m_nights; }
    double getRatePerNight() const noexcept { return m_ratePerNight; }
    double getTotalAmount() const noexcept { return m_totalAmount; }
    const std::string& getTimestamp() const noexcept { return m_timestamp; }
    TransactionStatus getStatus() const noexcept { return m_status; }

    // Setters
    void setStatus(TransactionStatus status) { m_status = status; }
    void setTotalAmount(double total) { m_totalAmount = total; }

    std::string toCsvRow() const;
    static Transaction fromCsvRow(const std::string& row);

    static std::string statusToString(TransactionStatus status);
    static TransactionStatus stringToStatus(const std::string& str);
};

#endif // TRANSACTION_HPP
