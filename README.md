
# DB_Trading_Bot

A minimal C++ trading-bot scaffold using CMake, libcurl and GoogleTest (optional).

This repository provides a small example trading bot project with a CMake-based build, a header/include layout, and optional unit tests under `tests/` powered by googletest in `extern/`.

## Status

- Project: active scaffold; core source files live in `src/` and headers in `include/`.
- Build system: CMake (minimum 3.22). C++20 is required.
- Primary dependencies: libcurl (HTTP connectivity). Unit tests use googletest when `BUILD_TESTS=ON`.

## Prerequisites

- CMake >= 3.22
- A C++20-capable compiler (MSVC, clang, or GCC)
- libcurl development libraries (CMake's `find_package(CURL REQUIRED)` is used)
- Optional: vcpkg (this repo includes `vcpkg.json` and `vcpkg-configuration.json` to make dependency management easier)
- Git (to clone submodules, if you plan to use the bundled googletest)

If you use vcpkg as your package manager, run CMake from a shell with the vcpkg toolchain enabled or pass the vcpkg toolchain file to CMake.

## Quick build (PowerShell)

Open PowerShell in the repository root and run:

```powershell
mkdir build; cd build
# configure (Debug/Release is handled by --config when building on multi-config generators like MSVC)
cmake ..
# build the project (Release config shown here)
cmake --build . --config Release
```

Notes:
- Built binaries are placed under `build/bin/` (see CMakeLists.txt: CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_BINARY_DIR}/bin).
- On Windows/MSVC use the `--config` flag (Debug/Release). On single-config generators you can pass `-DCMAKE_BUILD_TYPE=Release` to the configure step.
- This project also ships `CMakePresets.json`; if you prefer presets you can use `cmake --preset <preset-name>` depending on your CMake version.

## Run

- Main executable: `build/bin/DB_Trading_Bot(.exe)`
- Tests executable (when built): `build/bin/DB_Trading_Bot_Tests(.exe)`

Run tests with CTest from the build directory or run the test executable directly:

```powershell
# from build\
ctest -C Release --output-on-failure
# or run the test exe directly
.\bin\DB_Trading_Bot_Tests.exe
```

## Configure options

- BUILD_TESTS: ON/OFF (default: ON) — controls whether unit tests are added to the build
- You can pass other options to CMake as needed. Example disabling tests when configuring:

```powershell
cmake .. -DBUILD_TESTS=OFF
```

## Project layout

- `CMakeLists.txt` — top-level CMake build script
- `include/` — public headers (project API)
- `src/` — implementation (.cpp) files
- `tests/` — unit test sources (CMake test target added when BUILD_TESTS=ON)
- `extern/` — third party submodules
- `vcpkg.json`, `vcpkg-configuration.json` — optional vcpkg manifest and configuration

## Development notes / next steps

- Wire real market connectors (REST / WebSocket clients). libcurl is available for HTTP; consider adding a websocket library if needed.
- Add a configuration system (JSON/TOML/YAML) and better logging.
- Add robust error handling and CLI options for live vs paper trading.
- Secure any API keys via environment variables or a secrets manager.

## Contributing

Ehhh really? Let me develop it to somewhat working stage first

# vcpkg tips (Windows only)

If you are using **vcpkg** on Windows and it is **not** added to your system environment variables,  
you can create a `CMakeUserPresets.json` file to help CMake locate it and define your own build presets.

Example `CMakeUserPresets.json`:

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "debug",
      "inherits": "vcpkg - debug",
      "environment": {
        "VCPKG_ROOT": "C:/vcpkg"
      }
    }
  ]
}
```

With this setup:
- **CMakePresets.json** → shared build presets (`Debug` / `Release`)
- **CMakeUserPresets.json** → personal overrides (e.g. local `vcpkg` path)
- **vcpkg-configuration.json** → locked registry & baseline for reproducible builds