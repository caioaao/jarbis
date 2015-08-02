#ifdef DO_SMOKE_TEST

#include "A4988Simulator.h"

#include <iostream>

int main()
{
    std::cout << "----------------------" << std::endl;

    std::cout << "Testing A4988Simulator" << std::endl;
    simulator::test_A4988_simulator();
    std::cout << "A4988Simulator test done" << std::endl;
}

#else
#error Only compile this source with DO_SMOKE_TEST
#endif
