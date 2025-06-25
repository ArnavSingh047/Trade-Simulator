
# TradeSim

A simple Qt6/C++ desktop app that streams live OKX Level-2 order-book data and shows real-time trading cost estimates.

---

## Features

- **Live Data**: Connects to OKX WebSocket for L2 bids/asks  
- **Cost Metrics** (per tick):  
  - Slippage (0.2% linear)  
  - Fees (user fee tier × size)  
  - Market Impact (Almgren–Chriss model)  
  - Net Cost (sum of above)  
  - Maker/Taker Ratio (placeholder)  
  - Internal Latency (ms)  
- **UI**: Inputs on left, live outputs on right  
- **Performance**: Processes each tick in under 10 ms

---

## Quick Start

1. **Clone** this repo  
2. **Download JSON header**  

   mkdir external/nlohmann
   curl -L https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp \
     -o external/nlohmann/json.hpp


3. **Install**

   * Qt 6.9.0 (MSVC2022\_64)
   * CMake ≥ 3.16
4. **Build**


   mkdir build && cd build
   cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Qt/6.9.0/msvc2022_64"
   cmake --build . --config Release

5. **Run**


   cd Release
   TradeSim.exe

6. **Simulate**

   * Connect your VPN (required for OKX data)
   * Enter Asset, Quantity, Volatility, Fee Tier
   * Click **Start Simulation**

---

## Code Structure

```plaintext
tradeSim/
├─ CMakeLists.txt
├─ main.cpp
├─ external/nlohmann/json.hpp
└─ src/
   ├─ websocket/WSClient.{h,cpp}
   ├─ orderbook/OrderBook.{h,cpp}
   ├─ models/
   │  ├─ SlippageModel.{h,cpp}
   │  └─ AlmgrenChriss.{h,cpp}
   └─ UI/
      ├─ SimulatorUI.h
      └─ MainWindow.cpp



## Developer

* **Name:** Arnav Singh
* **Language:** C++
* **Year:** 3rd-Year ECE Student, BMS College of Engineeeing