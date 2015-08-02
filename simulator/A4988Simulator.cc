#include "simulator/A4988Simulator.h"

#include <stdint.h>

#ifdef DO_SMOKE_TEST
#include <cassert>
#endif

namespace simulator
{
    void
    A4988Simulator::set_value(A4988SimulatorPort port_idx,
                                   bool logical_value)
    {
        uint32_t old_state = state_;

        state_ &= ~((1 & !logical_value) << port_idx);
        state_ |=  ((1 &  logical_value) << port_idx);
        state_ &= (1 << NUM_PORTS_) - 1; //cleanup all other unused bits on
                                         //bitmask
        switch(port_idx)
        {
        case STEP_PORT:
            if(true == logical_value && 0 == (old_state & (1 << STEP_PORT)))
            {
                // See page 9 for explanation.
                step_();
            }
            break;
        case MS1_PORT:
        case MS2_PORT:
        case MS3_PORT:
            update_microstep_resolution_();
            break;
        case DIR_PORT:
            update_step_direction_();
        default:
            break;
        }
    }


    bool
    A4988Simulator::get_value_(A4988SimulatorPort port_idx)
    {
        return !!(state_ & (1 << port_idx));
    }


    void
    A4988Simulator::update_microstep_resolution_(void)
    {
        // Although table 1 from datasheet shows only 5 configurations for the
        // MSx pins, page 7 explains how it really works, resulting in the
        // formula: 2^(MS1) * 2^(MS2*2) * 2^(MS3) This interpretation needs real
        // testing, thou

        bool v1 = get_value_(MS1_PORT);
        bool v2 = get_value_(MS2_PORT);
        bool v3 = get_value_(MS3_PORT);

        microstep_resolution_ = ((1 << v1) * (1 << (v2 * 2)) * (1 << v3));
    }


    void
    A4988Simulator::update_step_direction_(void)
    {
        step_direction_ = !!(state_ & (DIR_PORT));
    }


    void
    A4988Simulator::step_(void)
    {
        //stub
    }


    A4988Simulator::A4988Simulator()
    {
        set_value(MS1_PORT, false);
        set_value(MS2_PORT, false);
        set_value(MS3_PORT, false);
        set_value(DIR_PORT, false);
        set_value(NSLEEP_PORT, false);
        set_value(NENABLE_PORT, false);
        set_value(NRESET_PORT, false);
        set_value(STEP_PORT, false);
    }


#ifdef DO_SMOKE_TEST
    uint32_t
    A4988Simulator::state(void)
    {
        return state_;
    }

    unsigned int
    A4988Simulator::microstep_resolution(void)
    {
        return microstep_resolution_;
    }


    void
    test_state_assignment_(void)
    {
        A4988Simulator driverSim = A4988Simulator();
        static const uint32_t MS1_PORT_MSK_ = (1 << A4988Simulator::MS1_PORT);
        static const uint32_t MS3_PORT_MSK_ = (1 << A4988Simulator::MS3_PORT);

        driverSim.set_value(A4988Simulator::MS1_PORT, true);
        assert(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(A4988Simulator::MS3_PORT, true);

        assert((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());

        driverSim.set_value(A4988Simulator::MS3_PORT, false);
        assert(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(A4988Simulator::MS3_PORT, false);
        assert(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(A4988Simulator::MS3_PORT, true);
        assert((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());

        driverSim.set_value(A4988Simulator::MS3_PORT, true);
        assert((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());
    }


    void
    test_microstep_cfg_(void)
    {
        static const unsigned int expected_microstep_res_[8] =
            {1, 2, 4, 8, 2, 4, 8, 16};

        A4988Simulator driverSim = A4988Simulator();

        for(int i = 0; i < 8; ++i)
        {
            driverSim.set_value(A4988Simulator::MS1_PORT, 1 & i);
            driverSim.set_value(A4988Simulator::MS2_PORT, 2 & i);
            driverSim.set_value(A4988Simulator::MS3_PORT, 4 & i);

            unsigned int resulting_res = driverSim.microstep_resolution();
            assert(resulting_res == expected_microstep_res_[i]);
        }
    }


    void
    test_stepping_(void)
    {
        // stub
    }


    void
    test_direction_(void)
    {
        // stub
    }


    void
    test_A4988_simulator(void)
    {
        test_state_assignment_();
        test_microstep_cfg_();
        test_direction_();
        test_stepping_();
    }
#endif
}
