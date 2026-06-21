#!/usr/bin/env python3
"""
Mac Monitor 使用示例
展示如何使用各个采集器获取系统数据
"""
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "src"))

from mac_monitor.collectors import (
    PmsetBattCollector,
    PmsetAcCollector,
    PmsetStatsCollector,
    SystemProfilerHardwareCollector,
    SystemProfilerPowerCollector,
    SystemProfilerSoftwareCollector
)
from mac_monitor.utils import is_apple_silicon


def main():
    print("=" * 70)
    print("🍎 Mac Monitor 使用示例")
    print("=" * 70)

    # 检查架构
    if not is_apple_silicon():
        print("❌ 本工具仅支持Apple Silicon架构Mac")
        return 1

    print(f"✅ 架构检查通过: Apple Silicon")
    print()

    # 1. 采集基础硬件信息
    print("📱 硬件信息:")
    hw_collector = SystemProfilerHardwareCollector()
    hw_data = hw_collector.collect()
    print(f"   设备型号: {hw_data.machine_name}")
    print(f"   芯片类型: {hw_data.chip_type}")
    print(f"   内存大小: {hw_data.physical_memory}")
    print(f"   系统版本: {SystemProfilerSoftwareCollector().collect().os_version}")
    print()

    # 2. 采集电源和电池信息
    print("🔋 电池信息:")
    batt_collector = PmsetBattCollector()
    batt_data = batt_collector.collect()
    print(f"   当前电量: {batt_data.battery_percent}%")
    print(f"   电源类型: {batt_data.power_source.strip()}")
    print(f"   AC连接: {'是' if batt_data.ac_attached else '否'}")
    print(f"   充电状态: {batt_data.charging_state}")

    power_collector = SystemProfilerPowerCollector()
    power_data = power_collector.collect()
    if power_data.battery_health_info:
        health = power_data.battery_health_info
        print(f"   循环次数: {health.sppower_battery_cycle_count} 次")
        print(f"   健康状态: {health.sppower_battery_health}")
        print(f"   最大容量: {health.sppower_battery_health_maximum_capacity}")
    print()

    # 3. 采集适配器信息
    print("🔌 电源适配器信息:")
    ac_collector = PmsetAcCollector()
    ac_data = ac_collector.collect()
    if ac_data.wattage:
        print(f"   适配器功率: {ac_data.wattage}W")
    if ac_data.manufacturer:
        print(f"   制造商: {ac_data.manufacturer}")
    if ac_data.serial_number:
        print(f"   序列号: {ac_data.serial_number}")
    print()

    # 4. 采集系统统计信息
    print("📊 系统统计:")
    stats_collector = PmsetStatsCollector()
    stats_data = stats_collector.collect()
    print(f"   睡眠次数: {stats_data.sleep_count} 次")
    print(f"   黑暗唤醒: {stats_data.dark_wake_count} 次")
    print(f"   用户唤醒: {stats_data.user_wake_count} 次")
    print()

    # 5. 导出为JSON示例
    print("💾 数据导出示例 (电池数据JSON):")
    print("-" * 50)
    print(batt_data.to_json(indent=2))
    print("-" * 50)

    print("\n🎉 所有采集功能正常工作！")
    return 0


if __name__ == "__main__":
    sys.exit(main())
