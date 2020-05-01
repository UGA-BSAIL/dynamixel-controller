cmake_minimum_required(VERSION 2.8.4)
project(dynamixel_controller)

set(CMAKE_CXX_STANDARD 11)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(dynamixel-controller DynamixelIO.cpp DynamixelMotor.cpp dynio.h)
target_link_libraries(dynamixel-controller PRIVATE nlohmann_json::nlohmann_json)
