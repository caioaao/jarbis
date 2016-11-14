cmake_minimum_required (VERSION 2.6)
project (Jarbis)

set(Jarbis_MAJOR_VERSION 0)
set(Jarbis_MINOR_VERSION 1)
set(Jarbis_PATCH_VERSION 0)
set(Jarbis_VERSION
  "${Jarbis_MAJOR_VERSION}.${Jarbis_MINOR_VERSION}.${Jarbis_PATCH_VERSION}")

add_definitions(-std=c++11)

include_directories("./")

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR "lib/jarbis-${Jarbis_VERSION}"         CACHE PATH
  "Installation directory for libraries")
set(INSTALL_BIN_DIR "bin/jarbis-${Jarbis_VERSION}"         CACHE PATH
  "Installation directory for executables")
set(INSTALL_INCLUDE_DIR "include/jarbis-${Jarbis_VERSION}" CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/jarbis)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Recurse into subdirs
add_subdirectory (base)
add_subdirectory (simulator)
export(TARGETS JarbisBase JarbisSimulator
  FILE "${PROJECT_BINARY_DIR}/JarbisTargets.cmake")
export(PACKAGE Jarbis)

# Create the FooBarConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(JarbisConfig.cmake.in
  "${PROJECT_BINARY_DIR}/JarbisConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${Jarbis_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(JarbisConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/JarbisConfig.cmake" @ONLY)
# ... for both
configure_file(JarbisConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/JarbisConfigVersion.cmake" @ONLY)

# Install the JarbisConfig.cmake and JarbisConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/JarbisConfig.cmake"
  "${PROJECT_BINARY_DIR}/JarbisConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT JarbisTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)

enable_testing()
add_test(NAME BaseTest COMMAND JarbisBaseTest)
add_test(NAME SimulatorTest COMMAND JarbisSimulatorTest)
