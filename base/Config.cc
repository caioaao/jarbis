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


    bool GlobalConfig::is_cfg_initialized_ = false;
    std::shared_ptr<ConfigMap> GlobalConfig::cfg_ =
        std::shared_ptr<ConfigMap>(new ConfigMap());

    void
    GlobalConfig::init_cfg_(void)
    {
        // stub: reads all files
        cfg_->add_from_file("log_cfg.txt");
    }


    std::shared_ptr<ConfigMap>
    GlobalConfig::get_object(void)
    {
        if(!is_cfg_initialized_)
        {
            init_cfg_();
        }
        return cfg_;
    }
};
