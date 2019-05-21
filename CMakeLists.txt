cmake_minimum_required(VERSION 2.8)
project(ADS_Test)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/dbb/Schreibtisch/git/ADS/AdsLib)

link_directories(/home/dbb/Schreibtisch/git/ADS)
#link_libraries(AdsLib-Linux pthread)


add_library(ADS SHARED adsVerbindung.h adsVerbindung.cpp adsFunktionen.cpp adsFunktionen.h)

target_link_libraries(ADS AdsLib-Linux pthread)

set_property(TARGET ADS PROPERTY POSITION_INDEPENDENT_CODE ON)



add_executable(ADS_Test main.cpp)

target_link_libraries(ADS_Test ADS)