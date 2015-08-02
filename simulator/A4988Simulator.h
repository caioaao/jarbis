#ifndef A4988SIMULATOR_H
#define A4988SIMULATOR_H

#include <stdint.h>

namespace simulator
{class A4988Simulator
    {
    public:
        enum A4988SimulatorPort
        {
            MS1_PORT,
            MS2_PORT,
            MS3_PORT,
            DIR_PORT,
            NSLEEP_PORT,
            NENABLE_PORT,
            NRESET_PORT,
            STEP_PORT
        };

        A4988Simulator();
        void set_value(A4988SimulatorPort port_idx, bool logical_value);

        static bool microstep_cfg_is_valid(bool ms1, bool ms2, bool ms3);

#ifdef DO_SMOKE_TEST
        uint32_t state(void);
        unsigned int microstep_resolution(void);
        bool step_direction(void);
#endif
    private:
        static const int NUM_PORTS_ = 8;
        uint32_t state_;
        unsigned int microstep_resolution_;
        bool step_direction_;


        bool get_value_(A4988SimulatorPort port_idx);
        void update_microstep_resolution_(void);
        void update_step_direction_(void);
        void step_(void);
    };


#ifdef DO_SMOKE_TEST
    void test_A4988_simulator(void);
#endif // #ifdef DO_SMOKE_TEST
}

#endif
