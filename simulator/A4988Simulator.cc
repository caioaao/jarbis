#include "A4988Simulator.h"

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
        state_ &= ~((1 & !logical_value) << port_idx);
        state_ |=  ((1 &  logical_value) << port_idx);

        if((MS1_PORT == port_idx) ||
           (MS2_PORT == port_idx) ||
           (MS3_PORT == port_idx))
        {
            update_microstep_resolution_();
        }
    }

    bool
    A4988Simulator::get_value_(A4988SimulatorPort port_idx)
    {
        return (state_ & (1 << port_idx));
    }

    bool
    A4988Simulator::microstep_cfg_is_valid(bool ms1, bool ms2, bool ms3)
    {
        // based on table 1 from a4988's datasheet
        return !((ms1 ^ ms2) & ms3);
    }

    void
    A4988Simulator::update_microstep_resolution_()
    {
        static unsigned int microstep_resolution_table_[2][2][2];
        static bool table_is_initialized_ = false;
        if(false == table_is_initialized_)
        {
            table_is_initialized_ = true;
            microstep_resolution_table_[0][0][0] = 1;
            microstep_resolution_table_[1][0][0] = 2;
            microstep_resolution_table_[0][1][0] = 4;
            microstep_resolution_table_[1][1][0] = 8;
            microstep_resolution_table_[1][1][1] = 16;
        }
        bool v1 = get_value_(MS1_PORT);
        bool v2 = get_value_(MS2_PORT);
        bool v3 = get_value_(MS3_PORT);

        if(true == A4988Simulator::microstep_cfg_is_valid(v1, v2, v3))
        {
            microstep_resolution_ = microstep_resolution_table_[v1][v2][v3];
        }
    }

    A4988Simulator::A4988Simulator()
    {
        state_ = 0;
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
        driverSim.set_value(MS1_PORT, true);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());

        driverSim.set_value(MS3_PORT, false);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_value(MS3_PORT, false);
        assert((1 << MS1_PORT) == driverSim.state());

        driverSim.set_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());

        driverSim.set_value(MS3_PORT, true);
        assert(((1 << MS1_PORT) | (1 << MS3_PORT)) == driverSim.state());
    }

    void
    test_microstep_cfg_()
    {
        // A4988 datasheet, pg 6, table 1
        static const bool ms_vals_[5][3] = {{0,0,0},
                                            {1,0,0},
                                            {0,1,0},
                                            {1,1,0},
                                            {1,1,1}};
        static const unsigned int expected_microstep_res_[5] = {1,2,4,8,16};
        static const int num_res = 5;

        A4988Simulator driverSim = A4988Simulator();

        for(int i = 0; i < num_res; ++i)
        {
            assert(A4988Simulator::microstep_cfg_is_valid(ms_vals_[i][0],
                                                          ms_vals_[i][1],
                                                          ms_vals_[i][2]));


            driverSim.set_value(MS1_PORT, ms_vals_[i][0]);
            driverSim.set_value(MS2_PORT, ms_vals_[i][1]);
            driverSim.set_value(MS3_PORT, ms_vals_[i][2]);

            assert(driverSim.microstep_resolution()
                   == expected_microstep_res_[i]);
        }
    }



    void
    test_A4988_simulator(void)
    {
        test_state_assignment_();
        test_microstep_cfg_();
    }
#endif
}
