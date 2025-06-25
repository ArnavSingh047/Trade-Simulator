#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct Level {
    double price;
    double volume;
};

class OrderBook {
public:
    void update(const nlohmann::json &data);
    double bestBid() const;
    double bestAsk() const;

private:
    std::vector<Level> bids, asks;
};

#endif // ORDERBOOK_H
