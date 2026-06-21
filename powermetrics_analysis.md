# powermetrics 命令分析报告

## 概述
powermetrics 是 macOS 上的高级功耗和性能监控工具，可以提供非常详细的系统能耗、CPU/GPU性能、温度等实时数据。**需要 root 权限**才能运行。

## 核心功能
powermetrics 支持多种采样器，可以采集不同类型的系统数据：

### 1. CPU 性能监控
**采样器**：`cpu_power`
**输出内容**：
- CPU 各个核心的使用率（用户态/内核态）
- CPU 频率分布和平均运行频率
- CPU P-state（性能状态）和 C-state（空闲状态）驻留时间
- 每个核心的功耗估计
- 整个 CPU  package 的总功耗

### 2. GPU 性能监控
**采样器**：`gpu_power`（部分硬件支持）
**输出内容**：
- GPU 使用率
- GPU 功耗估计
- GPU 频率信息

### 3. 进程级能耗监控
**采样器**：`tasks`
**输出内容**：
- 每个进程的 CPU 时间使用
- 进程导致的 package idle 唤醒次数
- 进程的能耗评分（composite score）
- 支持按能耗、CPU时间、唤醒次数等排序
- 可选参数：
  - `--show-process-gpu`：显示每个进程的 GPU 使用时间
  - `--show-process-io`：显示每个进程的 I/O 统计
  - `--show-process-netstats`：显示每个进程的网络统计
  - `--show-process-coalition`：按进程组统计，适合追踪临时进程

### 4. 电池和功耗监控
**采样器**：`battery`
**输出内容**：
- 电池放电速率
- 当前电量和最大容量
- 电池循环次数
- 设计容量衰减情况
- 背光亮度级别

### 5. 温度和风扇监控
**采样器**：`smc`
**输出内容**：
- 系统各个温度传感器的读数（CPU、GPU、主板等）
- 风扇转速
- 系统管理控制器（SMC）的其他信息

### 6. 散热压力监控
**采样器**：`thermal`
**输出内容**：
- 当前系统的热压力状态
- CPU  throttling（降频）信息

### 7. 中断分布监控
**采样器**：`interrupts`
**输出内容**：
- 每个 CPU 的中断频率
- 按设备分类的中断统计（网络、音频、存储等）
- 帮助识别驱动问题和异常的设备活动

### 8. 磁盘和网络活动监控
**采样器**：`disk`, `network`
**输出内容**：
- 磁盘读写吞吐量
- 网络吞吐量
- 可以按进程统计（使用 `--show-process-io` 和 `--show-process-netstats`）

### 9. 设备电源状态监控
**采样器**：`devices`
**输出内容**：
- 各个外设的电源状态驻留时间
- 低功耗状态（L）、可用状态（U）、开启状态（O）的占比

## 常用参数

### 基础参数
- `-i N`：采样间隔，单位毫秒，默认5000ms（5秒）
- `-n N`：采样次数，0表示无限采样，默认0
- `-o 文件`：输出到指定文件而不是标准输出
- `-f 格式`：输出格式，支持 `text`（默认，人类可读）和 `plist`（机器可读）

### 采样器选择
- `-s 采样器列表`：指定要使用的采样器，逗号分隔
  - `default`：默认采样器集合
  - `all`：所有可用采样器
  - 常用组合：`-s cpu_power,gpu_power,battery,smc,thermal,tasks`

### 显示选项
- `--show-pstates`：显示 CPU P-state 分布
- `--show-plimits`：显示功率限制和强制空闲信息
- `--show-process-energy`：显示进程的能耗评分
- `--show-usage-summary`：退出时显示最终使用汇总

## 输出格式特点
- 支持文本和 plist 两种格式
- plist 格式是结构化的，适合程序解析
- 实时输出数据，适合持续监控
- 可以按时间间隔采样，适合统计分析

## 使用示例
```bash
# 基本使用：每1秒采样1次，共采样5次，输出默认信息
sudo powermetrics -i 1000 -n 5

# 采集CPU、GPU、电池、温度信息，输出为plist格式
sudo powermetrics -s cpu_power,gpu_power,battery,smc -f plist -o power_data.plist

# 监控进程能耗，按能耗排序，显示GPU使用
sudo powermetrics -s tasks --show-process-gpu -r composite
```

## 注意事项
1. **需要 root 权限**：必须使用 sudo 运行
2. **数据是估计值**：功耗数据是估算的，不适合不同设备之间的比较，但适合同一设备上的优化比较
3. **性能影响**：高频率采样（<100ms）会增加系统负担
4. **Apple Silicon 支持**：在 Apple 芯片上可以提供更详细的功耗数据，包括 CPU、GPU、ANE（神经网络引擎）的单独功耗

## 推荐使用场景
1. 实时监控 CPU/GPU 功耗和温度
2. 分析应用程序的能耗效率
3. 识别异常高能耗的进程
4. 分析系统散热和降频情况
5. 性能优化和功耗优化的基准测试
6. 监控电池放电速率和实际续航表现
