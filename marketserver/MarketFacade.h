#include <memory>
#include <vector>
#include <string>

class Market;
struct Order;
struct Asset;

class MarketFacade
{
private:
    std::unique_ptr<Market> m_pMarket;
public:
    MarketFacade();
    ~MarketFacade();

    void WakeUp();
    void Sleep();
    void placeAskOrder(Order&& order);
    void cancelAskOrder(int orderId);
    void placeBidOrder(Order&& order);
    void cancelBidOrder(int orderId);
    void modifyOrder(int orderId, Order&& newOrder);
    void AddAsset(Asset&& asset);
    void RemoveAsset(const std::string& code);
    void GetAssetList(std::vector<std::pair<int, std::string>>& vecAssets) const;
    void Attach(std::shared_ptr<>);
};