cmake_minimum_required(VERSION 2.8)
project(adsVerbindung)

set(CMAKE_CXX_STANDARD 14)

add_library(adsVerbindung STATIC adsVerbindung.h adsVerbindung.cpp adsFunktionen.cpp adsFunktionen.h)
set_property(TARGET adsVerbindung PROPERTY POSITION_INDEPENDENT_CODE ON)

if (WIN32 OR MSVC)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ADS/x64/Debug ${LIBRARY_OUTPUT_PATH})
    target_link_libraries(adsVerbindung AdsLibd)
endif (WIN32 OR MSVC)

if (UNIX)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ADS)
    target_link_libraries(adsVerbindung AdsLib-Linux pthread)
endif (UNIX)

add_executable(adsVerbindungTest main.cpp)

target_link_libraries(adsVerbindungTest adsVerbindung)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ADS/AdsLib)