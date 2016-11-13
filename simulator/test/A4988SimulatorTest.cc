#include "simulator/test/A4988SimulatorTest.h"

#include "base/debug.h"
#include "simulator/A4988Simulator.h"

#include <memory>
#include <iostream>

namespace simulator_test {
    void
    test_state_assignment_(void) {
        simulator::A4988Simulator driverSim = simulator::A4988Simulator(std::unique_ptr<simulator::A4988StepperMotor>(new simulator::A4988StepperMotor(1)));
        static const uint32_t MS1_PORT_MSK_ = (1 << simulator::A4988Simulator::MS1_PORT);
        static const uint32_t MS3_PORT_MSK_ = (1 << simulator::A4988Simulator::MS3_PORT);

        driverSim.set_value(simulator::A4988Simulator::MS1_PORT, true);
        ASSERT(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(simulator::A4988Simulator::MS3_PORT, true);

        ASSERT((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());

        driverSim.set_value(simulator::A4988Simulator::MS3_PORT, false);
        ASSERT(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(simulator::A4988Simulator::MS3_PORT, false);
        ASSERT(MS1_PORT_MSK_ == driverSim.state());

        driverSim.set_value(simulator::A4988Simulator::MS3_PORT, true);
        ASSERT((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());

        driverSim.set_value(simulator::A4988Simulator::MS3_PORT, true);
        ASSERT((MS1_PORT_MSK_ | MS3_PORT_MSK_) == driverSim.state());
    }


    void
    test_microstep_cfg_(void) {
        static const unsigned int expected_microstep_res_[8] =
            {1, 2, 4, 8, 2, 4, 8, 16};

        simulator::A4988Simulator driverSim = simulator::A4988Simulator(std::unique_ptr<simulator::A4988StepperMotor>(new simulator::A4988StepperMotor(1)));

        for(int i = 0; i < 8; ++i) {
            driverSim.set_value(simulator::A4988Simulator::MS1_PORT, 1 & i);
            driverSim.set_value(simulator::A4988Simulator::MS2_PORT, 2 & i);
            driverSim.set_value(simulator::A4988Simulator::MS3_PORT, 4 & i);

            uint32_t resulting_res = driverSim.microstep_resolution();
            ASSERT(resulting_res == expected_microstep_res_[i]);
        }
    }


    void
    test_stepping_(void) {
        static const int n_steps = 11;
        simulator::A4988StepperMotor motor = simulator::A4988StepperMotor(90);
        uint32_t steps[] = {1, 2, 4, 8, 16, 32, 64, 1, 1, 1, 1};
        simulator::A4988StepperMotor::StepDirection directions[] = {simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_FORWARD,
                                                                    simulator::A4988StepperMotor::StepDirection::STEP_REVERSE};
        double expected_positions[] = {90,
                                       135,
                                       157.5,
                                       168.75,
                                       174.375,
                                       177.188,
                                       178.594,
                                       268.594,
                                       358.594,
                                       88.5938,
                                       358.594};


        for(int i = 0; i < n_steps; ++i) {
            motor.step(steps[i], directions[i]);
            ASSERT(abs(motor.position() - expected_positions[i]) < 1e-6);
        }

        // Testing negative
        simulator::A4988StepperMotor motor2 = simulator::A4988StepperMotor(1);
        motor2.step(1, simulator::A4988StepperMotor::StepDirection::STEP_REVERSE);
        ASSERT(abs(motor.position() - 359.) < 1e-6);
    }


    void
    test_direction_(void) {
        // stub
    }


    void
    test_A4988_simulator(void) {
        test_state_assignment_();
        test_microstep_cfg_();
        test_direction_();
        test_stepping_();
    }
}
