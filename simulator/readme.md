# Simulator

Classes here simulate the robot.

To avoid ROS dependency on the simulator, no simulated objects interact with
it. Instead, they're responsible for keeping and simulating state. A single
thread is responsible for retreiving all state it needs and publish to ROS
nodes.
