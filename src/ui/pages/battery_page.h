#ifndef BATTERY_PAGE_H
#define BATTERY_PAGE_H

#include "base_page.h"
#include "../../collectors/pmset_collector.h"
#include "../../models/battery.h"
#include <ftxui/component/component.hpp>

namespace ui::pages {

class BatteryPage : public BasePage {
public:
    BatteryPage();
    ~BatteryPage() override = default;

    ftxui::Component get_component() override;
    void refresh() override;
    std::string get_name() const override;

private:
    collectors::PmsetCollector pmset_collector_;
    models::BatteryInfo battery_info_;
    ftxui::Component component_;

    /**
     * @brief 渲染电池页面内容
     */
    ftxui::Element render();
};

} // namespace ui::pages

#endif // BATTERY_PAGE_H
