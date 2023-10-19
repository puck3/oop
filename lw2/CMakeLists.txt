cmake_minimum_required(VERSION 3.10)
project(lw2)

find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}_lib twelve.cpp)
add_executable(${PROJECT_NAME}_exe main.cpp)
add_executable(${PROJECT_NAME}_test tests.cpp)

target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib ${GTEST_LIBRARIES})
