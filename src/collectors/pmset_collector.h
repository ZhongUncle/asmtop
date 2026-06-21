#ifndef PMSET_COLLECTOR_H
#define PMSET_COLLECTOR_H

#include "base_collector.h"
#include "../models/battery.h"
#include <string>

namespace collectors {

class PmsetCollector : public BaseCollector<models::BatteryInfo> {
public:
    /**
     * @brief 采集电池信息
     * @return 结构化的电池信息
     */
    models::BatteryInfo collect() override;

private:
    /**
     * @brief 解析pmset -g batt的输出
     * @param output pmset命令的输出
     * @return 结构化的电池信息
     */
    models::BatteryInfo parse_batt_output(const std::string& output);
};

} // namespace collectors

#endif // PMSET_COLLECTOR_H
