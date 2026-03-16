#include <chrono>
#include <set>

enum class OrderType
{
    MARKET,
    LIMIT
};
struct Order
{
    int id;
    int assetId;
    int volume;
    double price;
    time_t timestamp;
    OrderType type;

};

class OrderBook 
{
    private:
        std::set < Order > bidOrders;
        std::set < Order > askOrders;
    public:
        void AddBidOrder(Order&& order);
        void AddAskOrder(Order&& order);
        void RemoveBidOrder(int orderId);
        void RemoveAskOrder(int orderId);
        void ExecuteOrders();
};