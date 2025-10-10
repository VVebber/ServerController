cmake_minimum_required(VERSION 3.19)

project(ServerController VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network)

add_executable(ServerController
    src/main.cpp
    src/Common.h src/Common.cpp
    src/Logs/Log.h src/Logs/Log.cpp
    src/Application.h src/Application.cpp
    src/AppVariables.h src/AppVariables.cpp

    src/Tasks/TaskManager.h src/Tasks/TaskManager.cpp
    src/Tasks/NetworkSkan.h src/Tasks/NetworkSkan.cpp

    src/Tasks/ConsoleCommand.h src/Tasks/ConsoleCommand.cpp


    src/Network/Protocol/RawSocket.h     src/Network/Protocol/RawSocket.cpp
    src/Network/Protocol/ICMP/ICMP.h     src/Network/Protocol/ICMP/ICMP.cpp
    src/Network/Protocol/ARP/ARP.h       src/Network/Protocol/ARP/ARP.cpp
    src/Network/Protocol/LLDP/LLDP.h src/Network/Protocol/LLDP/LLDP.cpp


    src/HTTPServer/NetWorker.h src/HTTPServer/NetWorker.cpp
    src/HTTPServer/CommandHandlers/HandlersFactory.h src/HTTPServer/CommandHandlers/HandlersFactory.cpp
    Проблемы_1
    src/AgrParser.h src/AgrParser.cpp

)

target_link_libraries(ServerController
    PRIVATE
    Qt::Core
    Qt::Network
)
