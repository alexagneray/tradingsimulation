project(TradingSimulation)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build: Enabling verbose mode")
    add_compile_definitions(VERBOSE_MODE)
endif()



add_subdirectory(marketserver)