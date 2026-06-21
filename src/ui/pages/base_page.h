#ifndef BASE_PAGE_H
#define BASE_PAGE_H

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace ui::pages {

class BasePage {
public:
    virtual ~BasePage() = default;

    /**
     * @brief 获取页面的FTXUI组件
     * @return 页面组件
     */
    virtual ftxui::Component get_component() = 0;

    /**
     * @brief 刷新页面数据
     */
    virtual void refresh() = 0;

    /**
     * @brief 获取页面名称
     * @return 页面名称
     */
    virtual std::string get_name() const = 0;
};

} // namespace ui::pages

#endif // BASE_PAGE_H
