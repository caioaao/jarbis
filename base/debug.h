#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <cassert>

namespace debug
{
#ifdef _DO_ASSERT
    void my_assert(std::string func, bool cond);
#define ASSERT(x) my_assert(__FUNCTION__, x)
#else
#define ASSERT(x)
#endif

    std::string bit_repr(int x);
};


#endif
