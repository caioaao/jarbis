add_library(JarbisBase debug.cc Logger.cc Config.cc RandUtils.cc Kinematics.cc)

set_target_properties(JarbisBase PROPERTIES
  PUBLIC_HEADER "debug.h;Logger.h;Config.h;RandUtils.h;Kinematics.h")

install(
  TARGETS JarbisBase
  EXPORT JarbisTargets
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}/base" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/base")

add_subdirectory(test)
