#include "trading_bot.h"

#include <iostream>

TradingBot::TradingBot(std::string name) : name_(std::move(name)) {}

void TradingBot::start(std::chrono::milliseconds interval) {
  std::cout << "TradingBot '" << name_
            << "' started. (no real trading implemented)" << std::endl;

  (void)interval;  // avoid unused parameter for now
    

}

std::string TradingBot::get_name() const { return name_; }
