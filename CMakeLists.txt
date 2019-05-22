cmake_minimum_required(VERSION 2.8)
project(adsVerbindung)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ADS/AdsLib)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ADS)

add_library(adsVerbindung SHARED adsVerbindung.h adsVerbindung.cpp adsFunktionen.cpp adsFunktionen.h)

target_link_libraries(adsVerbindung AdsLib-Linux)

set_property(TARGET adsVerbindung PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(adsVerbindungTest main.cpp)

target_link_libraries(adsVerbindungTest adsVerbindung pthread)