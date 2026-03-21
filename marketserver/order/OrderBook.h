#pragma once

#include <chrono>
#include <set>
#include <mutex>
#include <list>

#include "Order.h"
#include "../Orderer.h"



struct OrderHistoryEntry
{
    Order order;
    time_t executionTime;
};


/**
 * Gestion des ordres d'achat et de vente. 
 * Les ordres exécutés se retrouvent dans m_setOrderHistory pour garder une trace de l'historique des transactions
 * Une fois l'ordre exécuté, son propriétaire peut être notifié pour mettre à jour son portefeuille et son historique de transactions
 * (design pattern observateur)
 * 
 */
class OrderBook 
{
    private:
        std::set < Order > m_setBidOrders;
        std::set < Order > m_setAskOrders;
        std::set<OrderHistoryEntry> m_setOrderHistory;
        std::mutex m_mutOrderBook;
        std::list<std::shared_ptr<Orderer>> m_lstOrderers;
    public:
        void AddBidOrder(Order&& order);
        void AddAskOrder(Order&& order);
        void RemoveBidOrder(int orderId);
        void RemoveAskOrder(int orderId);
        void ExecuteOrders();

        void Attach(std::shared_ptr<Orderer> orderer);
        void Detach(std::shared_ptr<Orderer> orderer);
};