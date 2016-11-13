#ifndef A4988SIMULATOR_H
#define A4988SIMULATOR_H

#include <cstdint>
#include "simulator/SimObj.h"

namespace simulator {
    class A4988StepperMotor {
        /*
         * This uses the step resolution to keep track of the rotor
         * position. It's safer this way, as it won't need floating points
         * except when converting it to degrees. This way there is only a
         * constant error proportional to the convertion, no drifts related to
         * time.
         * For implementation details, see the step method.
         */
    public:
        enum StepDirection {
            STEP_FORWARD,
            STEP_REVERSE
        };

        void step(uint32_t step_resolution, StepDirection direction);
        double position(void);

    private:
        static const uint32_t MAX_RESOLUTION_ = 64;
        uint32_t position_; // in terms of maximum resolution
    };

    class A4988Simulator: public SimObj {
    public:
        enum Port {
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
        virtual void update(void);

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
}

#endif
