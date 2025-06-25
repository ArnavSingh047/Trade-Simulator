#include "OrderBook.h"

void OrderBook::update(const nlohmann::json &data) {
    bids.clear();
    asks.clear();
    for (auto &b : data["bids"]) {
        bids.push_back({ std::stod(b[0].get<std::string>()),
                         std::stod(b[1].get<std::string>()) });
    }
    for (auto &a : data["asks"]) {
        asks.push_back({ std::stod(a[0].get<std::string>()),
                         std::stod(a[1].get<std::string>()) });
    }
}

double OrderBook::bestBid() const {
    return bids.empty() ? 0.0 : bids.front().price;
}

double OrderBook::bestAsk() const {
    return asks.empty() ? 0.0 : asks.front().price;
}
