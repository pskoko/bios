cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17) 

project(LCP-inducing)

option(BUILD_UNIT_TESTS "Build unit tests" OFF)
#if (BUILD_UNIT_TESTS)
#    enable_testing()
#
#    add_library(Catch INTERFACE src/StarSuffixStructure.cpp src/StarSuffixStructure.hpp)
#    target_include_directories(Catch INTERFACE tests/unit/include)
#
#endif()

set(SOURCES_LIST
        "src/StarSuffixStructure.cpp"
        "src/StringSuffixStructure.cpp"
        "src/SuffixStructure.cpp"
        )

option(BUILD_DOC "Build documentation" ON)
if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOC_DIR ${CMAKE_BINARY_DIR}/doc/doxygen)
        configure_file(${CMAKE_SOURCE_DIR}/doc/doxygen/Doxyfile.in ${DOC_DIR}/Doxyfile @ONLY)
        add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM)
    else ()
        message("Doxygen not found.")
    endif ()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(LCP ${SOURCES_LIST})
