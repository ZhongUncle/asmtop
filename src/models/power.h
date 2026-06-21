#ifndef POWER_H
#define POWER_H

#include <string>

namespace models {

/**
 * @brief 功耗信息数据结构
 */
struct PowerInfo {
    /// CPU功耗（瓦特）
    float cpu_power = 0.0f;

    /// GPU功耗（瓦特）
    float gpu_power = 0.0f;

    /// ANE（神经网络引擎）功耗（瓦特）
    float ane_power = 0.0f;

    /// 其他部件功耗（瓦特）
    float other_power = 0.0f;

    /// 总功耗（瓦特）
    float total_power = 0.0f;

    /// 功耗限制（瓦特）
    float power_limit = 0.0f;

    /// 采样是否成功
    bool is_valid = false;

    /// 错误信息
    std::string error_message;

    /**
     * @brief 获取总功耗百分比
     * @return 0-100的百分比值
     */
    float get_total_percentage() const {
        if (power_limit <= 0) return 0.0f;
        return std::min(100.0f, (total_power / power_limit) * 100.0f);
    }

    /**
     * @brief 获取CPU功耗百分比
     * @return 0-100的百分比值
     */
    float get_cpu_percentage() const {
        if (power_limit <= 0) return 0.0f;
        return std::min(100.0f, (cpu_power / power_limit) * 100.0f);
    }

    /**
     * @brief 获取GPU功耗百分比
     * @return 0-100的百分比值
     */
    float get_gpu_percentage() const {
        if (power_limit <= 0) return 0.0f;
        return std::min(100.0f, (gpu_power / power_limit) * 100.0f);
    }

    /**
     * @brief 获取ANE功耗百分比
     * @return 0-100的百分比值
     */
    float get_ane_percentage() const {
        if (power_limit <= 0) return 0.0f;
        return std::min(100.0f, (ane_power / power_limit) * 100.0f);
    }
};

} // namespace models

#endif // POWER_H
