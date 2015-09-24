#ifndef A4988SIMULATOR_H
#define A4988SIMULATOR_H

#include <cstdint>

namespace simulator
{
    class A4988StepperMotor
    {
    public:
        enum StepDirection
        {
            STEP_FORWARD,
            STEP_REVERSE
        };

        void step(uint32_t step_resolution, StepDirection direction);
    };

    class A4988Simulator
    {
    public:
        enum Port
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
        void set_value(Port port_idx, bool logical_value);
        uint32_t state(void);
        uint32_t microstep_resolution(void);
        bool step_direction(void);
        A4988StepperMotor * controlled_motor(void);

        static bool microstep_cfg_is_valid(bool ms1, bool ms2, bool ms3);

    private:
        static const int NUM_PORTS_ = 8;
        uint32_t state_;
        uint32_t microstep_resolution_;
        A4988StepperMotor::StepDirection step_direction_;
        A4988StepperMotor controlled_motor_;

        bool get_value_(Port port_idx);
        void update_microstep_resolution_(void);
        void update_step_direction_(void);
        void step_(void);
        bool outputs_are_enabled_(void);
    };



#ifdef DO_SMOKE_TEST
    void test_A4988_simulator(void);
#endif // #ifdef DO_SMOKE_TEST
}

#endif
