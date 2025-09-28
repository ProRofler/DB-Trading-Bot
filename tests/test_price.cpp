#include <gtest/gtest.h>

#include <string>

#include "price_handler.h"

TEST(Price, notError) {
  EXPECT_TRUE(price_handler::get().get_current_price() != "Error");
}
