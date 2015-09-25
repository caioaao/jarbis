#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <cstdint>

namespace cfg
{
    class ConfigMap
    {
    private:
        std::unordered_map<std::string, int64_t> cfg_dict_;
        void parse_line_(std::string line);
    public:
        void add_from_file(std::string filepath);
        int64_t get(std::string key);
    };
};

#endif
