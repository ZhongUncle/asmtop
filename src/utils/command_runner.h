#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include <string>

namespace utils {

/**
 * @brief 执行系统命令并返回输出
 * @param command 要执行的命令
 * @return 命令的标准输出内容，如果执行失败返回空字符串
 */
std::string run_command(const std::string& command);

} // namespace utils

#endif // COMMAND_RUNNER_H
