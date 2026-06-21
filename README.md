# 🍎 Mac System Monitor

专为 **Apple Silicon (ARM架构)** Mac 设计的终端系统监控工具，提供丰富的系统数据采集和可视化功能。

## ✨ 功能特性

### 📊 数据采集
- **电池信息**: 电量、充电状态、健康度、循环次数等
- **硬件信息**: CPU、GPU、内存、存储、网络等详细配置
- **功耗监控**: CPU、GPU、ANE（神经网络引擎）的实时功耗和趋势
- **温度监控**: CPU、GPU、内存的温度和风扇转速
- **进程能耗**: 进程的CPU使用率和能耗排行
- **系统状态**: CPU、内存、网络的实时使用率和趋势

### 🎨 可视化组件
- 进度条: 展示百分比类数据（电量、使用率等）
- 条形图: 多数据对比展示
- 折线图: 历史趋势数据展示（功耗、温度、性能等）
- 饼图: 占比类数据展示
- 表格: 结构化数据展示，支持排序
- 卡片: 关键指标高亮展示
- 状态指示器: 状态类信息展示

### 🖥️ 页面功能
1. **概览页面**: 关键系统指标汇总展示
2. **硬件信息**: 详细的硬件配置信息
3. **电池信息**: 电池健康和充电状态详情
4. **功耗监控**: 各部件功耗数据和历史趋势
5. **温度监控**: 温度传感器数据和风扇状态
6. **进程能耗**: 进程能耗排行，找出最耗电的应用
7. **系统状态**: CPU、内存、网络的实时状态和趋势

## 🚀 快速开始

### 环境要求
- Apple Silicon (M1/M2/M3 系列) Mac
- macOS 12.0+
- Python 3.9+

### 安装依赖
```bash
pip install -r requirements.txt
```

### 运行程序
```bash
# 基础功能运行
python3 run.py

# 完整功能运行（需要root权限，可查看功耗、温度、进程数据）
sudo python3 run.py
```

### 快捷键
- `1-7` 切换到对应页面
- `H/h` 显示帮助信息
- `Q/q` 退出程序

## 📁 项目结构

```
mac-monitor/
├── src/
│   └── mac_monitor/
│       ├── collectors/         # 数据采集层
│       │   ├── base.py         # 采集器基类
│       │   ├── pmset_collector.py    # pmset命令采集
│       │   ├── system_profiler_collector.py  # system_profiler采集
│       │   └── powermetrics_collector.py     # powermetrics采集
│       ├── models/             # 数据模型层
│       │   ├── base.py         # 模型基类
│       │   ├── pmset_models.py        # pmset数据模型
│       │   ├── system_profiler_models.py  # system_profiler模型
│       │   └── powermetrics_models.py     # powermetrics模型
│       ├── visualizers/        # 可视化组件层
│       │   ├── base.py         # 组件基类
│       │   ├── progress_bar.py        # 进度条组件
│       │   ├── bar_chart.py          # 条形图组件
│       │   ├── line_chart.py         # 折线图组件
│       │   ├── pie_chart.py          # 饼图组件
│       │   ├── table.py              # 表格组件
│       │   ├── card.py               # 卡片组件
│       │   └── status_indicator.py   # 状态指示器
│       ├── pages/              # 页面层
│       │   ├── base.py         # 页面基类
│       │   ├── overview.py     # 概览页面
│       │   ├── hardware.py     # 硬件信息页面
│       │   ├── battery.py      # 电池详情页面
│       │   ├── power.py        # 功耗监控页面
│       │   ├── thermal.py      # 温度监控页面
│       │   ├── process.py      # 进程能耗页面
│       │   └── system.py       # 系统状态页面
│       ├── core/               # 核心框架层
│       │   ├── app.py          # 主应用类
│       │   ├── config.py       # 配置管理
│       │   ├── event.py        # 事件系统
│       │   ├── base.py         # 采集器基类
│       │   └── exceptions.py   # 异常定义
│       ├── utils/              # 工具函数
│       │   ├── command_runner.py    # 命令执行工具
│       │   ├── permission_checker.py  # 权限检查工具
│       │   └── parsers/        # 各种解析器
│       └── main.py             # 程序入口
├── tests/                      # 测试代码
├── docs/                       # 文档
├── examples/                   # 示例数据
├── requirements.txt            # 依赖声明
├── pyproject.toml              # 项目配置
└── run.py                      # 启动脚本
```

## 🔧 技术栈
- **Python 3.9+**: 开发语言
- **Rich**: 终端UI库，提供丰富的可视化组件
- **Plotext**: 终端图表库（可选依赖）
- **Pydantic**: 数据验证和序列化
- **subprocess**: 系统命令执行

## 📝 使用说明

### 权限说明
- 基础功能（电池信息、硬件信息等）不需要root权限
- 功耗、温度、进程监控等功能需要root权限，请使用 `sudo` 运行

### 数据来源
本工具通过调用macOS系统内置命令获取数据：
- `pmset`: 电源管理和电池状态
- `system_profiler`: 系统硬件和软件配置
- `powermetrics`: 实时功耗和性能监控（需要root权限）

## 🤝 贡献
欢迎提交Issue和Pull Request！

## 📄 许可证
MIT License

## ⚠️ 注意事项
- 本工具仅支持Apple Silicon架构的Mac，不支持Intel架构
- 部分功能需要root权限，首次运行可能需要输入密码
- powermetrics命令会占用一定的系统资源，刷新间隔默认为2秒
