#pragma once

#include "PriceBucket.h"

#include <iostream>
#include <map>
#include <vector>

namespace gemini {

class OrderBook {
    using BuyBookT = std::map<PriceT, PriceBucket, std::greater<PriceT>>;
    using SellBookT = std::map<PriceT, PriceBucket>;

public:
    void addOrder(Order &order) {
        if (isLimitOrder(order)) {
            addLimitOrder(order);
        } else {
            addMarketOrder(order);
        }
    }

    bool isLimitOrder(const Order &order) const noexcept {
        return order.m_prc > 0;
    }
    bool isBuyOrder(const Order &order) const noexcept {
        return order.m_side == Side::BUY;
    }
    bool isSellOrder(const Order &order) const noexcept {
        return order.m_side == Side::SELL;
    }

    std::vector<Order> getAllOrders() const {
        std::vector<Order> result;
        getAllOrdersUtil(m_sellBook, result);
        getAllOrdersUtil(m_buyBook, result);
        return result;
    }

private:
    /// TODO: confirm with Hiring team if Market orders are allowed or not.
    void addMarketOrder([[maybe_unused]] Order &order) {}

    void addLimitOrder(Order &order) {
        if (isBuyOrder(order)) {
            static std::greater_equal<PriceT> ge;
            tryCrossingSpread(order, m_sellBook, ge);
            addOrderInBook(order, m_buyBook);
        } else {
            static std::less_equal<PriceT> le;
            tryCrossingSpread(order, m_buyBook, le);
            addOrderInBook(order, m_sellBook);
        }
    }

    template <typename BookT, typename Comp>
    void tryCrossingSpread(Order &order, BookT &oppBook, Comp &comp) {
        for (auto &[prc, priceBucket] : oppBook) {
            if (order.m_qty == 0 or not comp(order.m_prc, prc)) {
                break;
            }
            priceBucket.fillOrder(order);
        }
    }

    template <typename BookT>
    void addOrderInBook(const Order &order, BookT &book) {
        if (order.m_qty == 0) {
            return;
        }

        if (book.find(order.m_prc) != book.end()) {
            book[order.m_prc].addOrder(order);
        } else {
            book.emplace(order.m_prc, PriceBucket{order});
        }
    }

    template <typename BookT>
    void getAllOrdersUtil(const BookT &book, std::vector<Order> &result) const {
        for (const auto &[prc, prcBucket] : book) {
            const auto &orders = prcBucket.getOrders();
            result.insert(result.end(), orders.begin(), orders.end());
        }
    }

    BuyBookT m_buyBook;
    SellBookT m_sellBook;
};

} // namespace gemini