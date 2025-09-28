#include "trading_bot.h"

#include <csignal>
#include <format>
#include <iostream>
#include <thread>

#include "price_handler.h"

static std::atomic<bool> g_interrupted{false};

static void signal_handler(int) {
  std::cout << "User aborted" << std::endl;
  g_interrupted.store(true);
}

trading_bot::trading_bot(std::string name) : name_(std::move(name)) {}

void trading_bot::start(std::chrono::milliseconds interval) {
  if (is_running.exchange(true)) return;  // already running

  std::cout << "TradingBot '" << name_
            << "' started. (no real trading implemented)" << std::endl;

  is_running = true;

  std::signal(SIGINT, signal_handler);

  while (is_running.load() && !g_interrupted.load()) {
    std::cout << trading_bot::get_current_time_and_date()
              << " -- bot is working" << std::endl;

    std::cout << "Current SPY price: " << price_handler::get().get_current_price()
              << std::endl;

    std::this_thread::sleep_for(interval);
  }

  price_handler::get().stop();
}

std::string trading_bot::get_name() const { return name_; }

// static
std::string trading_bot::get_current_time_and_date() {
  auto time = std::chrono::floor<std::chrono::seconds>(
      std::chrono::system_clock::now());

  return std::format("{:%Y-%m-%d %H:%M:%S}", time);
}
