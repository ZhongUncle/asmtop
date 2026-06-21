#include "hardware_page.h"
#include <ftxui/dom/elements.hpp>
#include <string>

using namespace ftxui;

namespace ui::pages {

HardwarePage::HardwarePage() {
    // 初始化时采集一次数据
    refresh();

    // 创建组件
    component_ = Renderer([&] { return render(); });
}

Component HardwarePage::get_component() {
    return component_;
}

void HardwarePage::refresh() {
    hardware_info_ = system_profiler_collector_.collect();
}

std::string HardwarePage::get_name() const {
    return "硬件信息";
}

Element HardwarePage::render() {
    // 构建信息表格
    auto table = vbox({
        hbox({
            text("设备名称：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.machine_name.empty() ? "未知" : hardware_info_.machine_name) | bold,
        }),
        hbox({
            text("芯片型号：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.chip_type.empty() ? "未知" : hardware_info_.chip_type) | bold | color(Color::Blue),
        }),
        hbox({
            text("总核心数：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.get_total_cores() > 0 ? std::to_string(hardware_info_.get_total_cores()) + " (" +
                 std::to_string(hardware_info_.get_performance_cores()) + "性能 + " +
                 std::to_string(hardware_info_.get_efficiency_cores()) + "能效)" : "未知") | bold,
        }),
        hbox({
            text("内存容量：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.physical_memory.empty() ? "未知" : hardware_info_.physical_memory) | bold,
        }),
        hbox({
            text("机器型号：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.machine_model.empty() ? "未知" : hardware_info_.machine_model) | dim,
        }),
        hbox({
            text("型号编号：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.model_number.empty() ? "未知" : hardware_info_.model_number) | dim,
        }),
        hbox({
            text("序列号：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.serial_number.empty() ? "未知" : hardware_info_.serial_number) | dim,
        }),
        hbox({
            text("Boot ROM版本：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.boot_rom_version.empty() ? "未知" : hardware_info_.boot_rom_version) | dim,
        }),
        hbox({
            text("平台UUID：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.platform_uuid.empty() ? "未知" : hardware_info_.platform_uuid) | dim,
        }),
        hbox({
            text("激活锁状态：") | size(WIDTH, EQUAL, 16),
            text(hardware_info_.activation_lock_status == "activation_lock_enabled" ? "已启用" :
                 hardware_info_.activation_lock_status == "activation_lock_disabled" ? "已禁用" :
                 hardware_info_.activation_lock_status.empty() ? "未知" : hardware_info_.activation_lock_status) | bold |
                 color(hardware_info_.activation_lock_status == "activation_lock_enabled" ? Color::Green : Color::Yellow),
        }),
    });

    return vbox({
        text("💻 硬件信息") | bold | size(HEIGHT, LESS_THAN, 2),
        separator(),
        table | border,
    }) | flex | size(WIDTH, GREATER_THAN, 70) | hcenter;
}

} // namespace ui::pages
