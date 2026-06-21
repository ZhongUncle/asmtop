#ifndef POWER_PAGE_H
#define POWER_PAGE_H

#include "base_page.h"
#include "../../collectors/powermetrics_collector.h"
#include "../../models/power.h"
#include <ftxui/component/component.hpp>

namespace ui::pages {

class PowerPage : public BasePage {
public:
    PowerPage();
    ~PowerPage() override = default;

    ftxui::Component get_component() override;
    void refresh() override;
    std::string get_name() const override;

private:
    collectors::PowermetricsCollector powermetrics_collector_;
    models::PowerInfo power_info_;
    ftxui::Component component_;

    /**
     * @brief 渲染功耗页面内容
     */
    ftxui::Element render();

    /**
     * @brief 渲染没有权限时的提示信息
     */
    ftxui::Element render_permission_error();

    /**
     * @brief 渲染功耗数据
     */
    ftxui::Element render_power_data();
};

} // namespace ui::pages

#endif // POWER_PAGE_H
