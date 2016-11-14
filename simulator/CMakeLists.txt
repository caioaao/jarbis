add_library(jarbis_simulator A4988Simulator.cc)
target_link_libraries(jarbis_simulator jarbis_base)

install(TARGETS jarbis_simulator DESTINATION bin)
install(FILES SimObj.h A4988Simulator.h DESTINATION include/jarbis/simulator)

add_subdirectory(test)
