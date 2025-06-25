#include "AlmgrenChriss.h"
#include <cmath>

AlmgrenChriss::AlmgrenChriss(double vol, double liq)
    : volatility(vol), liquidity(liq) {}

double AlmgrenChriss::calculate_impact(double quantity) {
    return volatility * std::sqrt(quantity / liquidity);
}
