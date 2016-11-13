#include "simulator/test/A4988SimulatorTest.h"

#include "base/debug.h"
#include "simulator/A4988Simulator.h"

#include <iostream>

namespace simulator_test {
    void
    test_state_assignment_(void) {
        simulator::A4988Simulator driverSim = simulator::A4988Simulator();
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

        simulator::A4988Simulator driverSim = simulator::A4988Simulator();

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
        simulator::A4988StepperMotor motor = simulator::A4988StepperMotor();
        motor.step(32, simulator::A4988StepperMotor::StepDirection::STEP_FORWARD);
        motor.step(2, simulator::A4988StepperMotor::StepDirection::STEP_FORWARD);
        motor.step(4, simulator::A4988StepperMotor::StepDirection::STEP_FORWARD);
        motor.step(1, simulator::A4988StepperMotor::StepDirection::STEP_FORWARD);
        motor.step(8, simulator::A4988StepperMotor::StepDirection::STEP_FORWARD);
        // 122/64 steps
        // std::cout << motor.position() << std::endl;
        // ASSERT(abs(motor.position() - 180) < 1e-6);
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
