#ifndef POWERMETRICS_COLLECTOR_H
#define POWERMETRICS_COLLECTOR_H

#include "base_collector.h"
#include "../models/power.h"
#include <string>

namespace collectors {

class PowermetricsCollector : public BaseCollector<models::PowerInfo> {
public:
    /**
     * @brief 采集功耗信息
     * @return 结构化的功耗信息
     */
    models::PowerInfo collect() override;

    /**
     * @brief 构造函数
     * @param sample_duration 采样持续时间（毫秒），默认100ms
     */
    explicit PowermetricsCollector(int sample_duration = 100);

private:
    /// 采样持续时间（毫秒）
    int sample_duration_;

    /**
     * @brief 解析powermetrics的输出
     * @param output powermetrics命令的输出
     * @return 结构化的功耗信息
     */
    models::PowerInfo parse_powermetrics_output(const std::string& output);

    /**
     * @brief 从字符串中提取浮点数值
     * @param line 包含数值的字符串行
     * @param keyword 关键词，用于定位数值
     * @return 提取到的浮点值，失败返回0.0
     */
    float extract_float_value(const std::string& line, const std::string& keyword);
};

} // namespace collectors

#endif // POWERMETRICS_COLLECTOR_H
