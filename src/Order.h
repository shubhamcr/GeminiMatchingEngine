#pragma once

#include "Enums.h"
#include "Types.h"

#include <cstdint>
#include <string>

namespace gemini
{

struct Order {
    std::string m_orderId;
    Side m_side;
    std::string m_symbol;
    QtyT m_qty;
    PriceT m_prc;
    TimeT m_timestamp;
};

} // namespace gemini