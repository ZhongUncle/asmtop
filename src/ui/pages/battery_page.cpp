#include "battery_page.h"
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace ui::pages {

BatteryPage::BatteryPage() {
    // 初始化时采集一次数据
    refresh();

    // 创建组件
    component_ = Renderer([&] { return render(); });
}

Component BatteryPage::get_component() {
    return component_;
}

void BatteryPage::refresh() {
    battery_info_ = pmset_collector_.collect();
}

std::string BatteryPage::get_name() const {
    return "电池信息";
}

Element BatteryPage::render() {
    // 根据电量设置进度条颜色
    Color gauge_color = Color::Green;
    if (battery_info_.percentage < 20) {
        gauge_color = Color::Red;
    } else if (battery_info_.percentage < 50) {
        gauge_color = Color::Yellow;
    }

    return vbox({
        text("🔋 电池状态") | bold | size(HEIGHT, LESS_THAN, 2),
        separator(),
        vbox({
            // 电量进度条
            hbox({
                text("电量："),
                gauge(battery_info_.percentage / 100.0f) | color(gauge_color) | flex,
                text(" " + std::to_string(battery_info_.percentage) + "%") | bold,
            }) | size(HEIGHT, LESS_THAN, 3),

            text(""),

            // 信息表格
            hbox({
                vbox({
                    text("电源类型："),
                    text("充电状态："),
                    text("剩余时间："),
                    text("电池状态："),
                }) | size(WIDTH, EQUAL, 12),
                vbox({
                    text(battery_info_.power_source_str()) | bold,
                    text(battery_info_.charging_state_str()) | bold,
                    text(battery_info_.remaining_time.empty() ? "未知" : battery_info_.remaining_time) | bold,
                    text(battery_info_.is_present ? "已连接" : "未检测到") | bold | color(battery_info_.is_present ? Color::Green : Color::Red),
                }),
            }) | size(HEIGHT, LESS_THAN, 6),
        }) | border,
    }) | flex | size(WIDTH, GREATER_THAN, 50) | hcenter;
}

} // namespace ui::pages
