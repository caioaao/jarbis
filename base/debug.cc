#include "base/debug.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>

#ifdef _DO_ASSERT
void
debug::my_assert(std::string func, std::string cond_str, bool cond)
{
    if(!cond)
    {
        std::cerr << "assert failed at function " << func << std::endl;
        std::cerr << "Assert condition: " << cond_str << std::endl;
    }

    assert(cond);
}
#endif // #ifdef _DO_ASSERT


std::string
debug::bit_repr(int32_t x)
{
    std::string s;

    if(0 == x)
    {
        s = "0";
    }
    else
    {
        while(x != 0)
        {
            s.push_back('0' + (x & 1));
            x >>= 1;
        }
    }

    std::reverse(s.begin(), s.end());

    return s;
}
