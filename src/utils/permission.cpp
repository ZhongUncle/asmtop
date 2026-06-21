#include "permission.h"
#include <unistd.h>
#include <sys/sysctl.h>
#include <string>

namespace utils {

bool has_root_permission() {
    return geteuid() == 0;
}

int get_user_id() {
    return geteuid();
}

bool is_apple_silicon() {
    // Apple Silicon架构的sysctl信息
    char arch[256];
    size_t size = sizeof(arch);

    if (sysctlbyname("machdep.cpu.brand_string", &arch, &size, nullptr, 0) == 0) {
        std::string brand_string(arch);
        // Apple Silicon芯片包含"Apple"字样，如"Apple M1"、"Apple M2"等
        return brand_string.find("Apple") != std::string::npos;
    }

    // 另一种方式检查架构
    if (sysctlbyname("hw.optional.arm64", nullptr, &size, nullptr, 0) == 0) {
        return size > 0;
    }

    return false;
}

std::string get_architecture() {
    char arch[256];
    size_t size = sizeof(arch);

    if (sysctlbyname("machdep.cpu.brand_string", &arch, &size, nullptr, 0) == 0) {
        return std::string(arch);
    }

    return "Unknown";
}

} // namespace utils
