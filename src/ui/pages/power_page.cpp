#include "power_page.h"
#include "../../utils/permission.h"
#include <ftxui/dom/elements.hpp>
#include <iomanip>
#include <sstream>

using namespace ftxui;

namespace ui::pages {

PowerPage::PowerPage() {
    // 初始化时采集一次数据
    refresh();

    // 创建组件
    component_ = Renderer([&] { return render(); });
}

Component PowerPage::get_component() {
    return component_;
}

void PowerPage::refresh() {
    power_info_ = powermetrics_collector_.collect();
}

std::string PowerPage::get_name() const {
    return "功耗监控";
}

namespace {
    // 格式化浮点数为字符串，保留2位小数
    std::string format_float(float value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str();
    }

    // 根据功耗值获取对应的颜色
    Color get_power_color(float percentage) {
        if (percentage > 80) return Color::Red;
        if (percentage > 50) return Color::Yellow;
        return Color::Green;
    }
}

Element PowerPage::render_permission_error() {
    return vbox({
        text("⚠️  数据采集失败") | bold | color(Color::Yellow) | hcenter,
        separator(),
        vbox({
            text(power_info_.error_message) | hcenter,
            text(""),
            text("可能的解决方案：") | hcenter,
            text("1. 确保你运行在Apple Silicon架构的Mac上") | hcenter,
            text("2. 检查系统权限设置，允许终端访问系统监控数据") | hcenter,
            text("3. 尝试使用sudo运行：sudo ./mac-monitor") | hcenter,
            text(""),
            text("注意：powermetrics命令仅在Apple Silicon架构上可用") | dim | hcenter,
        }) | border,
    }) | flex | hcenter | size(WIDTH, GREATER_THAN, 60);
}

Element PowerPage::render_power_data() {
    float total_percent = power_info_.get_total_percentage();
    float cpu_percent = power_info_.get_cpu_percentage();
    float gpu_percent = power_info_.get_gpu_percentage();
    float ane_percent = power_info_.get_ane_percentage();

    return vbox({
        text("⚡ 实时功耗") | bold | size(HEIGHT, LESS_THAN, 2),
        separator(),
        vbox({
            // 总功耗
            hbox({
                text("总功耗："),
                gauge(total_percent / 100.0f) | color(get_power_color(total_percent)) | flex,
                text(" " + format_float(power_info_.total_power) + " W / " + format_float(power_info_.power_limit) + " W") | bold,
            }) | size(HEIGHT, LESS_THAN, 3),

            text(""),

            // CPU功耗
            hbox({
                text("CPU："),
                gauge(cpu_percent / 100.0f) | color(get_power_color(cpu_percent)) | flex,
                text(" " + format_float(power_info_.cpu_power) + " W") | bold,
            }) | size(HEIGHT, LESS_THAN, 3),

            // GPU功耗
            hbox({
                text("GPU："),
                gauge(gpu_percent / 100.0f) | color(get_power_color(gpu_percent)) | flex,
                text(" " + format_float(power_info_.gpu_power) + " W") | bold,
            }) | size(HEIGHT, LESS_THAN, 3),

            // ANE功耗
            hbox({
                text("ANE："),
                gauge(ane_percent / 100.0f) | color(get_power_color(ane_percent)) | flex,
                text(" " + format_float(power_info_.ane_power) + " W") | bold,
            }) | size(HEIGHT, LESS_THAN, 3),

            text(""),

            // 信息表格
            hbox({
                vbox({
                    text("架构："),
                    text("用户ID："),
                    text("权限状态："),
                }) | size(WIDTH, EQUAL, 12),
                vbox({
                    text(utils::get_architecture()) | bold,
                    text(std::to_string(utils::get_user_id())) | bold,
                    text(utils::has_root_permission() ? "已获取root权限" : "无root权限") | bold | color(utils::has_root_permission() ? Color::Green : Color::Red),
                }),
            }) | size(HEIGHT, LESS_THAN, 5),
        }) | border,
    }) | flex | size(WIDTH, GREATER_THAN, 60) | hcenter;
}

Element PowerPage::render() {
    if (!power_info_.is_valid) {
        return render_permission_error();
    }

    return render_power_data();
}

} // namespace ui::pages
