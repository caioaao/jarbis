#include "base/Config.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace base
{
    void
    ConfigMap::add_from_file(const std::string& filepath)
    {
        std::ifstream ifs;

        ifs.open(filepath, std::ifstream::in);

        std::string line;
        while(getline(ifs, line))
        {
            parse_line_(line);
        }

        ifs.close();
    }


    void
    ConfigMap::parse_line_(const std::string& line)
    {
        std::stringstream linestream;
        std::string key;
        int64_t value;

        linestream.str(line);

        linestream >> key >> value;

        if(cfg_dict_.count(key))
        {
            // stub
        }
        cfg_dict_[key] = value;
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
