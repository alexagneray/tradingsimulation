#include "Market.h"

#ifdef VERBOSE_MODE
#include <iostream>
#endif

Market::Market():
    m_bMustSleep(false)
{
}

void Market::WakeUp()
{
    m_thdMarket = std::thread([this]() {
        while (true) {
            m_orderBook.ExecuteOrders();

            #ifdef VERBOSE_MODE
                std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
            #else
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            #endif
            
            
            if(m_bMustSleep)
            {
                break;
            }
        }
    });

    #ifdef VERBOSE_MODE
        std::cout << "The market has now woken up !" << std::endl;
    #endif
}

void Market::Sleep()
{
    if (m_thdMarket.joinable()) {
        m_bMustSleep = true;
        m_thdMarket.join();
    }
    #ifdef VERBOSE_MODE
        std::cout << "The market is now sleeping !" << std::endl;
    #endif
}
OrderBook &Market::GetOrderBook()
{
    return m_orderBook;   
}

void Market::GetAssetList(std::vector<std::pair<int, std::string>>& vecAssets) const
{
    for(const auto& asset: m_mapAssets)
    {
        vecAssets.push_back(std::make_pair(asset.second.id, asset.first));
    }
}


void Market::AddAsset(Asset&& asset)
{
    #ifdef VERBOSE_MODE
        std::cout << "Ajout de l'actif " << asset.code << std::endl;
    #endif
    m_mapAssets.emplace(asset.code,std::move(asset));
}


void Market::RemoveAsset(const std::string& code)
{
    std::size_t count = m_mapAssets.erase(code);

    #ifdef VERBOSE_MODE
        if(count)
        {
            std::cout << "L'actif de code " << code << " a bien été supprimé !";
        }
        else
        {
            std::cout << "L'actif de code " << code << " n'existe pas !";
        }
    #endif
    
}