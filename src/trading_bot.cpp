#include "trading_bot.h"
#include <iostream>

TradingBot::TradingBot(std::string name) : name_(std::move(name)) {}

void TradingBot::start() {
    std::cout << "TradingBot '" << name_ << "' started. (no real trading implemented)" << std::endl;
}

std::string TradingBot::name() const { return name_; }
