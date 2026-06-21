#include "system_profiler_collector.h"
#include "../utils/command_runner.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace collectors {

models::HardwareInfo SystemProfilerCollector::collect() {
    std::string output = utils::run_command("system_profiler SPHardwareDataType -json 2>/dev/null");
    return parse_json_output(output);
}

models::HardwareInfo SystemProfilerCollector::parse_json_output(const std::string& json_output) {
    models::HardwareInfo info;

    if (json_output.empty()) {
        return info;
    }

    try {
        json j = json::parse(json_output);

        if (j.contains("SPHardwareDataType") && j["SPHardwareDataType"].is_array() && !j["SPHardwareDataType"].empty()) {
            const auto& hardware = j["SPHardwareDataType"][0];

            if (hardware.contains("chip_type") && hardware["chip_type"].is_string()) {
                info.chip_type = hardware["chip_type"].get<std::string>();
            }

            if (hardware.contains("machine_name") && hardware["machine_name"].is_string()) {
                info.machine_name = hardware["machine_name"].get<std::string>();
            }

            if (hardware.contains("machine_model") && hardware["machine_model"].is_string()) {
                info.machine_model = hardware["machine_model"].get<std::string>();
            }

            if (hardware.contains("model_number") && hardware["model_number"].is_string()) {
                info.model_number = hardware["model_number"].get<std::string>();
            }

            if (hardware.contains("serial_number") && hardware["serial_number"].is_string()) {
                info.serial_number = hardware["serial_number"].get<std::string>();
            }

            if (hardware.contains("physical_memory") && hardware["physical_memory"].is_string()) {
                info.physical_memory = hardware["physical_memory"].get<std::string>();
            }

            if (hardware.contains("number_processors") && hardware["number_processors"].is_string()) {
                info.number_processors = hardware["number_processors"].get<std::string>();
            }

            if (hardware.contains("boot_rom_version") && hardware["boot_rom_version"].is_string()) {
                info.boot_rom_version = hardware["boot_rom_version"].get<std::string>();
            }

            if (hardware.contains("platform_UUID") && hardware["platform_UUID"].is_string()) {
                info.platform_uuid = hardware["platform_UUID"].get<std::string>();
            }

            if (hardware.contains("activation_lock_status") && hardware["activation_lock_status"].is_string()) {
                info.activation_lock_status = hardware["activation_lock_status"].get<std::string>();
            }
        }
    } catch (const json::parse_error& e) {
        // 解析错误，返回空对象
    } catch (const json::type_error& e) {
        // 类型错误，返回空对象
    }

    return info;
}

} // namespace collectors
