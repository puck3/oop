cmake_minimum_required(VERSION 3.10)
project(LW1)

find_package(GTest REQUIRED)

add_library(${CMAKE_PROJECT_NAME}_lib vowels_count.cpp)
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
add_executable(${CMAKE_PROJECT_NAME}_test tests.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME}_lib ${GTEST_LIBRARIES})
