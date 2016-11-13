add_library(jarbis_simulator A4988Simulator.cc)
target_link_libraries(jarbis_simulator jarbis_base)

add_subdirectory(test)
