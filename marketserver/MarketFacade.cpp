#include "MarketFacade.h"
#include "Market.h"
#include "order/OrderBook.h"

MarketFacade::MarketFacade():
    m_pMarket(std::make_unique<Market>())
{
    // Initialize market and order book if needed
}

MarketFacade::~MarketFacade()
{
    // Clean up resources if needed
}

void MarketFacade::WakeUp()
{
    m_pMarket->WakeUp();
}

void MarketFacade::Sleep()
{
    m_pMarket->Sleep();
}

void MarketFacade::placeAskOrder(Order&& order)
{
    m_pMarket->GetOrderBook().AddAskOrder(std::move(order));
}
void MarketFacade::cancelAskOrder(int orderId)
{
    m_pMarket->GetOrderBook().RemoveAskOrder(orderId);
}
void MarketFacade::placeBidOrder(Order&& order)
{
    m_pMarket->GetOrderBook().AddBidOrder(std::move(order));
}
void MarketFacade::cancelBidOrder(int orderId)
{
    m_pMarket->GetOrderBook().RemoveBidOrder(orderId);
}

void MarketFacade::AddAsset(Asset&& asset)
{
    m_pMarket->AddAsset(std::move(asset));
}


void MarketFacade::RemoveAsset(const std::string& code)
{
    m_pMarket->RemoveAsset(code);
}

void MarketFacade::GetAssetList(std::vector<std::pair<int, std::string>> &vecAssets) const
{
    m_pMarket->GetAssetList(vecAssets);
}
