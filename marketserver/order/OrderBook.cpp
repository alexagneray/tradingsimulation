#include "OrderBook.h"
#include <algorithm>

            #ifdef VERBOSE_MODE
                    #include <iostream>
            #endif

void OrderBook::AddBidOrder(Order &&order)
{
    std::lock_guard<std::mutex> lock(m_mutOrderBook);

            #ifdef VERBOSE_MODE
                    std::cout << "Adding bid order: " << order.id << " for asset "
                                << order.assetId << " with volume " << order.volume
                                << " at price " << order.price << std::endl;
            #endif
    
    m_setBidOrders.insert(std::move(order));
}

void OrderBook::AddAskOrder(Order &&order)
{
    std::lock_guard<std::mutex> lock(m_mutOrderBook);
            #ifdef VERBOSE_MODE
                    std::cout << "Adding ask order: " << order.id << " for asset "
                                << order.assetId << " with volume " << order.volume
                                << " at price " << order.price << std::endl;
            #endif
    m_setAskOrders.insert(std::move(order));
}

void OrderBook::RemoveBidOrder(int orderId)
{
    std::lock_guard<std::mutex> lock(m_mutOrderBook);

    auto it = std::find_if(m_setBidOrders.begin(), m_setBidOrders.end(), [orderId](const Order& o) {
        return o.id == orderId;
    });
    if (it != m_setBidOrders.end()) {
        m_setBidOrders.erase(it);
    }
            #ifdef VERBOSE_MODE
                    std::cout << "Removed bid order with ID: " << orderId << std::endl;
            #endif
}

void OrderBook::RemoveAskOrder(int orderId)
{
    std::lock_guard<std::mutex> lock(m_mutOrderBook);

    auto it = std::find_if(m_setAskOrders.begin(), m_setAskOrders.end(), [orderId](const Order& o) {
        return o.id == orderId;
    });
    if (it != m_setAskOrders.end()) {
        m_setAskOrders.erase(it);
    }
            #ifdef VERBOSE_MODE
                    std::cout << "Removed ask order with ID: " << orderId << std::endl;
            #endif
}

void OrderBook::ExecuteOrders()
{
    if(m_setAskOrders.empty() || m_setBidOrders.empty()) {
        #ifdef VERBOSE_MODE
                    std::cout << "No order to execute !" << std::endl;
            #endif
        return; // No orders to execute
    }
    std::lock_guard<std::mutex> lock(m_mutOrderBook);
    auto itBid = m_setBidOrders.begin();
    auto itAsk = m_setAskOrders.begin();
    
    if (itBid->price < itAsk->price) {
        return; // No match possible
    }
    
    Order bid = *itBid;
    Order ask = *itAsk;
    
    m_setBidOrders.erase(itBid);
    m_setAskOrders.erase(itAsk);
    
    int trade_volume = std::min(bid.volume, ask.volume);
    
    // Execute trade at ask price (conventional)
    // Here you could add logging or callbacks for the trade
    
    if (bid.volume > trade_volume) {
        bid.volume -= trade_volume;
        m_setBidOrders.insert(bid);
    }
    
    if (ask.volume > trade_volume) {
        ask.volume -= trade_volume;
        m_setAskOrders.insert(ask);
    }

            #ifdef VERBOSE_MODE
                    std::cout << "Order executed ! " << std::endl;
            #endif
}

void OrderBook::Attach(std::shared_ptr<Orderer> orderer)
{
    m_lstOrderers.push_back(orderer);
}

void OrderBook::Detach(std::shared_ptr<Orderer> orderer)
{
    m_lstOrderers.remove(orderer);
}
