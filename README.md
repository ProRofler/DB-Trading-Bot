DB-Trading-Bot
===============

Minimal C++ trading bot scaffold using CMake.

Build (PowerShell):

```powershell
mkdir build; cd build
cmake ..
cmake --build . --config Release
# run the executable (from build): .\Release\db_trading_bot.exe or .\db_trading_bot.exe
```

Project structure:
- CMakeLists.txt - project build
- include/ - public headers
- src/ - implementation

Next steps:
- Wire real market connectors
- Add logging, configuration, and tests
