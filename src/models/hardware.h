#ifndef HARDWARE_H
#define HARDWARE_H

#include <string>

namespace models {

struct HardwareInfo {
    std::string chip_type;        // 芯片型号，如"Apple M5"
    std::string machine_name;     // 机器名称，如"MacBook Air"
    std::string machine_model;    // 机器型号，如"Mac17,3"
    std::string model_number;     // 型号编号，如"MDH74CH/A"
    std::string serial_number;    // 序列号
    std::string physical_memory;  // 物理内存，如"16 GB"
    std::string number_processors;// 处理器信息，如"proc 10:4:6:0"
    std::string boot_rom_version; // Boot ROM版本
    std::string platform_uuid;    // 平台UUID
    std::string activation_lock_status; // 激活锁状态

    // 辅助方法：解析处理器核心数
    int get_performance_cores() const {
        if (number_processors.empty()) return 0;
        size_t first_colon = number_processors.find(':');
        size_t second_colon = number_processors.find(':', first_colon + 1);
        if (first_colon != std::string::npos && second_colon != std::string::npos) {
            try {
                return std::stoi(number_processors.substr(first_colon + 1, second_colon - first_colon - 1));
            } catch (...) {}
        }
        return 0;
    }

    int get_efficiency_cores() const {
        if (number_processors.empty()) return 0;
        size_t first_colon = number_processors.find(':');
        size_t second_colon = number_processors.find(':', first_colon + 1);
        size_t third_colon = number_processors.find(':', second_colon + 1);
        if (second_colon != std::string::npos && third_colon != std::string::npos) {
            try {
                return std::stoi(number_processors.substr(second_colon + 1, third_colon - second_colon - 1));
            } catch (...) {}
        }
        return 0;
    }

    int get_total_cores() const {
        return get_performance_cores() + get_efficiency_cores();
    }
};

} // namespace models

#endif // HARDWARE_H
