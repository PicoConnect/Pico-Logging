cmake_minimum_required(VERSION 3.31)
project(PicoLogging)

set(CMAKE_CXX_STANDARD 20)

# recursively search for all source files in the Source and Include directories
file(GLOB_RECURSE SOURCES

    "${PROJECT_SOURCE_DIR}/Include/*.h"
    "${PROJECT_SOURCE_DIR}/Source/*.cpp"
)

# Declare as a static library and use the recursive file finding.
add_library(PicoLogging STATIC ${SOURCES})

# Set language to C++
set_target_properties(PicoLogging PROPERTIES LINKER_LANGUAGE CXX)


# Add the standard include files to the build
target_include_directories(PicoLogging PUBLIC
        "${PROJECT_SOURCE_DIR}/Include"
)