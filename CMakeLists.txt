#-------------------------------------------------------------------------------
#                               Base settings.
#-------------------------------------------------------------------------------

# Set CMake minimum required version.
cmake_minimum_required(VERSION 3.0)

# Set project information.
project(
    PelcoD
    VERSION 1.0.0
    LANGUAGES CXX
)

# Set C++ standard version.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#-------------------------------------------------------------------------------
#                          Build variables settings.
#-------------------------------------------------------------------------------

# Set library target name.
set(LIBRARY_TARGET "pelcod")

# Set path to source files.
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Set library definitions.
add_definitions(-DPELCOD_LIBRARY)


#-------------------------------------------------------------------------------
#                           Project files settings.
#-------------------------------------------------------------------------------

# Set source header files.
set(
    SOURCE_HEADER_FILES
    ${SOURCE_PATH}/Export.hpp
    ${SOURCE_PATH}/AbstractPelcoDDevice.hpp
    ${SOURCE_PATH}/PelcoDEDeviceUDP.hpp
)

# Set source source files.
set(
    SOURCE_SOURCE_FILES
    ${SOURCE_PATH}/AbstractPelcoDDevice.cpp
    ${SOURCE_PATH}/PelcoDEDeviceUDP.cpp
)

# Set source files to list.
list(
    APPEND SOURCE_FILES
    ${SOURCE_HEADER_FILES}
    ${SOURCE_SOURCE_FILES}
)


#-------------------------------------------------------------------------------
#                          External packages settings.
#-------------------------------------------------------------------------------

# Find Boost C++ Libraries.
find_package(
    Boost 1.56
    REQUIRED COMPONENTS system
)

# Print an error message if Boost C++ Libraries are not found.
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost C++ Libraries are required to build the library")
endif()


#-------------------------------------------------------------------------------
#                       Include directories settings.
#-------------------------------------------------------------------------------

# Set source include directories to list.
list(
    APPEND SOURCE_INCLUDE_DIRECTORIES
    ${SOURCE_PATH}
    ${Boost_INCLUDE_DIRS}
)


#-------------------------------------------------------------------------------
#                        External libraries settings.
#-------------------------------------------------------------------------------

# Set main external libraries to list.
list(
    APPEND SOURCE_EXTERNAL_LIBRARIES
    ${Boost_LIBRARIES}
)


#-------------------------------------------------------------------------------
#                          Library target settings.
#-------------------------------------------------------------------------------

# Add library target.
add_library(
    ${LIBRARY_TARGET} SHARED
    ${SOURCE_FILES}
)

# Add library include directories.
target_include_directories(
    ${LIBRARY_TARGET}
    PUBLIC ${SOURCE_INCLUDE_DIRECTORIES}
)

# Link library external libraries.
target_link_libraries(
    ${LIBRARY_TARGET}
    PUBLIC ${SOURCE_EXTERNAL_LIBRARIES}
)

# Set target properties.
set_target_properties(
    ${LIBRARY_TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION_MAJOR}
    SOVERSION 1
)

#-------------------------------------------------------------------------------
#                               Install settings.
#-------------------------------------------------------------------------------

# Define GNU standard installation directories.
include(GNUInstallDirs)

# Install binaries.
install(
    TARGETS ${LIBRARY_TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install include files.
install(
    DIRECTORY "${SOURCE_PATH}/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.hpp"
)
