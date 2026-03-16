#include "asset/Asset.h"
#include <map>

class Market 
{
    private:
    std::map<std::string, Asset> assets;

    public:
    void WakeUp();
    void Sleep();

    void AddAsset(Asset&& asset);
    void RemoveAsset(const std::string& code);

    


};