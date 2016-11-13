cmake_minimum_required (VERSION 2.6)
project (Jarbis)
include_directories("./")

add_subdirectory (base)
add_subdirectory (simulator)
enable_testing()
add_test(NAME base_test COMMAND jarbis_base_test)
add_test(NAME simulator_test COMMAND jarbis_simulator_test)
