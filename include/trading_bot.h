#pragma once

#include <string>
#include <atomic>
#include <chrono>

class TradingBot {
public:
    TradingBot(std::string name = "DB-trader");
    void start(std::chrono::milliseconds interval = std::chrono::seconds(1));
    
    std::string get_name() const;
private:
    std::string name_;
};
