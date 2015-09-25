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
        void parse_line_(std::string line);
    public:
        void add_from_file(std::string filepath);
        int64_t get(std::string key);

        static ConfigMap get_global_config(void);
    };

    class GlobalConfig
    {
    private:
        static std::shared_ptr<ConfigMap> cfg_;
        static bool is_cfg_initialized_;

        static void init_cfg_(void);

        GlobalConfig(){}
    public:
        static std::shared_ptr<ConfigMap> get_object(void);
    };
};

#endif
