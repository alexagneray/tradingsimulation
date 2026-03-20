#pragma once

#include "MarketFacade.h"
#include "order/Order.h"
#include <vector>

struct OrderEntry
{
    Order order;
    OrderDir dir;
    bool executed;
};
/**
 * Une entité qui passe des ordres, et qui peut être notifiée quand l'ordre a été exécuté. 
 */
class Orderer
{
    private:
    const MarketFacade& m_marketFacade;
    std::vector<OrderEntry> m_vecOrderEntries;

    public:
    Orderer(const MarketFacade& market);
    void Update(const Order& order, bool executed, time_t executionTime);
};