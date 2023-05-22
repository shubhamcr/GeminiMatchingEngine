#pragma once

#include "Enums.h"

#include <string>

namespace gemini::utils {

Side getSide(const std::string &side) {
    return side == "BUY" ? Side::BUY : Side::SELL;
}

std::string getSide(Side side) { return side == Side::BUY ? "BUY" : "SELL"; }

} // namespace gemini::utils
