#ifndef TYPERESURE_H
#define TYPERESURE_H
#include <QString>

enum class TypeResurs {
    OperatingSystem = 0,
    ComputerSystem,
    Processor,
    PhysicalMemory,
    LogicalDisk,
    NetworkAdapter,
    Service,
    Process,
    UserAccount,
    BIOS,
    BaseBoard
};

inline QString urlResurs(TypeResurs res) {
    switch (res) {
        case TypeResurs::OperatingSystem:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_OperatingSystem";
        case TypeResurs::ComputerSystem:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_ComputerSystem";
        case TypeResurs::Processor:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_Processor";
        case TypeResurs::PhysicalMemory:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_PhysicalMemory";
        case TypeResurs::LogicalDisk:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_LogicalDisk";
        case TypeResurs::NetworkAdapter:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_NetworkAdapter";
        case TypeResurs::Service:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_Service";
        case TypeResurs::Process:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_Process";
        case TypeResurs::UserAccount:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_UserAccount";
        case TypeResurs::BIOS:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_BIOS";
        case TypeResurs::BaseBoard:
            return "http://schemas.microsoft.com/wbem/wsman/1/cimv2/Win32_BaseBoard";
        default:
            return "";
    }
}


#endif // TYPERESURE_H
