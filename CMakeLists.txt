cmake_minimum_required(VERSION 3.16)
project(TradeSim)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebSockets)

# Source files
set(SOURCES
    main.cpp
    src/websocket/WSClient.cpp
    src/orderbook/OrderBook.cpp
    src/models/SlippageModel.cpp
    src/models/AlmgrenChriss.cpp
    src/UI/MainWindow.cpp
)

# Header files (for IDEs)
set(HEADERS
    src/websocket/WSClient.h
    src/orderbook/OrderBook.h
    src/models/SlippageModel.h
    src/models/AlmgrenChriss.h
    src/UI/SimulatorUI.h
)

add_executable(TradeSim ${SOURCES} ${HEADERS})

target_include_directories(TradeSim PRIVATE
    src
    external    # ensure you've placed nlohmann/json.hpp under external/nlohmann/
)

target_link_libraries(TradeSim PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebSockets
)
