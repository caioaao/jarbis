#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <cassert>

namespace debug {
    void my_assert(std::string func, std::string cond_str, bool cond);
#define ASSERT(x) debug::my_assert(__FUNCTION__, #x, (x))
}


#endif
