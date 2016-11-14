add_library(JarbisSimulator A4988Simulator.cc)
target_link_libraries(JarbisSimulator JarbisBase)

set_target_properties(JarbisSimulator PROPERTIES
  PUBLIC_HEADER "SimObj.h;A4988Simulator.h")

install(
  TARGETS JarbisSimulator
  EXPORT JarbisTargets
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}/simulator" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/simulator")

add_subdirectory(test)
