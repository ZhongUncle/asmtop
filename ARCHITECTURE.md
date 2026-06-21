# Mac 系统监控工具 架构设计（C++版本）

## 项目概述
这是一个专为 Apple Silicon（ARM架构）Mac 设计的高性能终端系统监控工具，使用现代C++17开发，资源占用极低，提供丰富的可视化数据展示功能。

## 目录结构
```
mac-monitor/
├── CMakeLists.txt                # CMake构建配置
├── src/                          # 源代码目录
│   ├── main.cpp                  # 程序入口
│   ├── collectors/               # 数据采集层
│   │   ├── base_collector.h      # 采集器基类
│   │   ├── pmset_collector.h/.cpp  # pmset命令采集器
│   │   ├── system_profiler_collector.h/.cpp  # system_profiler采集器
│   │   └── powermetrics_collector.h/.cpp  # powermetrics采集器（需要root，macOS系统限制：硬件功耗数据需sudo权限访问）
│   ├── models/                   # 数据模型层
│   │   ├── battery.h             # 电池相关数据结构
│   │   ├── hardware.h            # 硬件相关数据结构
│   │   ├── power.h               # 功耗相关数据结构
│   │   ├── thermal.h             # 温度相关数据结构
│   │   ├── process.h             # 进程相关数据结构
│   │   └── system.h              # 系统状态数据结构
│   ├── ui/                       # UI层
│   │   ├── components/           # 可复用UI组件
│   │   │   ├── progress_bar.h    # 进度条组件
│   │   │   ├── line_chart.h      # 折线图组件
│   │   │   ├── table.h           # 表格组件
│   │   │   ├── card.h            # 卡片/仪表盘组件
│   │   │   └── status_indicator.h  # 状态指示器组件
│   │   └── pages/                # 页面层
│   │       ├── base_page.h       # 页面基类
│   │       ├── overview_page.h/.cpp  # 概览页面
│   │       ├── hardware_page.h/.cpp  # 硬件信息页面
│   │       ├── battery_page.h/.cpp   # 电池详情页面
│   │       ├── power_page.h/.cpp     # 功耗监控页面
│   │       ├── thermal_page.h/.cpp   # 温度监控页面
│   │       ├── process_page.h/.cpp   # 进程能耗页面
│   │       └── system_page.h/.cpp    # 系统状态页面
│   ├── core/                     # 核心框架层
│   │   ├── app.h/.cpp            # ✅ 已实现：主应用类，管理页面注册、切换、全局事件、自动刷新
│   │   ├── config.h/.cpp         # 配置管理（待实现）
│   │   ├── event.h               # 事件系统定义（待实现）
│   │   └── types.h               # 通用类型定义（待实现）
│   └── utils/                    # 工具函数
│       ├── command_runner.h/.cpp  # 命令执行工具
│       ├── permission.h/.cpp     # 权限检查和架构检测
│       ├── string_utils.h/.cpp   # 字符串处理工具
│       └── parsers/              # 各种解析器（文本、JSON、Plist）
├── include/                      # 第三方header-only依赖
│   └── nlohmann/                 # JSON解析库
├── tests/                        # 测试目录
│   ├── CMakeLists.txt
│   └── test_collectors.cpp       # 采集器测试
├── docs/                         # 文档目录
│   ├── PLAN.md                   # 项目计划
│   ├── AGENTS.md                 # 执行规则
│   ├── ARCHITECTURE.md           # 架构文档（本文件）
│   ├── pmset_analysis.md         # pmset命令分析
│   ├── system_profiler_analysis.md  # system_profiler命令分析
│   └── powermetrics_analysis.md  # powermetrics命令分析
├── examples/                     # 样例数据目录
│   ├── pmset_sample.txt          # pmset样例输出
│   ├── system_profiler_sample.json  # system_profiler样例输出
│   └── powermetrics_sample.plist # powermetrics样例输出
└── README.md                     # 项目说明文档
```

## 模块设计

### 1. 数据采集层 (collectors)
**职责**：封装系统命令调用，解析命令输出，返回结构化数据
- 每个命令对应一个采集器类，继承自BaseCollector
- 提供统一的调用接口 `collect()` 方法
- 内置数据解析逻辑，将原始输出转换为数据模型对象
- 处理命令执行异常和权限问题

