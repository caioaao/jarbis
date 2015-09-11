#include "debug.h"
#include <iostream>

namespace debug
{
    void
    myAssert(std::string func, bool cond)
    {
        if(!cond)
        {
            std::cerr << "assert failed at function " << func << std::endl;
        }

        assert(cond);
    }
};
