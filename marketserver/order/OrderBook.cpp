#include "OrderBook.h"
#include <algorithm>

void OrderBook::AddBidOrder(Order &&order)
{
    bidOrders.insert(std::move(order));
}

void OrderBook::AddAskOrder(Order &&order)
{
    askOrders.insert(std::move(order));
}

void OrderBook::RemoveBidOrder(int orderId)
{
    auto it = std::find_if(bidOrders.begin(), bidOrders.end(), [orderId](const Order& o) {
        return o.id == orderId;
    });
    if (it != bidOrders.end()) {
        bidOrders.erase(it);
    }
}

void OrderBook::RemoveAskOrder(int orderId)
{
    auto it = std::find_if(askOrders.begin(), askOrders.end(), [orderId](const Order& o) {
        return o.id == orderId;
    });
    if (it != askOrders.end()) {
        askOrders.erase(it);
    }
}

void OrderBook::ExecuteOrders()
{
    while (!bidOrders.empty() && !askOrders.empty()) {
        auto itBid = bidOrders.begin();
        auto itAsk = askOrders.begin();
        
        if (itBid->price < itAsk->price) {
            break; // No match possible
        }
        
        Order bid = *itBid;
        Order ask = *itAsk;
        
        bidOrders.erase(itBid);
        askOrders.erase(itAsk);
        
        int trade_volume = std::min(bid.volume, ask.volume);
        
        // Execute trade at ask price (conventional)
        // Here you could add logging or callbacks for the trade
        
        if (bid.volume > trade_volume) {
            bid.volume -= trade_volume;
            bidOrders.insert(bid);
        }
        
        if (ask.volume > trade_volume) {
            ask.volume -= trade_volume;
            askOrders.insert(ask);
        }
    }
}
