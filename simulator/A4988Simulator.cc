#include "A4988Simulator.h"

#ifdef DO_SMOKE_TEST
#include <cassert>
#endif

namespace simulator
{
    void
    A4988Simulator::set_port_value(A4988SimulatorPort port_idx,
                                   bool logical_value)
    {
        state_ &= ~((1 & !logical_value) << port_idx);
        state_ |=  ((1 &  logical_value) << port_idx);
    }

    A4988Simulator::A4988Simulator()
    {
        state_ = 0;
    }

#ifdef DO_SMOKE_TEST
    uint32_t
    A4988Simulator::state()
    {
        return state_;
    }

    void
    test_A4988_simulator(void)
    {
        A4988Simulator driverSim = A4988Simulator();
        driverSim.set_port_value(MS1_PORT, true);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_port_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());

        driverSim.set_port_value(MS3_PORT, false);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_port_value(MS3_PORT, false);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_port_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());

        driverSim.set_port_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());
    }
#endif
}
