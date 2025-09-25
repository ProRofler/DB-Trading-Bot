#pragma once

#include <atomic>
#include <chrono>
#include <string>

class TradingBot {
 public:
  TradingBot(std::string name);
  void start(std::chrono::milliseconds interval = std::chrono::seconds(1));

  std::string get_name() const;

 private:
  std::string name_;

  std::atomic<bool> is_running{false};
};
