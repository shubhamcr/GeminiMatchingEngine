#pragma once

#include "OrderBook.h"
#include "Utils.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace gemini {

class MatchingEngine {
public:
    void addOrder(const std::string &orderId, const std::string &side,
                  const std::string &symbol, QtyT qty, PriceT prc,
                  TimeT timestamp) {
        Order order{orderId, utils::getSide(side), symbol, qty, prc, timestamp};
        m_symbolToOrderBook[symbol].addOrder(order);
    }

    void printAllOrdersInArrivalOrder() {
        auto allOrders = getAllOrdersSortedByArrivalTime();
        std::cout << std::endl;
        for (const auto &order : allOrders) {
            std::cout << order.m_orderId << " " << utils::getSide(order.m_side)
                      << " " << order.m_symbol << " " << order.m_qty << " "
                      << order.m_prc << std::endl;
        }
    }

    /**
     *  @return vector of all orders present in the system sorted by their
     * arrival times. In the resultant vector all SELL orders are present before
     * BUY orders.
     */
    std::vector<Order> getAllOrdersSortedByArrivalTime() const {
        std::vector<Order> allOrders;
        for (const auto &[symbol, book] : m_symbolToOrderBook) {
            auto orders = book.getAllOrders();
            allOrders.insert(allOrders.end(), orders.begin(), orders.end());
        }

        std::sort(allOrders.begin(), allOrders.end(),
                  [](const Order &o1, const Order &o2) {
                      if (o1.m_side != o2.m_side) {
                          return o1.m_side == Side::SELL;
                      }
                      return o1.m_timestamp < o2.m_timestamp;
                  });

        return allOrders;
    }

private:
    std::unordered_map<std::string, OrderBook> m_symbolToOrderBook;
};

} // namespace gemini