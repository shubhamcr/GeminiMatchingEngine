#pragma once

#include "Order.h"

#include <list>

namespace gemini
{

class PriceBucket
{
public:
    PriceBucket() = default;
    PriceBucket(const Order& order) : m_prc{order.m_prc}, m_volume{order.m_qty}, m_orders{order}
    {
    }
    
    void addOrder(const Order& order) {
        m_orders.push_back(order);
        m_volume += order.m_qty;
    }

    std::size_t numOrders() const { return m_orders.size(); }
 
    void fillOrder(Order& order) {
        if (m_orders.empty()) {
            return;
        }
        auto counterOrderIt = m_orders.begin();
        while (order.m_qty != 0 and counterOrderIt != m_orders.end()) {
            auto& counterOrder = *counterOrderIt;
            auto fillQty = std::min(order.m_qty, counterOrder.m_qty);
            std::cout << "TRADE " << order.m_symbol << " " << order.m_orderId 
                      << " " << counterOrder.m_orderId << " " << fillQty
                      << " " << m_prc << std::endl;
            
            m_volume -= fillQty;
            order.m_qty -= fillQty;
            counterOrder.m_qty -= fillQty;
            if (counterOrder.m_qty == 0) {
                counterOrderIt = m_orders.erase(counterOrderIt);
            }
        }

    }

    auto begin() { return m_orders.begin(); }
    auto end() { return m_orders.end(); }

    const std::list<Order>& getOrders() const noexcept { return m_orders; }

private:
    PriceT m_prc{};
    uint64_t m_volume{};
    std::list<Order> m_orders;
};

} // namespace gemini