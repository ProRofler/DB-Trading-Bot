#pragma once

#include <atomic>
#include <chrono>
#include <string>

class trading_bot {
 public:
  trading_bot(std::string name);
  void start(std::chrono::milliseconds interval = std::chrono::seconds(1));

  std::string get_name() const;

 private:
  // methods
  static std::time_t get_current_time_and_date();

  // members
  std::string name_;
  std::atomic<bool> is_running{false};
};
