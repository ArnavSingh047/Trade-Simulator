#ifndef ALMGRENCHRISS_H
#define ALMGRENCHRISS_H

class AlmgrenChriss {
    double volatility;
    double liquidity;

public:
    AlmgrenChriss(double vol, double liq);
    double calculate_impact(double quantity);
};

#endif // ALMGRENCHRISS_H
