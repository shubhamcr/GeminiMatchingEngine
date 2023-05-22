#include <tuple>
#include <vector>

#include "MatchingEngine.h"
#include "gtest/gtest.h"

namespace gemini::test {

TEST(MatchingEngineTest, addOrder) {
    using OrderTuple =
        std::tuple<std::string, std::string, std::string, QtyT, PriceT, TimeT>;
    std::vector<OrderTuple> inputs{
        OrderTuple{"12345", "BUY", "BTCUSD", 5, 10000, 0},
        OrderTuple{"zod42", "SELL", "BTCUSD", 2, 10001, 1},
        OrderTuple{"13471", "BUY", "BTCUSD", 6, 9971, 2},
        OrderTuple{"11431", "BUY", "ETHUSD", 9, 175, 3},
        OrderTuple{"1abe14", "SELL", "BTCUSD", 7, 9800, 4},
        OrderTuple{"plu401", "SELL", "ETHUSD", 5, 170, 5},
        OrderTuple{"45691", "BUY", "ETHUSD", 3, 180, 6}};

    MatchingEngine matchingEngine;
    for (const auto &input : inputs) {
        matchingEngine.addOrder(std::get<0>(input), std::get<1>(input),
                                std::get<2>(input), std::get<3>(input),
                                std::get<4>(input), std::get<5>(input));
    }

    std::vector<Order> expectedOrders{
        Order{"zod42", Side::SELL, "BTCUSD", 2, 10001, 1},
        Order{"13471", Side::BUY, "BTCUSD", 4, 9971, 2},
        Order{"11431", Side::BUY, "ETHUSD", 4, 175, 3},
        Order{"45691", Side::BUY, "ETHUSD", 3, 180, 6}};

    EXPECT_EQ(expectedOrders, matchingEngine.getAllOrdersSortedByArrivalTime());
}

/// Tests the scenario when no order is filled as the spread is never crossed.
TEST(MatchingEngineTest, addOrderZeroOrdersFilled) {
    using OrderTuple =
        std::tuple<std::string, std::string, std::string, QtyT, PriceT, TimeT>;
    std::vector<OrderTuple> inputs{
        OrderTuple{"12345", "BUY", "BTCUSD", 5, 10000, 0},
        OrderTuple{"zod42", "SELL", "BTCUSD", 2, 10001, 1},
        OrderTuple{"13471", "BUY", "BTCUSD", 6, 9971, 2},
        OrderTuple{"11431", "BUY", "ETHUSD", 9, 175, 3},
        OrderTuple{"1abe14", "SELL", "BTCUSD", 7, 19800, 4},
        OrderTuple{"plu401", "SELL", "ETHUSD", 5, 1700, 5},
        OrderTuple{"45691", "BUY", "ETHUSD", 3, 180, 6}};

    MatchingEngine matchingEngine;
    for (const auto &input : inputs) {
        matchingEngine.addOrder(std::get<0>(input), std::get<1>(input),
                                std::get<2>(input), std::get<3>(input),
                                std::get<4>(input), std::get<5>(input));
    }

    std::vector<Order> expectedOrders{
        Order{"zod42", Side::SELL, "BTCUSD", 2, 10001, 1},
        Order{"1abe14", Side::SELL, "BTCUSD", 7, 19800, 4},
        Order{"plu401", Side::SELL, "ETHUSD", 5, 1700, 5},
        Order{"12345", Side::BUY, "BTCUSD", 5, 10000, 0},
        Order{"13471", Side::BUY, "BTCUSD", 6, 9971, 2},
        Order{"11431", Side::BUY, "ETHUSD", 9, 175, 3},
        Order{"45691", Side::BUY, "ETHUSD", 3, 180, 6}};

    EXPECT_EQ(expectedOrders, matchingEngine.getAllOrdersSortedByArrivalTime());
}

} // namespace gemini::test