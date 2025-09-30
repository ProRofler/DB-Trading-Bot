#include "trading_bot.h"

int main() {
  trading_bot bot("DB-Trader", broker::exante);
  bot.start();
  return 0;
}
