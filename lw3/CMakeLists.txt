cmake_minimum_required(VERSION 3.10)
project(lw3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME}_lib ${SOURCES})
add_executable(${PROJECT_NAME}_exe main.cpp)

target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)









