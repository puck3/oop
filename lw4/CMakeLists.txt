cmake_minimum_required(VERSION 3.10)
project(lw4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
# set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

add_executable(${PROJECT_NAME}_exe main.cpp)
# add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})

# target_link_libraries(${PROJECT_NAME}_test PRIVATE ${GTEST_LIBRARIES})
