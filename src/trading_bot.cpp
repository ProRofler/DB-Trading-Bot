#include "trading_bot.h"
#include "price_handler.h"

#include <csignal>
#include <format>
#include <iostream>
#include <thread>

namespace utils {

static std::atomic<bool> g_interrupted{false};

static void signal_handler(int) {
    g_interrupted.store(true);
    price_handler::get().stop();
    std::cout << "User aborted" << std::endl;
}

inline static std::string format_price(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}
}  // namespace utils

void trading_bot::start(std::chrono::milliseconds interval,
                        [[maybe_unused]] const broker broker_type) {
    if (is_running.exchange(true)) return;  // already running
    is_running.store(true);

    std::cout
        << "*****************************************************************\n"
        << "TradingBot '" << name_ << "' started. (no real trading implemented)"
        << "\n*****************************************************************"
        << std::endl;

    std::signal(SIGINT, utils::signal_handler);

    while (is_running.load() && !utils::g_interrupted.load()) {
        double price = price_handler::get().get_current_price();
        std::cout << "\r" << trading_bot::get_current_time_and_date() << " -- "
                  << "Current SPY price: "
                  << (price == 0.0 ? "N/A" : utils::format_price(price))
                  << "     "  // overwrite leftovers with spaces
                  << std::flush;

        std::this_thread::sleep_for(interval);
    }
    std::cout << "Program loop end" << std::endl;
}

std::string trading_bot::get_name() const { return name_; }

// static
std::string trading_bot::get_current_time_and_date() {
    auto time = std::chrono::floor<std::chrono::seconds>(
        std::chrono::system_clock::now());

    return std::format("{:%Y-%m-%d %H:%M:%S}", time);
}
