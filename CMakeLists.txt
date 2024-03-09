cmake_minimum_required(VERSION 3.26)
project(DA_WaterSupply)

set(CMAKE_CXX_STANDARD 20)

add_executable(DA_WaterSupply main.cpp
        src/Location.cpp
        src/City.cpp
        src/Reservoir.h
        src/Reservoir.cpp
        src/Station.h
        src/Station.cpp)
