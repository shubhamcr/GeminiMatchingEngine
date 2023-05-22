#include <charconv>
#include <cstdio>
#include <iostream>
#include <sstream>

#include "MatchingEngine.h"
#include "Types.h"

static gemini::TimeT timestamp{};

bool validateInput(const std::string &orderId, const std::string &side,
                   const std::string &symbol, const std::string &qtyStr,
                   const std::string &prcStr, gemini::QtyT &qty,
                   gemini::PriceT &prc) {
    if (orderId.empty()) {
        std::cerr << "Order id cannot be empty!" << std::endl;
        return false;
    }

    if (side.empty() or (side != "BUY" and side != "SELL")) {
        std::cerr << "Invalid side:" << side
                  << "! Valid values for side are BUY and SELL." << std::endl;
        return false;
    }

    if (symbol.empty()) {
        std::cerr << "Instrument cannot be empty!" << std::endl;
        return false;
    }

    if (qtyStr.empty()) {
        std::cerr << "Quantity cannot be empty!" << std::endl;
        return false;
    } else {
        if (qtyStr[0] == '-') {
            std::cerr << "Quantity should not be a negative number!"
                      << std::endl;
            return false;
        }

        if (auto [ptr, ec] = std::from_chars(
                qtyStr.c_str(), qtyStr.c_str() + qtyStr.size(), qty);
            ec != std::errc()) {
            std::cerr << "Unable to parse Quantity! ERROR: "
                      << std::make_error_code(ec).message() << std::endl;
            return false;
        }

        if (qty == 0) {
            std::cerr << "Quantity cannot be zero!" << std::endl;
            return false;
        }
    }

    if (prcStr.empty()) {
        std::cerr << "Price cannot be empty!" << std::endl;
        return false;
    } else {
        if (prcStr[0] == '-') {
            std::cerr << "Price should not be a negative number!" << std::endl;
            return false;
        }

        if (auto [ptr, ec] = std::from_chars(
                prcStr.c_str(), prcStr.c_str() + prcStr.size(), prc);
            ec != std::errc()) {
            std::cerr << "Unable to parse Price! ERROR: "
                      << std::make_error_code(ec).message() << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    std::cerr << "====== Match Engine =====" << std::endl;
    std::cerr << "Enter 'exit' to quit" << std::endl;

    std::string line;
    std::string orderId;
    std::string side;
    std::string symbol;
    std::string qtyStr;
    std::string prcStr;

    gemini::MatchingEngine matchingEngine;

    while (getline(std::cin, line) && line != "exit") {
        std::cerr << "Received: '" << line << "'" << std::endl;
        std::istringstream iss(line);
        iss >> orderId;
        iss >> side;
        iss >> symbol;
        iss >> qtyStr;
        iss >> prcStr;

        gemini::QtyT qty{};
        gemini::PriceT prc{};
        if (not validateInput(orderId, side, symbol, qtyStr, prcStr, qty,
                              prc)) {
            std::cerr << "Unable to parse this input!" << std::endl;
        }

        matchingEngine.addOrder(orderId, side, symbol, qty, prc, ++timestamp);
    }

    matchingEngine.printAllOrdersInArrivalOrder();

    return 0;
}