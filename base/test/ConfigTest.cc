#include "base/test/ConfigTest.h"

#include <fstream>
#include <random>
#include <cstdint>
#include <sstream>
#include <iterator>

#include "base/Config.h"
#include "base/RandUtils.h"
#include "base/debug.h"

namespace base_test
{
    typedef std::vector<std::pair<std::string, int64_t> > CfgEntryVector_;

    void test_load_file_(void);
    void test_load_multiple_files_(void);
    void test_load_invalid_file_(void);
    void test_matching_entries_(const base::ConfigMap &mp,
                                const CfgEntryVector_& entries);
    void gen_cfg_file_(std::string filepath,
                              const CfgEntryVector_& entries);
    CfgEntryVector_ gen_cfg_values_(size_t amt, size_t max_len = 10);
    std::vector<std::string> gen_filepaths_(size_t amt = 10);



    void
    config_test(void)
    {
        test_load_file_();
        test_load_multiple_files_();
        test_load_invalid_file_();
    }


    void
    test_load_invalid_file_(void)
    {
        std::string filepath = "invalid_file.test.cfg";
        CfgEntryVector_ valid_entries = gen_cfg_values_(10);


        gen_cfg_file_(filepath, valid_entries);

        std::ofstream ofs;
        ofs.open(filepath, std::ofstream::out | std::ofstream::app);

        ofs << "INVALIDLINE\n";
        ofs.close();

        base::ConfigMap cfg;
        cfg.add_from_file(filepath);
        test_matching_entries_(cfg, valid_entries);
    }


    void
    test_load_multiple_files_(void)
    {
        std::vector<std::string> filepaths = gen_filepaths_();
        std::vector<CfgEntryVector_> entries;

        for(std::vector<std::string>::iterator it = filepaths.begin();
            it != filepaths.end(); ++it)
        {
            entries.push_back(gen_cfg_values_(10));
            gen_cfg_file_((*it), entries.back());
        }

        base::ConfigMap mp;
        for(std::vector<std::string>::iterator it = filepaths.begin();
            it != filepaths.end(); ++it)
        {
            mp.add_from_file(*it);
        }

        for(std::vector<CfgEntryVector_>::const_iterator it = entries.begin();
            it != entries.end(); ++it)
        {
            test_matching_entries_(mp, *it);
        }
    }


    void
    test_load_file_(void)
    {
        static const std::string filepath_ = "tmp_testdata1.test.cfg";

        CfgEntryVector_ test_values = gen_cfg_values_(10);

        gen_cfg_file_(filepath_, test_values);

        base::ConfigMap mp;

        mp.add_from_file(filepath_);

        test_matching_entries_(mp, test_values);
    }


    void
    test_matching_entries_(const base::ConfigMap &mp,
                           const CfgEntryVector_& entries)
    {
        for(CfgEntryVector_::const_iterator it = entries.begin();
            it != entries.end(); ++it)
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


    void
    gen_cfg_file_(std::string filepath, const CfgEntryVector_& entries)
    {
        std::ofstream ofs;
        ofs.open(filepath, std::ofstream::trunc | std::ofstream::out);

        for(CfgEntryVector_::const_iterator it = entries.begin();
            it != entries.end(); ++it)
        {
            ofs << (*it).first << ' ' << (*it).second << '\n';
        }

        ofs.close();
    }

    std::vector<std::string>
    gen_filepaths_(size_t amt)
    {
        std::vector<std::string> filepaths(amt);
        std::stringstream ss;

        for(std::vector<std::string>::iterator it = filepaths.begin();
            it != filepaths.end(); ++it)
        {
            ss << "cfg_test_file" << std::distance(filepaths.begin(), it)
               << ".test.cfg";

            ss >> (*it);

            ss.clear();
        }

        return filepaths;
    }
};
