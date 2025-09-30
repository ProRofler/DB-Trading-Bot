#include "price_handler.h"

#include <curl/curl.h>

#include <chrono>

#include "brokers.h"

namespace curl {

static size_t write_callback(void* contents, size_t size, size_t nmemb,
                             void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

double extract_price(const std::string& json) {
  const std::string key = "\"regularMarketPrice\":";
  auto pos = json.find(key);
  if (pos == std::string::npos) return -1;

  pos += key.size();
  // skip spaces
  while (pos < json.size() && isspace(json[pos])) ++pos;

  // read number
  size_t end = pos;
  while (end < json.size() && (isdigit(json[end]) || json[end] == '.')) ++end;

  return std::stod(json.substr(pos, end - pos));
}

double request_yahoo() {
  CURL* curl;
  CURLcode res;
  std::string read_buffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(
        curl, CURLOPT_URL,
        "https://query1.finance.yahoo.com/v8/finance/chart/SPY?interval=1m");

    // Pretend to be a real browser
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers,
                                "User-Agent: Mozilla/5.0 (Windows NT 10.0; "
                                "Win64; x64) AppleWebKit/537.36 (KHTML, like "
                                "Gecko) Chrome/120.0.0.0 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

    res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  double current_price = extract_price(read_buffer);

  return current_price;
}

}  // namespace curl

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

double price_handler::get_current_price() { return get().price; }

void price_handler::fetch_price() {
  while (is_active.load()) {
    mtx.lock();
    price = curl::request_yahoo();
    mtx.unlock();

    std::this_thread::sleep_for(std::chrono::minutes(1));  // sleep for one min
  }
}