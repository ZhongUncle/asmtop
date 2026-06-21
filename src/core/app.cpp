#include "app.h"
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <chrono>
#include <sstream>

using namespace ftxui;
using namespace ui::pages;

namespace core {

App::App()
    : screen_(ScreenInteractive::TerminalOutput()),
      current_page_index_(0),
      running_(false) {}

App::~App() {
    if (running_) {
        exit();
    }
}

void App::register_page(std::shared_ptr<BasePage> page, char shortcut) {
    pages_.push_back({page, shortcut});
}

void App::run() {
    running_ = true;

    // 启动刷新线程
    refresh_thread_ = std::thread(&App::refresh_loop, this);

    // 创建主渲染器
    auto main_renderer = create_main_renderer();

    // 运行事件循环
    screen_.Loop(main_renderer);

    running_ = false;
    if (refresh_thread_.joinable()) {
        refresh_thread_.join();
    }
}

void App::exit() {
    running_ = false;
    screen_.Exit();
}

void App::switch_to_page(int index) {
    if (index >= 0 && static_cast<size_t>(index) < pages_.size()) {
        current_page_index_ = index;
    }
}

int App::get_current_page_index() const {
    return current_page_index_;
}

std::shared_ptr<BasePage> App::get_current_page() const {
    if (current_page_index_ >= 0 && static_cast<size_t>(current_page_index_) < pages_.size()) {
        return pages_[static_cast<size_t>(current_page_index_)].page;
    }
    return nullptr;
}

const std::vector<std::shared_ptr<BasePage>>& App::get_pages() const {
    static std::vector<std::shared_ptr<BasePage>> pages;
    pages.clear();
    for (const auto& entry : pages_) {
        pages.push_back(entry.page);
    }
    return pages;
}

Component App::create_main_renderer() {
    auto renderer = Renderer([&] {
        auto current_page = get_current_page();
        if (!current_page) {
            return text("无可用页面") | hcenter | vcenter | border;
        }

        return vbox({
            render_navbar(),
            separator(),
            current_page->get_component()->Render() | flex,
            separator(),
            render_statusbar(),
        }) | border;
    });

    // 绑定全局按键事件
    renderer |= CatchEvent([&](Event event) {
        // 退出快捷键
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            exit();
            return true;
        }

        // 页面切换快捷键
        for (size_t i = 0; i < pages_.size(); ++i) {
            if (event == Event::Character(pages_[i].shortcut)) {
                switch_to_page(static_cast<int>(i));
                return true;
            }
        }

        return false;
    });

    return renderer;
}

void App::refresh_loop() {
    while (running_) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto current_page = get_current_page();
        if (current_page) {
            current_page->refresh();
            screen_.PostEvent(Event::Custom); // 通知UI刷新
        }
    }
}

Element App::render_navbar() const {
    auto current_page = get_current_page();
    std::string title = "🍎 Mac 系统监控工具";
    std::string page_name = current_page ? current_page->get_name() : "未知页面";

    return hbox({
        text(title) | bold,
        filler(),
        text("当前页面：" + page_name) | dim,
    });
}

Element App::render_statusbar() const {
    std::stringstream ss;
    ss << "快捷键：";
    for (size_t i = 0; i < pages_.size(); ++i) {
        ss << pages_[i].shortcut << "=" << pages_[i].page->get_name();
        if (i != pages_.size() - 1) {
            ss << " ";
        }
    }
    ss << " Q=退出 | 数据每1秒自动刷新";

    return text(ss.str()) | dim | hcenter;
}

} // namespace core