### 2. 数据模型层 (models)
**职责**：定义标准化的数据结构，提供数据验证和转换功能
- 使用dataclass定义强类型数据结构
- 提供单位转换和格式化方法
- 支持JSON序列化和反序列化
- 提供数据验证和异常处理

### 3. 可视化组件层 (visualizers)
**职责**：提供可复用的终端可视化组件
- 每个组件对应一种可视化类型
- 接收标准化数据，输出终端可渲染的内容
- 支持样式配置和响应式布局
- 组件之间相互独立，可组合使用

**已实现的组件：**
- ProgressBarVisualizer：进度条组件，展示百分比类数据
- BarChartVisualizer：条形图组件，支持横向/纵向条形图，多数据对比
- LineChartVisualizer：折线图组件，展示历史趋势数据
- PieChartVisualizer：饼图组件，展示占比类数据
- TableVisualizer：表格组件，支持行列展示、排序功能
- CardVisualizer：卡片/仪表盘组件，展示关键指标
- StatusIndicatorVisualizer：状态指示器组件，展示状态类信息

### 4. 页面层 (pages)
**职责**：组合可视化组件，实现具体的页面布局和业务逻辑
- 每个页面对应一个功能视图
- 负责页面内的组件布局和数据绑定
- 处理页面内的用户交互逻辑
- 提供统一的渲染接口 `render()` 方法

### 5. 核心框架层 (core)
**职责**：提供应用基础框架和通用功能
- App：主应用类，管理页面切换、事件分发、定时刷新
- Config：全局配置管理，支持用户自定义设置
- Event：事件系统，处理键盘输入和状态变化
- Exporter：数据导出功能，支持JSON/CSV等格式

## 技术栈
| 层级 | 技术选型 | 说明 |
|------|----------|------|
| 开发语言 | C++17 | 高性能，编译为原生arm64代码 |
| 终端UI | FTXUI | 现代化C++终端UI库，支持丰富的可视化组件 |
| 命令执行 | popen系统调用 | 执行macOS内置命令获取系统数据 |
| 数据处理 | nlohmann/json | header-only JSON解析库 |
| 构建工具 | CMake | 跨平台构建，自动下载依赖 |
| 测试框架 | Google Test | 单元测试和集成测试（待集成） |
| 打包工具 | 静态编译 | 生成单文件可执行程序，无需依赖 |

## 设计原则
1. **单一职责**：每个模块/类只负责一项功能
2. **接口统一**：同层模块提供一致的调用接口
3. **松耦合**：模块之间依赖最小化，通过接口交互
4. **可扩展性**：方便添加新的数据源、可视化组件和页面
5. **性能优先**：最小化资源占用，适合后台长期运行
6. **ARM优化**：仅针对Apple Silicon架构优化，充分利用其特性

## 数据流
```
用户操作 → 核心框架 → 页面层 → 数据采集层 → 系统命令
                                          ↓
系统命令输出 → 数据采集层 → 数据模型 → 页面层 → 可视化组件 → 终端渲染
```

## 新对话快速上手指南
当开启新的对话继续项目开发时，请按以下步骤进行：
1. 首先读取以下核心文档，了解项目上下文：
   - `docs/PLAN.md`：项目计划和阶段划分
   - `docs/AGENTS.md`：执行规则和要求
   - `docs/ARCHITECTURE.md`：架构设计（本文件）
2. 查看当前目录结构和已完成的代码
3. 确认当前需要执行的阶段和任务
4. 严格按照执行规则开展工作，完成后主动停止并汇报

## 临时文件清理规则
以下类型的文件属于临时文件，阶段完成后需要清理：
1. 测试生成的临时数据文件
2. 调试过程中产生的日志文件
3. 临时的代码备份文件
4. 编译/打包过程中产生的中间文件
5. 其他非项目必要的文件

清理要求：
- 保留所有源代码、文档、测试用例、样例数据
- 清理前确认文件不再需要，避免误删有用文件
- 清理完成后保留目录结构的完整性
