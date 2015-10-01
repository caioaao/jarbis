#include "base/test/ConfigTest.h"

#include <fstream>
#include <random>
#include <cstdint>

#include "base/Config.h"
#include "base/RandUtils.h"
#include "base/debug.h"

namespace base_test
{
    typedef std::vector<std::pair<std::string, int64_t> > CfgEntryVector_;

    void test_load_file_(void);
    CfgEntryVector_ gen_cfg_values_(size_t amt, size_t max_len = 10);


    void
    config_test(void)
    {
        test_load_file_();
    }


    void
    test_load_file_(void)
    {

        static const std::string filepath_ = "tmp_testdata1.cfg";
        CfgEntryVector_ test_values = gen_cfg_values_(10);

        std::ofstream ofs;
        ofs.open(filepath_, std::ofstream::trunc | std::ofstream::out);

        for(CfgEntryVector_::const_iterator it = test_values.begin();
            it != test_values.end(); ++it)
        {
            ofs << (*it).first << ' ' << (*it).second << '\n';
        }

        ofs.close();

        base::ConfigMap mp;
        mp.add_from_file(filepath_);

        for(CfgEntryVector_::const_iterator it = test_values.begin();
            it != test_values.end(); ++it)
        {
            ASSERT(mp.get(it->first) == it->second);
        }
    }


    CfgEntryVector_
    gen_cfg_values_(size_t amt, size_t max_len)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int64_t> distribution(-1e16,1e16);

        CfgEntryVector_ vals(amt);

        for(CfgEntryVector_::iterator it = vals.begin(); it != vals.end(); ++it)
        {
            it->first = base::random_string(max_len,
                                            base::ALPHABET_ALPHANUMERIC);
            it->second = distribution(generator);
        }

        return vals;
    }
};
