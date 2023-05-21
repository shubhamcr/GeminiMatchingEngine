#include "OrderBook.h"

#include <vector>

#include "gtest/gtest.h"

namespace gemini::test
{

TEST(OrderBookTest, addOrder)
{
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

} // namespace gemini::test