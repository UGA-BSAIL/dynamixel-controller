cmake_minimum_required(VERSION 2.8.4)
project(dynamixel_controller)

set(CMAKE_CXX_STANDARD 11)

find_package(nlohmann_json 3.2.0 REQUIRED)

file(GLOB DYNAMIXEL_SDK
        "DynamixelSDK/src/DynamixelSDK.h"
        "DynamixelSDK/src/dynamixel_sdk/*.cpp"
        "DynamixelSDK/src/dynamixel_sdk/*.h")


add_library(dynamixel-controller main.cpp DynamixelIO.cpp DynamixelMotor.cpp ${DYNAMIXEL_SDK})
target_link_libraries(dynamixel-controller PRIVATE nlohmann_json::nlohmann_json)

add_executable(main main.cpp DynamixelIO.cpp DynamixelMotor.cpp ${DYNAMIXEL_SDK})
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)