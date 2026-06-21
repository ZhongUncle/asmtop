# 🖥️ asmtop

**Apple Silicon Mac real-time system monitoring utility**

专为 **Apple Silicon (M1/M2/M3/M4/M5 系列)** Mac 设计的高性能终端系统监控工具，使用现代C++17开发，资源占用极低，提供丰富的系统数据采集和可视化功能。

## ✨ 功能特性

### 📊 已实现功能
- **电池信息**: 实时电量、充电状态、电源类型、剩余时间等
- **硬件信息**: 芯片型号、CPU核心、内存、序列号等完整硬件配置
- **功耗监控**: CPU、GPU、ANE（神经网络引擎）的实时功耗展示（需要sudo权限）
- 每秒自动刷新数据，响应流畅
- 快捷键切换页面，操作简单
- 友好的权限不足提示

### 🔄 开发中功能
- **温度监控**: CPU、GPU、内存温度和风扇转速展示，支持历史趋势折线图
- **进程能耗**: 进程CPU使用率和能耗排行TOP15
- **系统状态**: CPU、内存、网络的实时使用率和趋势
- **概览页面**: 所有关键指标汇总展示

### 🎨 可视化组件
- 进度条: 展示百分比类数据（电量、功耗占比等），根据负载自动变色
- 表格: 结构化数据展示
- 折线图: 历史趋势数据展示（开发中）
- 卡片: 关键指标高亮展示（开发中）

## 🚀 快速开始

### 环境要求
- Apple Silicon (M1/M2/M3/M4/M5 系列) Mac
- macOS 12.0+
- CMake 3.14+ (编译时需要)

### 编译安装
```bash
# 克隆项目
git clone https://github.com/你的用户名/asmtop.git
cd asmtop

# 编译
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)

# 运行（基础功能，不需要sudo）
./bin/asmtop

# 完整功能（需要root权限，可查看功耗数据）
sudo ./bin/asmtop
```

### 快捷键
- `1` 电池信息页面
- `2` 硬件信息页面
- `3` 功耗监控页面
- `Q/q` 退出程序
- 数据每秒自动刷新

## 📁 项目结构

```
asmtop/
├── CMakeLists.txt                # CMake构建配置
├── src/                          # 源代码目录
│   ├── main.cpp                  # 程序入口
│   ├── collectors/               # 数据采集层
│   │   ├── base_collector.h      # 采集器基类
│   │   ├── pmset_collector.h/.cpp  # pmset命令采集（电池信息）
│   │   ├── system_profiler_collector.h/.cpp  # system_profiler采集（硬件信息）
│   │   └── powermetrics_collector.h/.cpp  # powermetrics采集（功耗数据，需要root）
│   ├── models/                   # 数据模型层
│   │   ├── battery.h             # 电池相关数据结构
│   │   ├── hardware.h            # 硬件相关数据结构
│   │   ├── power.h               # 功耗相关数据结构
│   │   ├── thermal.h             # 温度相关数据结构（开发中）
│   │   ├── process.h             # 进程相关数据结构（开发中）
│   │   └── system.h              # 系统状态数据结构（开发中）
│   ├── ui/                       # UI层
│   │   ├── components/           # 可复用UI组件
│   │   │   ├── progress_bar.h    # 进度条组件
│   │   │   ├── line_chart.h      # 折线图组件（开发中）
│   │   │   ├── table.h           # 表格组件（开发中）
│   │   │   ├── card.h            # 卡片/仪表盘组件（开发中）
│   │   │   └── status_indicator.h  # 状态指示器组件（开发中）
│   │   └── pages/                # 页面层
│   │       ├── base_page.h       # 页面基类
│   │       ├── battery_page.h/.cpp   # 电池详情页面
│   │       ├── hardware_page.h/.cpp  # 硬件信息页面
│   │       ├── power_page.h/.cpp     # 功耗监控页面
│   │       ├── thermal_page.h/.cpp   # 温度监控页面（开发中）
│   │       ├── process_page.h/.cpp   # 进程能耗页面（开发中）
│   │       ├── system_page.h/.cpp    # 系统状态页面（开发中）
│   │       └── overview_page.h/.cpp  # 概览页面（开发中）
│   ├── core/                     # 核心框架层
│   │   ├── app.h/.cpp            # 主应用类，管理页面注册、切换、全局事件、自动刷新
│   │   ├── config.h/.cpp         # 配置管理（待实现）
│   │   ├── event.h               # 事件系统定义（待实现）
│   │   └── types.h               # 通用类型定义（待实现）
│   └── utils/                    # 工具函数
│       ├── command_runner.h/.cpp  # 命令执行工具
│       ├── permission.h/.cpp     # 权限检查和架构检测
│       ├── string_utils.h/.cpp   # 字符串处理工具（待实现）
│       └── parsers/              # 各种解析器（文本、JSON、Plist）
├── include/                      # 第三方header-only依赖
│   └── nlohmann/                 # JSON解析库
├── docs/                         # 文档目录
│   ├── PLAN.md                   # 项目开发计划
│   ├── AGENTS.md                 # 开发执行规则
│   ├── ARCHITECTURE.md           # 架构设计文档
│   ├── pmset_analysis.md         # pmset命令分析
│   ├── system_profiler_analysis.md  # system_profiler命令分析
│   └── powermetrics_analysis.md  # powermetrics命令分析
├── examples/                     # 样例数据目录
│   ├── pmset_sample.txt          # pmset样例输出
│   ├── system_profiler_sample.json  # system_profiler样例输出
│   └── powermetrics_sample.plist # powermetrics样例输出
├── .gitignore                    # Git忽略规则
└── README.md                     # 项目说明文档
```

## 🔧 技术栈
- **C++17**: 高性能原生开发，编译为arm64架构代码
- **FTXUI**: 现代化C++终端UI库，支持丰富的可视化组件
- **CMake**: 跨平台构建工具，自动下载依赖
- **nlohmann/json**: header-only JSON解析库
- **系统内置命令**: 直接调用`pmset`/`system_profiler`/`powermetrics`获取数据，无需额外依赖

## 📝 使用说明

### 权限说明
- ✅ 基础功能（电池信息、硬件信息等）**不需要root权限**，直接运行即可
- ⚠️ 功耗、温度、进程监控等功能**需要root权限**，请使用 `sudo` 运行
> 📝 说明：powermetrics获取CPU/GPU/ANE等硬件级功耗数据需要root权限，这是macOS系统的安全限制，普通用户无法访问这类敏感硬件监控数据。

### 数据来源
本工具通过调用macOS系统内置命令获取数据，无需修改系统配置，安全可靠：
- `pmset`: 电源管理和电池状态查询
- `system_profiler`: 系统硬件和软件配置信息
- `powermetrics`: 实时功耗和性能监控（需要root权限）

## 🎯 性能目标
- CPU占用 < 1%
- 内存占用 < 20MB
- 启动时间 < 100ms
- 界面响应延迟 < 0.5秒

## 🤝 贡献
欢迎提交Issue和Pull Request！本项目采用小步迭代开发，具体开发计划请查看`docs/PLAN.md`。

## 📄 许可证
MIT License

## ⚠️ 注意事项
- ❌ 本工具**仅支持Apple Silicon架构的Mac**，不支持Intel架构
- 部分功能需要root权限，首次运行可能需要输入密码
- 数据默认每秒自动刷新，可根据需求修改源码调整间隔
