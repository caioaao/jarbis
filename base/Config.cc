#include "base/Config.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "base/Logger.h"

#define SYS_CFG_DIR "./"

namespace base
{
    void
    ConfigMap::add_from_file(const std::string& filepath)
    {
        std::ifstream ifs;

        ifs.open(filepath, std::ifstream::in);

        std::string line;
        size_t line_num = 1;
        while(getline(ifs, line))
        {
            if(!parse_line_(line))
            {
                corelog() << log_level(LogLevel::LOG_CRIT)
                        << "Parse error at " << filepath << ':' << line_num
                        << '\n';
            }
            ++line_num;
        }

        ifs.close();
    }


    bool
    ConfigMap::parse_line_(const std::string& line)
    {
        std::stringstream linestream;
        std::string key;
        int64_t value;
        bool parsed_ok = true;

        linestream.str(line);

        if(linestream >> key >> value)
        {
            if(cfg_dict_.count(key))
            {
                corelog() << log_level(LogLevel::LOG_CRIT) << "Key " << key
                        << " is duplicated. Ignoring last value (" << value << ")"
                        << '\n';
                parsed_ok = false;
            }
            cfg_dict_[key] = value;
        }
        else
        {
            corelog() << log_level(LogLevel::LOG_CRIT)
                    << "Invalid line ignored. Raw line: " << line << '\n';

            parsed_ok = false;
        }

        return parsed_ok;
    }


    int64_t
    ConfigMap::get(const std::string& key) const
    {
        std::unordered_map<std::string, int64_t>::const_iterator
            it = cfg_dict_.find(key);

        if(it != cfg_dict_.end())
        {
            return (it->second);
        }
        else
        {
            return -1;
        }
    }


    const ConfigMap&
    SysConfig::instance(void)
    {
        static bool is_initialized_ = false;
        static ConfigMap * instance_ = new ConfigMap();

        if(!is_initialized_)
        {
            is_initialized_ = true;
            instance_->add_from_file(SYS_CFG_DIR "general.cfg");
        }

        return *instance_;
    }
};
