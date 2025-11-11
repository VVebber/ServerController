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

    src/Common.h            src/Common.cpp
    src/Logs/Log.h          src/Logs/Log.cpp
    src/AgrParser.h         src/AgrParser.cpp
    src/Application.h       src/Application.cpp
    src/AppVariables.h      src/AppVariables.cpp

    src/Tasks/TaskManager.h           src/Tasks/TaskManager.cpp
    src/Tasks/ConsoleCommand.h        src/Tasks/ConsoleCommand.cpp
    src/Tasks/CommandController.h     src/Tasks/CommandController.cpp

    src/Network/NetworkSkan.h                  src/Network/NetworkSkan.cpp
    src/Network/Workers/PingWorker.h           src/Network/Workers/PingWorker.cpp
    src/Network/Workers/IScanWorker.h          src/Network/Workers/IScanWorker.cpp

    src/Network/Protocol/RawSocket.h           src/Network/Protocol/RawSocket.cpp
    src/Network/Protocol/LLDP/LLDP.h           src/Network/Protocol/LLDP/LLDP.cpp
    src/Network/Protocol/ARP/ARP_Ping.h        src/Network/Protocol/ARP/ARP_Ping.cpp
    src/Network/Protocol/ICMP/CheckPing.h      src/Network/Protocol/ICMP/CheckPing.cpp
    src/Network/Protocol/NetFlow/NetFlow.h     src/Network/Protocol/NetFlow/NetFlow.cpp
    src/Network/Protocol/WinRM/WinRM.h         src/Network/Protocol/WinRM/WinRM.cpp

    src/HTTPServer/Request.h
    src/HTTPServer/NetWorker.h src/HTTPServer/NetWorker.cpp   
    src/HTTPServer/CommandHandlers/HandlersFactory.h src/HTTPServer/CommandHandlers/HandlersFactory.cpp

    src/Models/DeviceInfo.h  src/Models/DeviceInfo.cpp
    src/Models/NetAdapter.h  src/Models/NetAdapter.cpp

    src/Common/JsonBuilder.h src/Common/JsonBuilder.cpp
    src/Network/Protocol/WinRM/TypeResure.h
    src/Network/Workers/WinRMWorker.h src/Network/Workers/WinRMWorker.cpp
)

target_include_directories(ServerController PRIVATE
    /usr/include/openwsman
    /usr/include/net-snmp
)

target_link_libraries(ServerController
    PRIVATE
    Qt::Core
    Qt::Network
    wsman_clientpp   # OpenWSMAN C++ клиент
    wsman            # OpenWSMAN
    snmp             # Net-SNMP
)
