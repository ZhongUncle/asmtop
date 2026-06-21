#ifndef BASE_COLLECTOR_H
#define BASE_COLLECTOR_H

namespace collectors {

template <typename T>
class BaseCollector {
public:
    virtual ~BaseCollector() = default;

    /**
     * @brief 采集数据
     * @return 采集到的结构化数据
     */
    virtual T collect() = 0;
};

} // namespace collectors

#endif // BASE_COLLECTOR_H
