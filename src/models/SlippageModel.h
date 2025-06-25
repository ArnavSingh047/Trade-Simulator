#ifndef SLIPPAGEMODEL_H
#define SLIPPAGEMODEL_H

class SlippageModel {
public:
    static double estimateSlippage(double quantity, double /*midPrice*/) {
        // Simple linear slippage
        return 0.002 * quantity;
    }
};

#endif // SLIPPAGEMODEL_H
