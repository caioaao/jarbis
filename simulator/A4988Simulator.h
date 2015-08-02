#ifndef A4988SIMULATOR_H
#define A4988SIMULATOR_H

#include <stdint.h>

namespace simulator
{
    enum A4988SimulatorPort
    {
        MS1_PORT,
        MS2_PORT,
        MS3_PORT,
        DIR_PORT,
        SLEEP_PORT,
        ENABLE_PORT,
        RESET_PORT,
        STEP_PORT
    };

    class A4988Simulator
    {
    private:
        uint32_t state_;
    public:
        A4988Simulator();
        void set_port_value(A4988SimulatorPort port_idx, bool logical_value);
#ifdef DO_SMOKE_TEST
        uint32_t state(void);
#endif
    };


#ifdef DO_SMOKE_TEST
    void test_A4988_simulator(void);
#endif // #ifdef DO_SMOKE_TEST
}

#endif
