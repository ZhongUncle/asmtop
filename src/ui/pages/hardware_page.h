#ifndef HARDWARE_PAGE_H
#define HARDWARE_PAGE_H

#include "base_page.h"
#include "../../collectors/system_profiler_collector.h"
#include "../../models/hardware.h"
#include <ftxui/component/component.hpp>

namespace ui::pages {

class HardwarePage : public BasePage {
public:
    HardwarePage();
    ~HardwarePage() override = default;

    ftxui::Component get_component() override;
    void refresh() override;
    std::string get_name() const override;

private:
    collectors::SystemProfilerCollector system_profiler_collector_;
    models::HardwareInfo hardware_info_;
    ftxui::Component component_;

    /**
     * @brief 渲染硬件页面内容
     */
    ftxui::Element render();
};

} // namespace ui::pages

#endif // HARDWARE_PAGE_H
