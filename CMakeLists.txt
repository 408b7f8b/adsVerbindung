cmake_minimum_required(VERSION 2.8)
project(adsVerbindung)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)

SET(CMAKE_VERBOSE_MAKEFILE:BOOL=ON)

ExternalProject_Add(ADS
        GIT_REPOSITORY https://github.com/Beckhoff/ADS.git
        CONFIGURE_COMMAND ""
        BUILD_IN_SOURCE 1
        BUILD_COMMAND make -j4
        INSTALL_COMMAND cp AdsLib-Linux.a libAdsLib-Linux.a
        )

include_directories(${CMAKE_BINARY_DIR}/ADS-prefix/src/ADS/AdsLib)

add_library(adsVerbindung STATIC adsVerbindung.h adsVerbindung.cpp adsFunktionen.cpp adsFunktionen.h)
set_property(TARGET adsVerbindung PROPERTY POSITION_INDEPENDENT_CODE ON)

if (WIN32 OR MSVC)
    link_directories(${CMAKE_BINARY_DIR}/ADS-prefix/src/ADS/x64/Debug ${LIBRARY_OUTPUT_PATH})
    target_link_libraries(adsVerbindung AdsLibd)
endif (WIN32 OR MSVC)

if (UNIX)
    link_directories(${CMAKE_BINARY_DIR}/ADS-prefix/src/ADS)
    target_link_libraries(adsVerbindung AdsLib-Linux pthread)
endif (UNIX)

add_executable(adsVerbindungTest main.cpp)
target_link_libraries(adsVerbindungTest adsVerbindung)