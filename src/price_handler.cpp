#include "price_handler.h"

#include <curl/curl.h>

#include <chrono>

// **********************curl related
static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                            void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

std::string curl_test() {
  CURL* curl = curl_easy_init();
  std::string read_buffer;

  if (curl) {
    curl_easy_setopt(
        curl, CURLOPT_URL,
        "https://query1.finance.yahoo.com/v8/finance/chart/SPY?interval=1m");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }

  return read_buffer;
}

// **********************

price_handler::price_handler() {
  t_1 = std::thread(&price_handler::fetch_price, this);
}

price_handler::~price_handler() {
  if (t_1.joinable()) t_1.join();
}

const price_handler& price_handler::get() {
  static price_handler instance;
  return instance;
}

void price_handler::stop() { get().is_active.exchange(false); }

std::string price_handler::get_current_price() { return get().price; }

void price_handler::fetch_price() {
  while (is_active.load()) {
    mtx.lock();
    price = curl_test();
    mtx.unlock();

    std::this_thread::sleep_for(std::chrono::minutes(1));  // sleep for one min
  }
}