#include "PriceBucket.h"
#include "gtest/gtest.h"

namespace gemini::test {

TEST(PriceBucketTest, addOrder) {
    Order o1{"order1", Side::BUY, "BTCUSD", 5, 10000, 0};
    Order o2{"order2", Side::SELL, "BTCUSD", 6, 10000, 1};
    Order o3{"order3", Side::SELL, "BTCUSD", 7, 10000, 2};

    std::list<Order> orders{o1, o2, o3};

    PriceBucket priceBucket;
    for (const auto &order : orders) {
        priceBucket.addOrder(order);
    }

    EXPECT_EQ(orders, priceBucket.getOrders());
    EXPECT_EQ(orders.size(), priceBucket.numOrders());
    EXPECT_EQ(18, priceBucket.getVolume());
    EXPECT_EQ(10000, priceBucket.getPrice());
}

TEST(PriceBucketTest, fillOrder) {
    Order o1{"order1", Side::SELL, "BTCUSD", 5, 10000, 0};
    Order o2{"order2", Side::SELL, "BTCUSD", 6, 10000, 1};
    Order o3{"order3", Side::SELL, "BTCUSD", 7, 10000, 2};
    std::list<Order> orders{o1, o2, o3};
    PriceBucket priceBucket;
    for (const auto &order : orders) {
        priceBucket.addOrder(order);
    }
    EXPECT_EQ(orders.size(), priceBucket.numOrders());
    EXPECT_EQ(18, priceBucket.getVolume());

    Order o4{"order4", Side::BUY, "BTCUSD", 10, 10001, 4};
    priceBucket.fillOrder(o4);
    EXPECT_EQ(0, o4.m_qty);
    EXPECT_EQ(2, priceBucket.numOrders());
    EXPECT_EQ(8, priceBucket.getVolume());
    EXPECT_EQ(10000, priceBucket.getPrice());
}

TEST(PriceBucketTest, fillOrderConsumeFullBook) {
    Order o1{"order1", Side::SELL, "BTCUSD", 5, 10000, 0};
    Order o2{"order2", Side::SELL, "BTCUSD", 6, 10000, 1};
    Order o3{"order3", Side::SELL, "BTCUSD", 7, 10000, 2};
    std::list<Order> orders{o1, o2, o3};
    PriceBucket priceBucket;
    for (const auto &order : orders) {
        priceBucket.addOrder(order);
    }
    EXPECT_EQ(orders.size(), priceBucket.numOrders());
    EXPECT_EQ(18, priceBucket.getVolume());

    Order o4{"order4", Side::BUY, "BTCUSD", 20, 10001, 4};
    priceBucket.fillOrder(o4);
    EXPECT_EQ(2, o4.m_qty);
    EXPECT_EQ(0, priceBucket.numOrders());
    EXPECT_EQ(0, priceBucket.getVolume());
}

} // namespace gemini::test
