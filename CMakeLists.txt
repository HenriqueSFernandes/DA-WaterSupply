cmake_minimum_required(VERSION 3.26)
project(water-supply)

set(CMAKE_CXX_STANDARD 17)

add_executable(water-supply main.cpp
        src/SupplyManagement.cpp
        src/SupplyManagement.h
        src/Graph.cpp
        src/Graph.h
        src/Location.cpp
        src/Location.h
        src/City.h
        src/City.cpp
        src/Reservoir.cpp
        src/Reservoir.h
        src/Station.h
        src/Station.cpp
        src/SpecialLocation.h


)