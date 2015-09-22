#include <iostream>
#include <string>
#include <map>

#include "simulator/A4988Simulator.h"
#include "simulator/Ui.h"
#include "base/debug.h"


int main()
{
//     std::map<std::string, simulator::A4988Simulator::Port> port_name_to_port;
//
//     port_name_to_port["MS1_PORT"] = simulator::A4988Simulator::MS1_PORT;
//     port_name_to_port["MS2_PORT"] = simulator::A4988Simulator::MS2_PORT;
//     port_name_to_port["MS3_PORT"] = simulator::A4988Simulator::MS3_PORT;
//     port_name_to_port["DIR_PORT"] = simulator::A4988Simulator::DIR_PORT;
//     port_name_to_port["NSLEEP_PORT"] = simulator::A4988Simulator::NSLEEP_PORT;
//     port_name_to_port["NENABLE_PORT"] = simulator::A4988Simulator::NENABLE_PORT;
//     port_name_to_port["NRESET_PORT"] = simulator::A4988Simulator::NRESET_PORT;
//     port_name_to_port["STEP_PORT"] = simulator::A4988Simulator::STEP_PORT;
//
//     simulator::A4988Simulator a4988;
//     std::string port_name;
//     bool v;
//     simulator::A4988Simulator::Port port;
//     std::string stat;
//
//
//     while(std::cin >> port_name >> v)
//     {
//         if(port_name_to_port.count(port_name) == 0)
//         {
//             std::cout << "Invalid port name" << std::endl;
//         }
//         else
//         {
//             port = port_name_to_port[port_name];
//             a4988.set_value(port, v);
//             stat = debug::bit_repr(a4988.state());
//             std::cout << stat << std::endl;
//         }
//     }

    simulator::Ui ui = simulator::Ui(36,36);

    ui.update_pixel(30,30, 15);
    ui.render();
    ui.update_pixel(25, 14, 2440);
    ui.render();
}
