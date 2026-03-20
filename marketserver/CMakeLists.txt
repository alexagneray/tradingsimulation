add_library(market Market.cpp order/OrderBook.cpp MarketFacade.cpp)

add_executable(marketserver marketserver.cpp Orderer.cpp)
target_link_libraries(marketserver market)
