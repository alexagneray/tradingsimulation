#pragma once

enum class OrderType
{
    MARKET,
    LIMIT
};

enum class OrderDir
{
    BID,
    ASK
};


struct Order
{
    int id;
    int assetId;
    int volume;
    double price;
    time_t timestamp;
    OrderType type;

    bool operator<(const Order& other) const
    {
        if (price == other.price) {
            return timestamp < other.timestamp; // FIFO for same price
        }
        return price > other.price; // Higher price has priority
    }
};