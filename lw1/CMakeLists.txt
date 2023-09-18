cmake_minimum_required(VERSION 3.10)
project(LW1)

find_package(GTest REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main ${GTEST_LIBRARIES}
${CMAKE_THREAD_LIBS_INIT})
enable_testing()
add_test(tests main)