#include <iostream>
#include <chrono>
#include <thread>
#include "MarketFacade.h"
#include "order/Order.h"
#include "asset/Asset.h"
#include "Orderer.h"


int main()
{
    MarketFacade marketFacade;
    Orderer orderer(marketFacade);
    

    marketFacade.WakeUp();
    
    Asset asset
    {
        .id = 0,
        .code = "Alexandre Inc.",
        .price = 100.0,
        .quantity = 1000
    };
    marketFacade.AddAsset(std::move(asset));

    std::vector<std::pair<int, std::string>> vecAssets;
    marketFacade.GetAssetList(vecAssets);

    for(auto x: vecAssets)
    {
        std::cout << x.first << " " << x.second << std::endl;
    }

    Order askOrder {
        .assetId = 0,
        .volume = 10,
        .price = 101,
        .timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        .type = OrderType::LIMIT,
    };

    Order bidOrder {
        .assetId = 0,
        .volume = 5,
        .price = 102,
        .timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        .type = OrderType::LIMIT,
    };

    marketFacade.placeAskOrder(std::move(askOrder));
    marketFacade.placeBidOrder(std::move(bidOrder));

    std::this_thread::sleep_for(std::chrono::duration<double> (10000));
    return 0;
}