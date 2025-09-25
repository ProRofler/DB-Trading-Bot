#include "trading_bot.h"

#include <csignal>
#include <iostream>
#include <thread>

static std::atomic<bool> g_interrupted{false};

static void signal_handler(int) { g_interrupted.store(true); }

TradingBot::TradingBot(std::string name) : name_(std::move(name)) {}

void TradingBot::start(std::chrono::milliseconds interval) {
  if (is_running.exchange(true)) return;  // already running

  std::cout << "TradingBot '" << name_
            << "' started. (no real trading implemented)" << std::endl;

  is_running = true;

  std::signal(SIGINT, signal_handler);

  while (is_running.load() && !g_interrupted.load()) {
    std::cout << "bot is working" << std::endl;
    std::this_thread::sleep_for(interval);
  }
}

std::string TradingBot::get_name() const { return name_; }
