#pragma once

#include "Enums.h"
#include "Types.h"

#include <cstdint>
#include <string>

namespace gemini {

struct Order {
    std::string m_orderId;
    Side m_side;
    std::string m_symbol;
    QtyT m_qty;
    PriceT m_prc;
    TimeT m_timestamp;

    bool operator==(const Order &other) const {
        return m_orderId == other.m_orderId and m_side == other.m_side and
               m_symbol == other.m_symbol and m_qty == other.m_qty and
               m_prc == other.m_prc;
    }
};

} // namespace gemini