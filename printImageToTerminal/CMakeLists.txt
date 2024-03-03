cmake_minimum_required(VERSION 3.28)
project(printImageToTerminal)

set(CMAKE_CXX_STANDARD 17)

add_executable(printImageToTerminal main.cpp
        Image/Script.cpp
        Image/PNG.cpp
        Image/Image.cpp
        Image/Color.cpp
        Image/iterators.cpp)
