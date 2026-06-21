#include "pmset_collector.h"
#include "../utils/command_runner.h"
#include <regex>
#include <string>

namespace collectors {

models::BatteryInfo PmsetCollector::collect() {
    std::string output = utils::run_command("pmset -g batt 2>/dev/null");
    return parse_batt_output(output);
}

models::BatteryInfo PmsetCollector::parse_batt_output(const std::string& output) {
    models::BatteryInfo info;

    if (output.empty()) {
        return info;
    }

    // 解析电源类型
    if (output.find("AC Power") != std::string::npos) {
        info.power_source = models::PowerSource::AC_POWER;
    } else if (output.find("Battery Power") != std::string::npos) {
        info.power_source = models::PowerSource::BATTERY_POWER;
    }

    // 解析电池状态行
    std::regex batt_regex(R"((\d+)%;.*?(charging|discharging|not charging|charged|fully charged))");
    std::smatch match;

    if (std::regex_search(output, match, batt_regex)) {
        // 电量百分比
        if (match.size() > 1) {
            info.percentage = std::stoi(match[1].str());
        }

        // 充电状态
        if (match.size() > 2) {
            std::string state = match[2].str();
            if (state == "charging") {
                info.charging_state = models::ChargingState::CHARGING;
            } else if (state == "discharging") {
                info.charging_state = models::ChargingState::DISCHARGING;
            } else if (state == "not charging") {
                info.charging_state = models::ChargingState::NOT_CHARGING;
            } else if (state == "charged" || state == "fully charged") {
                info.charging_state = models::ChargingState::FULLY_CHARGED;
            }
        }
    }

    // 解析剩余时间
    std::regex time_regex(R"((\d+:\d+|remaining|no estimate))");
    if (std::regex_search(output, match, time_regex)) {
        info.remaining_time = match[1].str();
    }

    // 电池存在
    info.is_present = output.find("InternalBattery") != std::string::npos;

    return info;
}

} // namespace collectors
