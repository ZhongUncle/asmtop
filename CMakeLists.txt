cmake_minimum_required(VERSION 3.14)
project(asmtop LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器警告选项
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 使用FetchContent自动下载FTXUI
include(FetchContent)
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v5.0.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(ftxui)

# 包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

# 源文件
set(SOURCES
    src/main.cpp
    src/core/app.cpp
    src/utils/command_runner.cpp
    src/utils/permission.cpp
    src/collectors/pmset_collector.cpp
    src/collectors/system_profiler_collector.cpp
    src/collectors/powermetrics_collector.cpp
    src/ui/pages/battery_page.cpp
    src/ui/pages/hardware_page.cpp
    src/ui/pages/power_page.cpp
)

# 生成可执行文件
add_executable(asmtop ${SOURCES})

# 链接FTXUI库
target_link_libraries(asmtop
    PRIVATE ftxui::component
    PRIVATE ftxui::dom
    PRIVATE ftxui::screen
)

# 设置输出目录
set_target_properties(asmtop PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
