#ifndef RANDUTILS_H
#define RANDUTILS_H

#include <cstdint>
#include <string>

namespace base
{
    extern std::string ALPHABET_ALPHANUMERIC;
    std::string random_string(size_t len, const std::string& alphabet);
};

#endif
