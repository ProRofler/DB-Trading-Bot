#include "trading_bot.h"

#include <curl/curl.h>

#include <csignal>
#include <format>
#include <iostream>
#include <thread>

static std::atomic<bool> g_interrupted{false};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                            void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void curl_test() {
  CURL* curl = curl_easy_init();
  std::string readBuffer;

  if (curl) {
    curl_easy_setopt(
        curl, CURLOPT_URL,
        "https://query1.finance.yahoo.com/v8/finance/chart/SPY?interval=1m");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << "Response: " << readBuffer << std::endl;
  }
}

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
    curl_test();

    std::this_thread::sleep_for(interval);
  }
}

std::string trading_bot::get_name() const { return name_; }

// static
std::string trading_bot::get_current_time_and_date() {
  auto time = std::chrono::floor<std::chrono::seconds>(
      std::chrono::system_clock::now());

  return std::format("{:%Y-%m-%d %H:%M:%S}", time);
}
