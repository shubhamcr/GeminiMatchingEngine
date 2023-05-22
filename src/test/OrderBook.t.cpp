#include <vector>

#include "OrderBook.h"
#include "gtest/gtest.h"

namespace gemini::test {

TEST(OrderBookTest, addOrder) {
    Order o1{"12345", Side::BUY, "BTCUSD", 5, 10000, 0};
    Order o2{"zod42", Side::SELL, "BTCUSD", 2, 10001, 1};
    Order o3{"13471", Side::BUY, "BTCUSD", 6, 9971, 2};
    Order o4{"1abe14", Side::SELL, "BTCUSD", 7, 9800, 4};

    std::vector<Order> orders{o1, o2, o3, o4};
    std::vector<QtyT> remainingQtyAfterFill{5, 2, 6, 0};
    OrderBook orderBook;
    for (std::size_t i = 0; i < orders.size(); ++i) {
        orderBook.addOrder(orders[i]);
        EXPECT_EQ(remainingQtyAfterFill[i], orders[i].m_qty);
    }
}

/// Test for the case when no order gets filled as the spread is never crossed.
TEST(OrderBookTest, addOrderZeroOrdersFilled) {
    std::vector<QtyT> qty{5, 2, 6, 7, 8, 15, 20};
    Order o1{"12345", Side::BUY, "BTCUSD", qty[0], 10000, 0};
    Order o2{"zod42", Side::SELL, "BTCUSD", qty[1], 10001, 1};
    Order o3{"13471", Side::BUY, "BTCUSD", qty[2], 9971, 2};
    Order o4{"1abe14", Side::SELL, "BTCUSD", qty[3], 10002, 4};
    Order o5{"1abe141", Side::SELL, "BTCUSD", qty[4], 10001, 5};
    Order o6{"order6", Side::BUY, "BTCUSD", qty[5], 10000, 6};
    Order o7{"order7", Side::BUY, "BTCUSD", qty[6], 9000, 7};

    std::vector<Order> orders{o1, o2, o3, o4, o5, o6, o7};
    OrderBook orderBook;
    for (std::size_t i = 0; i < orders.size(); ++i) {
        orderBook.addOrder(orders[i]);
        EXPECT_EQ(qty[i], orders[i].m_qty);
    }
}

} // namespace gemini::test