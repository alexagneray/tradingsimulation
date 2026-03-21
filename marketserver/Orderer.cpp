#include "Orderer.h"

#include <algorithm>
#include <memory>

Orderer::Orderer(MarketFacade &market):
    m_marketFacade(market)
{
}

void Orderer::Update(const Order &order, bool executed, time_t executionTime)
{
    auto it = std::find_if(
        m_vecOrderEntries.begin(),
        m_vecOrderEntries.end(),
        [order] (const OrderEntry& oe) {
            return oe.order.id == order.id; 
        }
    );

    if(it != m_vecOrderEntries.end())
    {
        it->executed = executed;
    }
}
