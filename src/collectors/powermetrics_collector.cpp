#include "powermetrics_collector.h"
#include "../utils/command_runner.h"
#include "../utils/permission.h"
#include <regex>
#include <string>
#include <sstream>
#include <iostream>

namespace collectors {

PowermetricsCollector::PowermetricsCollector(int sample_duration)
    : sample_duration_(sample_duration) {}

models::PowerInfo PowermetricsCollector::collect() {
    models::PowerInfo info;

    // 检查是否有root权限
    if (!utils::has_root_permission()) {
        info.is_valid = false;
        info.error_message = "powermetrics需要root权限才能运行";
        return info;
    }

    // 检查是否是Apple Silicon架构
    if (!utils::is_apple_silicon()) {
        info.is_valid = false;
        info.error_message = "powermetrics功耗采集仅支持Apple Silicon架构";
        return info;
    }

    try {
        // 构建powermetrics命令，采样指定时间，启用功耗相关采样器
        std::string command = "powermetrics --sample-rate " + std::to_string(sample_duration_) +
                             " --sample-count 1 --samplers cpu_power,gpu_power,ane_power 2>&1";

        std::string output = utils::run_command(command);

        if (output.empty()) {
            info.is_valid = false;
            info.error_message = "powermetrics命令执行失败，无输出";
            return info;
        }

        return parse_powermetrics_output(output);
    } catch (const std::exception& e) {
        info.is_valid = false;
        info.error_message = "执行powermetrics命令失败: " + std::string(e.what());
        return info;
    }
}

float PowermetricsCollector::extract_float_value(const std::string& line, const std::string& keyword) {
    size_t pos = line.find(keyword);
    if (pos == std::string::npos) {
        return 0.0f;
    }

    // 查找数字部分，支持小数和负号
    size_t num_start = pos + keyword.length();
    while (num_start < line.length() && !isdigit(line[num_start]) && line[num_start] != '.' && line[num_start] != '-') {
        num_start++;
    }

    if (num_start >= line.length()) {
        return 0.0f;
    }

    size_t num_end = num_start;
    while (num_end < line.length() && (isdigit(line[num_end]) || line[num_end] == '.')) {
        num_end++;
    }

    try {
        float value = std::stof(line.substr(num_start, num_end - num_start));

        // 检查单位，如果是mW（毫瓦），转换为W（瓦特）
        if (line.find("mW", num_end) != std::string::npos) {
            value /= 1000.0f;
        }

        return value;
    } catch (...) {
        return 0.0f;
    }
}

models::PowerInfo PowermetricsCollector::parse_powermetrics_output(const std::string& output) {
    models::PowerInfo info;
    info.is_valid = true;

    std::istringstream iss(output);
    std::string line;

    // Apple Silicon的powermetrics输出中，功耗相关的行格式：
    // CPU Power: 1234 mW
    // GPU Power: 567 mW
    // ANE Power: 0 mW
    // 或者使用瓦特单位
    // 也可能包含Combined Power、Package Power等总功耗字段

    while (std::getline(iss, line)) {
        // 提取CPU功耗
        if (line.find("CPU Power:") != std::string::npos) {
            info.cpu_power = extract_float_value(line, "Power:");
        }
        // 提取GPU功耗
        else if (line.find("GPU Power:") != std::string::npos) {
            info.gpu_power = extract_float_value(line, "Power:");
        }
        // 提取ANE功耗
        else if (line.find("ANE Power:") != std::string::npos) {
            info.ane_power = extract_float_value(line, "Power:");
        }
        // 提取总功耗（各种可能的字段名）
        else if (line.find("Total Power:") != std::string::npos ||
                 line.find("Combined Power:") != std::string::npos ||
                 line.find("Package Power:") != std::string::npos ||
                 line.find("SoC Power:") != std::string::npos) {
            info.total_power = extract_float_value(line, "Power:");
        }
        // 提取功耗限制
        else if (line.find("Power Limit:") != std::string::npos ||
                 line.find("TDP:") != std::string::npos) {
            info.power_limit = extract_float_value(line, "Limit:");
        }
    }

    // 如果总功耗为0但各部分功耗之和不为0，计算总功耗
    if (info.total_power <= 0 && (info.cpu_power > 0 || info.gpu_power > 0 || info.ane_power > 0)) {
        info.total_power = info.cpu_power + info.gpu_power + info.ane_power + info.other_power;
    }

    // 如果没有检测到功耗限制，根据芯片型号设置合理的默认值
    // M系列芯片典型功耗限制：M1-15W, M2-20W, M3-25W, M4/M5-30W
    if (info.power_limit <= 0) {
        std::string arch = utils::get_architecture();
        if (arch.find("M1") != std::string::npos) {
            info.power_limit = 15.0f;
        } else if (arch.find("M2") != std::string::npos) {
            info.power_limit = 20.0f;
        } else if (arch.find("M3") != std::string::npos) {
            info.power_limit = 25.0f;
        } else { // M4/M5及以上
            info.power_limit = 30.0f;
        }
    }

    // 验证数据合理性
    if (info.total_power <= 0 && info.cpu_power <= 0 && info.gpu_power <= 0 && info.ane_power <= 0) {
        info.is_valid = false;
        info.error_message = "未能解析到有效的功耗数据，请确认powermetrics命令输出格式";
    }

    return info;
}

} // namespace collectors
