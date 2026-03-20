#include "asset/Asset.h"
#include "order/OrderBook.h"
#include <thread>
#include <map>
#include <vector>


/**
 * Gestion des actifs présents sur le marché, 
 * gestion du thread d'exécution des ordres,
 * et interface pour accéder au carnet d'ordres.
 */
class Market 
{
    private:
    std::map<std::string, Asset> assets;
    std::thread marketThread;

    bool m_bMustSleep;

    OrderBook orderBook;

    public:
    Market();

    /**
     * Démarre le thread de marché qui exécute les ordres en continu.
     */
    void WakeUp();

    /**
     * Met en pause le thread qui exécute les ordres
     */
    void Sleep();

    /**
     * Ajoute un actif au marché ou le met à jour s'il existe déjà.
     */
    void AddAsset(Asset&& asset);

    /**
     * Supprime un actif du marché en fonction de son code.
     */
    void RemoveAsset(const std::string& code);

    /**
     * Retourne une référence au carnet d'ordres pour permettre la gestion des ordres.
     */
    OrderBook& GetOrderBook();


    /**
     * Renvoie la liste des Assets
     */
    void GetAssetList(std::vector<std::pair<int, std::string>>& vecAssets) const;
};