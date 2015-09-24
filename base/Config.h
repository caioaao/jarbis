#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <cstdint>

namespace cfg
{
    class ConfigMap:
        std::unordered_map<std::string, int64_t>
    {
    public:
        void add_from_file(std::string filepath);
    };
};

#endif
