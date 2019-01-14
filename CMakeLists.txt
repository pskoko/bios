cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17) 

project(LCP-inducing)


set(SOURCES_LIST
        "src/StringSuffixStructure.cpp"
        "src/SuffixStructure.cpp"
        "src/StarSuffixStructure.cpp"
        src/SAIS.cpp src/SAIS.hpp )

option(BUILD_DOC "Build documentation" OFF)
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

add_library(LCP_base ${SOURCES_LIST})

add_executable(LCP src/main.cpp)
target_link_libraries(LCP PUBLIC LCP_base)


option(BUILD_UNIT_TESTS "Build unit tests" ON)
if (BUILD_UNIT_TESTS)
    set(TEST_SOURCES
            tests/catch.cpp tests/SuffixStructureTest.cpp tests/StarSuffixStructureTest.cpp)
    enable_testing()

    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE tests/include)

    add_executable(LCP_test ${TEST_SOURCES})
    target_link_libraries(LCP_test PUBLIC LCP_base Catch)

    add_test(NAME UnitTest COMMAND LCP_test)

endif()
