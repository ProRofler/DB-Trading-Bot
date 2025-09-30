#pragma once
#include "brokers.h"

#include <atomic>
#include <chrono>
#include <string>

class trading_bot {
   public:
    constexpr trading_bot(std::string name, const broker broker_type)
        : name_(std::move(name)), broker_type_(broker_type) {};
    ~trading_bot() = default;

    void start(std::chrono::milliseconds interval = std::chrono::seconds(1),
               const broker broker_type = broker::yahoo);

    std::string get_name() const;

   private:
    // methods
    static std::string get_current_time_and_date();

    // members
    std::string name_;
    std::atomic<bool> is_running{false};

    // yahoo is default, not a broker just a demo
    broker broker_type_;
};
