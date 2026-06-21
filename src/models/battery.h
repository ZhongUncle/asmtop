#ifndef BATTERY_H
#define BATTERY_H

#include <string>

namespace models {

enum class PowerSource {
    AC_POWER,
    BATTERY_POWER,
    UNKNOWN
};

enum class ChargingState {
    CHARGING,
    DISCHARGING,
    NOT_CHARGING,
    FULLY_CHARGED,
    UNKNOWN
};

struct BatteryInfo {
    int percentage = 0; // 电量百分比 0-100
    PowerSource power_source = PowerSource::UNKNOWN;
    ChargingState charging_state = ChargingState::UNKNOWN;
    std::string remaining_time; // 剩余时间字符串
    bool is_present = false; // 电池是否存在

    // 辅助方法
    std::string power_source_str() const {
        switch (power_source) {
            case PowerSource::AC_POWER: return "AC电源";
            case PowerSource::BATTERY_POWER: return "电池供电";
            default: return "未知";
        }
    }

    std::string charging_state_str() const {
        switch (charging_state) {
            case ChargingState::CHARGING: return "充电中";
            case ChargingState::DISCHARGING: return "放电中";
            case ChargingState::NOT_CHARGING: return "未充电";
            case ChargingState::FULLY_CHARGED: return "已充满";
            default: return "未知";
        }
    }
};

} // namespace models

#endif // BATTERY_H
