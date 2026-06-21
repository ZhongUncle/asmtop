#ifndef APP_H
#define APP_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <vector>
#include <memory>
#include <atomic>
#include <string>
#include "../ui/pages/base_page.h"

namespace core {

class App {
public:
    App();
    ~App();

    /**
     * @brief 注册一个页面到应用中
     * @param page 页面对象
     * @param shortcut 激活该页面的快捷键字符
     */
    void register_page(std::shared_ptr<ui::pages::BasePage> page, char shortcut);

    /**
     * @brief 运行应用
     */
    void run();

    /**
     * @brief 退出应用
     */
    void exit();

    /**
     * @brief 切换到指定索引的页面
     * @param index 页面索引
     */
    void switch_to_page(int index);

    /**
     * @brief 获取当前页面索引
     * @return 当前页面索引
     */
    int get_current_page_index() const;

    /**
     * @brief 获取当前页面
     * @return 当前页面指针
     */
    std::shared_ptr<ui::pages::BasePage> get_current_page() const;

    /**
     * @brief 获取所有已注册的页面
     * @return 页面列表
     */
    const std::vector<std::shared_ptr<ui::pages::BasePage>>& get_pages() const;

private:
    struct PageEntry {
        std::shared_ptr<ui::pages::BasePage> page;
        char shortcut;
    };

    ftxui::ScreenInteractive screen_;
    std::vector<PageEntry> pages_;
    std::atomic<int> current_page_index_;
    std::atomic<bool> running_;
    std::thread refresh_thread_;

    /**
     * @brief 创建主渲染器
     * @return 主渲染器组件
     */
    ftxui::Component create_main_renderer();

    /**
     * @brief 刷新线程函数
     */
    void refresh_loop();

    /**
     * @brief 渲染顶部导航栏
     * @return 导航栏元素
     */
    ftxui::Element render_navbar() const;

    /**
     * @brief 渲染底部状态栏
     * @return 状态栏元素
     */
    ftxui::Element render_statusbar() const;
};

} // namespace core

#endif // APP_H
