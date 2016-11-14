add_library(jarbis_base debug.cc Logger.cc Config.cc RandUtils.cc Kinematics.cc)

install(TARGETS jarbis_base DESTINATION bin)
install(FILES debug.h Logger.h Config.h RandUtils.h Kinematics.h DESTINATION include/jarbis/base)

add_subdirectory(test)
