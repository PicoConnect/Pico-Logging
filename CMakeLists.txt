cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PicoLogging C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# recursively search for all source files in the Source and Include directories
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/Include/*.h"
    "${PROJECT_SOURCE_DIR}/Source/*.cpp"
)


# Declare as a static library and use the recursive file finding.
add_library(PicoLogging STATIC ${SOURCES})
add_library(PicoLogging::Lib ALIAS PicoLogging)


# Set library naming
set_target_properties(PicoLogging PROPERTIES
  OUTPUT_NAME PicoLogging
  EXPORT_NAME Lib
)

pico_set_program_name(PicoLogging "PicoLogging")
pico_set_program_version(PicoLogging "0.1")

# Set language to C++
set_target_properties(PicoLogging PROPERTIES LINKER_LANGUAGE CXX)

# make cache variables for install destinations
include(GNUInstallDirs)

target_include_directories(PicoLogging PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Instruct CMake where to install the targets
install(
    TARGETS PicoLogging
    EXPORT PicoLoggingTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Specify header destination
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Include/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# Export target information
install(EXPORT PicoLoggingTargets
  FILE PicoLoggingTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PicoLogging
  NAMESPACE PicoLogging::
)

# Use a standard helper module for packaging
include(CMakePackageConfigHelpers) 

# Generate the main Config file from our template
configure_package_config_file(
  "cmake/PicoLoggingConfig.cmake.in"
  "PicoLoggingConfig.cmake"
  INSTALL_DESTINATION
  "${CMAKE_INSTALL_LIBDIR}/cmake/PicoLogging"
)

# Generate a version file for version checking
write_basic_package_version_file( 
  "PicoLoggingConfigVersion.cmake" 
  #VERSION ${PROJECT_VERSION} 
  VERSION 0.1.0 #harcoded version for now
  COMPATIBILITY AnyNewerVersion 
)

# Install the generated config and version files
install(FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/PicoLoggingConfig.cmake" 
  "${CMAKE_CURRENT_BINARY_DIR}/PicoLoggingConfigVersion.cmake" 
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PicoLogging" 
)