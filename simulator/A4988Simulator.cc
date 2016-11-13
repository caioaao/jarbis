#include "simulator/A4988Simulator.h"

#include <cstdint>

#include "base/debug.h"

namespace simulator {
    void
    A4988StepperMotor::step(uint32_t step_resolution,
                            StepDirection direction) {
        uint32_t delta = MAX_RESOLUTION_ / step_resolution;
        if (StepDirection::STEP_REVERSE == direction) {
            delta = 360 * MAX_RESOLUTION_ - delta;
        }
        this->position_ = (this->position_ + delta) % (360 * MAX_RESOLUTION_);
    }


    double
    A4988StepperMotor::position(void) {
        return this->position_ / (float)MAX_RESOLUTION_;
    }


    void
    A4988Simulator::set_value(Port port_idx, bool logical_value) {
        uint32_t old_state = state_;

        state_ &= ~((1 & !logical_value) << port_idx);
        state_ |=  ((1 &  logical_value) << port_idx);
        state_ &= (1 << NUM_PORTS_) - 1; //cleanup all other unused bits on
                                         //bitmask
        switch(port_idx) {
        case STEP_PORT:
            if(true == logical_value && 0 == (old_state & (1 << STEP_PORT))) {
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
            break;
        case NRESET_PORT:
        case NENABLE_PORT:
        case NSLEEP_PORT:
        default:
            break;
        }
    }


    bool
    A4988Simulator::get_value_(Port port_idx) {
        return !!(state_ & (1 << port_idx));
    }


    void
    A4988Simulator::update_microstep_resolution_(void) {
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
    A4988Simulator::update_step_direction_(void) {
        if(0 != (state_ & (DIR_PORT))) {
            step_direction_ = A4988StepperMotor::STEP_FORWARD;
        }
        else {
            step_direction_ = A4988StepperMotor::STEP_REVERSE;
        }
    }


    bool
    A4988Simulator::outputs_are_enabled_(void) {
        static const uint32_t NRESET_MSK = (1 << NRESET_PORT);
        static const uint32_t NSLEEP_MSK = (1 << NSLEEP_PORT);
        static const uint32_t NENABLE_MSK = (1 << NENABLE_PORT);


        return (0 == (state_ & NENABLE_MSK)) && (0 != (state_ & NRESET_MSK)) &&
            (0 != (state_ & NSLEEP_MSK));
    }


    void
    A4988Simulator::step_(void) {
        if(outputs_are_enabled_()) {
            controlled_motor_.step(microstep_resolution_, step_direction_);
        }
    }


    A4988Simulator::A4988Simulator() {
        set_value(MS1_PORT, false);
        set_value(MS2_PORT, false);
        set_value(MS3_PORT, false);
        set_value(DIR_PORT, false);
        set_value(NSLEEP_PORT, false);
        set_value(NENABLE_PORT, false);
        set_value(NRESET_PORT, false);
        set_value(STEP_PORT, false);

        controlled_motor_ = A4988StepperMotor();
    }


    uint32_t
    A4988Simulator::state(void) {
        return state_;
    }

    uint32_t
    A4988Simulator::microstep_resolution(void) {
        return microstep_resolution_;
    }


    A4988StepperMotor *
    A4988Simulator::controlled_motor(void) {
        return &controlled_motor_;
    }

    void
    A4988Simulator::update(void) {
        step_();
    }
}
