project(LoraApp)
cmake_minimum_required(VERSION 3.7)

file(GLOB lib_SRC "main.cpp" "controller.cpp" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} ${lib_SRC})


target_link_libraries(${PROJECT_NAME} wiringPi gtest pthread)
set(gtest_disable_pthreads on)
