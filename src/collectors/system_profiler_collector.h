#ifndef SYSTEM_PROFILER_COLLECTOR_H
#define SYSTEM_PROFILER_COLLECTOR_H

#include "base_collector.h"
#include "../models/hardware.h"
#include <string>

namespace collectors {

class SystemProfilerCollector : public BaseCollector<models::HardwareInfo> {
public:
    /**
     * @brief 采集硬件信息
     * @return 结构化的硬件信息
     */
    models::HardwareInfo collect() override;

private:
    /**
     * @brief 解析system_profiler的JSON输出
     * @param json_output system_profiler命令的JSON输出
     * @return 结构化的硬件信息
     */
    models::HardwareInfo parse_json_output(const std::string& json_output);
};

} // namespace collectors

#endif // SYSTEM_PROFILER_COLLECTOR_H
