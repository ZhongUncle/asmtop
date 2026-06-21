#include <memory>
#include "core/app.h"
#include "ui/pages/battery_page.h"
#include "ui/pages/hardware_page.h"
#include "ui/pages/power_page.h"

using namespace core;
using namespace ui::pages;

int main() {
    App app;

    // 注册页面，指定快捷键
    app.register_page(std::make_shared<BatteryPage>(), '1');
    app.register_page(std::make_shared<HardwarePage>(), '2');
    app.register_page(std::make_shared<PowerPage>(), '3');

    // 运行应用
    app.run();

    return 0;
}
