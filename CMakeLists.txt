cmake_minimum_required(VERSION 3.10)
project(${CMAKE_BUILD_TYPE}-test)

enable_testing()

# Setup for Boost library
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.75 REQUIRED COMPONENTS unit_test_framework)

# Setup for FLTK library
find_package(FLTK REQUIRED NO_MODULE)
execute_process (
    COMMAND bash -c "fltk-config --use-images --version"
    OUTPUT_VARIABLE FLTK_VERSION   
)
execute_process (
    COMMAND bash -c "fltk-config --use-images --cxxflags"
    OUTPUT_VARIABLE FLTK_CXX_FLAGS
)
execute_process (
    COMMAND bash -c "fltk-config --use-images --ldflags"
    OUTPUT_VARIABLE FLTK_LD_FLAGS   
)
string(STRIP ${FLTK_CXX_FLAGS} FLTK_CXX_FLAGS)
string(STRIP ${FLTK_LD_FLAGS} FLTK_LD_FLAGS)
message(STATUS "FLTK ${FLTK_VERSION}")

# Setup for Graph_lib
set(GRAPH_INCLUDE_DIR "/usr/local/include/Graph_lib")
set(GRAPH_LIB_DIR "/usr/local/lib/Graph_lib")
set(GRAPH_LIB_LINK_DEBUG -L${GRAPH_LIB_DIR} -lGraph_libd)
set(GRAPH_LIB_LINK_RELEASE -L${GRAPH_LIB_DIR} -lGraph_lib)

# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall ${FLTK_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb -Og -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Include directories
include_directories(
    ${GRAPH_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    src_test/
    src_lf/
)

# Make src test library
file(GLOB SRC_TEST src_test/*.cpp)
# set(LIB_TEST_NAME "StaticSrcTest")
# add_library(${LIB_TEST_NAME} STATIC ${SRC_TEST})
# target_link_libraries(${LIB_TEST_NAME} debug ${GRAPH_LIB_LINK_DEBUG})
# target_link_libraries(${LIB_TEST_NAME} optimized  ${GRAPH_LIB_LINK_RELEASE})
# target_link_libraries(${LIB_TEST_NAME} general  ${FLTK_LD_FLAGS})

# # Make src LF library
file(GLOB SRC_LF src_lf/*.cpp)
# set(LIB_LF_NAME "StaticSrcLF")
# add_library(${LIB_LF_NAME} STATIC ${SRC_LF})
# target_link_libraries(${LIB_LF_NAME} debug ${GRAPH_LIB_LINK_DEBUG})
# target_link_libraries(${LIB_LF_NAME} optimized  ${GRAPH_LIB_LINK_RELEASE})
# target_link_libraries(${LIB_LF_NAME} general  ${FLTK_LD_FLAGS})

# Collect every library
set(COMMON_LIBS   
    ${FLTK_LD_FLAGS}
    Boost::unit_test_framework
    # ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${LIB_TEST_NAME}.a
    # ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${LIB_LF_NAME}.a
)

# Add executable
add_executable(${PROJECT_NAME} boost_auto_test_case.cpp ${SRC_LF} ${SRC_TEST})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE})

# Link libraries
target_link_libraries(${PROJECT_NAME} debug ${GRAPH_LIB_LINK_DEBUG})
target_link_libraries(${PROJECT_NAME} optimized ${GRAPH_LIB_LINK_RELEASE})
target_link_libraries(${PROJECT_NAME} general ${COMMON_LIBS})

# Add test
add_test(NAME ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}
)