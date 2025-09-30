#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "brokers.h"


class price_handler {
 public:
  static double get_current_price();
  static const price_handler& get();
  static void stop();

  price_handler(const price_handler& other) = delete;
  price_handler& operator=(const price_handler& other) = delete;

 private:
  double price = 0.;

 private:
  price_handler();
  ~price_handler();
  void fetch_price();

  mutable std::atomic<bool> is_active = true;
  std::mutex mtx;
  std::thread t_1;
};