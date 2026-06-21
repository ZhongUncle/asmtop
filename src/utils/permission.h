#ifndef PERMISSION_H
#define PERMISSION_H

#include <string>

namespace utils {

/**
 * @brief 检查当前是否有root权限
 * @return true 如果有root权限，false 否则
 */
bool has_root_permission();

/**
 * @brief 检查当前是否运行在Apple Silicon架构上
 * @return true 如果是Apple Silicon，false 否则
 */
bool is_apple_silicon();

/**
 * @brief 获取当前用户ID
 * @return 用户ID
 */
int get_user_id();

/**
 * @brief 获取当前架构名称
 * @return 架构名称字符串
 */
std::string get_architecture();

} // namespace utils

#endif // PERMISSION_H
