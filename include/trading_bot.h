#pragma once

#include <string>

class TradingBot {
public:
    TradingBot(std::string name);
    void start();
    std::string name() const;
private:
    std::string name_;
};
