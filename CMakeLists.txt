cmake_minimum_required(VERSION 3.26)
project(water-supply)

set(CMAKE_CXX_STANDARD 17)

add_executable(water-supply main.cpp
        src/SupplyManagement.cpp
        src/SupplyManagement.h
        src/Graph.h
        src/Location.cpp
        src/Location.h
        src/Menu.cpp
        src/Menu.h
)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)

    # request to configure the file
    configure_file(${DOXYFILE} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
