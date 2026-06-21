# pmset 命令分析报告

## 概述
pmset 是 macOS 上的电源管理命令行工具，主要用于管理和查询电源管理设置。对于系统监控工具来说，它提供了丰富的电池和电源相关信息。

## 核心查询功能

### 1. 电池状态查询
**命令**：`pmset -g batt` 或 `pmset -g ps`
**输出示例**：
```
Now drawing from 'AC Power'
 -InternalBattery-0 (id=5439587)	80%; AC attached; not charging present: true
```
**可提取信息**：
- 当前电源类型（AC电源/电池）
- 电池电量百分比
- 充电状态（充电中/未充电/充满）
- 电池存在状态

### 2. 电源适配器信息
**命令**：`pmset -g ac`
**输出示例**：
```
 Wattage = 60W
 Current = 2990mA
 Voltage = 20000mV
 AdapterID = 28702
 Manufacturer = Apple Inc.
 Family Code = 0xe000400a
 Serial String = F16HT90NMXP000179V
 Adapter Name = 40W Pwr Adapter 60W Max
 Hardware Version = 1.0
 Firmware Version = 01030079
```
**可提取信息**：
- 适配器功率（W）
- 输出电流（mA）
- 输出电压（mV）
- 适配器ID
- 制造商信息
- 序列号
- 适配器型号
- 硬件/固件版本

### 3. 系统电源状态
**命令**：`pmset -g systemstate`
**输出示例**：
```
Current System Capabilities are: CPU Graphics Audio Network 
Current Power State: 4
```
**可提取信息**：
- 当前系统可用功能模块
- 电源状态代码

### 4. 散热状态
**命令**：`pmset -g therm`
**功能**：显示影响CPU速度的散热状况

### 5. 电源断言
**命令**：`pmset -g assertions`
**功能**：显示当前阻止系统睡眠或显示器睡眠的进程和活动

### 6. 系统统计
**命令**：`pmset -g stats`
**功能**：显示系统启动以来的睡眠和唤醒次数统计

### 7. 全面信息导出
**命令**：`pmset -g everything`
**功能**：输出所有pmset支持的查询信息，适合一次性收集所有电源相关数据

## 输出格式特点
- 大部分输出为键值对格式，易于解析
- 电池状态输出为单行文本，需要简单的字符串处理
- 支持持续日志输出（如`-g pslog`、`-g rawlog`），适合实时监控

## 推荐使用场景
1. 实时监控电池电量和充电状态
2. 获取电源适配器的详细参数
3. 查看系统电源管理状态和异常（如阻止睡眠的进程）
4. 统计系统睡眠和唤醒情况
