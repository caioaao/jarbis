#include "base/debug.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>

#ifdef _DO_ASSERT
void
debug::my_assert(std::string func, std::string cond_str, bool cond) {
    if(!cond) {
        std::cerr << "assert failed at function " << func << std::endl;
        std::cerr << "Assert condition: " << cond_str << std::endl;
    }

    assert(cond);
}
#endif // #ifdef _DO_ASSERT
