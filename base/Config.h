#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <cstdint>
#include <memory>

namespace base
{
    class ConfigMap
    {
    private:
        std::unordered_map<std::string, int64_t> cfg_dict_;
        bool parse_line_(const std::string& line);
    public:
        void add_from_file(const std::string& filepath);
        int64_t get(const std::string& key) const;

        static ConfigMap get_global_config(void);
    };

    class SysConfig : public ConfigMap
    {
    private:
        SysConfig(){}
    public:
        static const ConfigMap& instance(void);
    };
};

#endif
