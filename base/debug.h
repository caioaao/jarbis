#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <cassert>

namespace debug
{
#ifdef _DO_ASSERT
    void myAssert(std::string func, bool cond);
#define ASSERT(x) myAssert(__FUNCTION__, x)
#else
#define ASSERT(x)
#endif
};


#endif
