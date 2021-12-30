cmake_minimum_required(VERSION 3.16.3)
project(picture_frame)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
#set_property(TARGET tgt PROPERTY CXX_STANDARD 17)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)

set(CMAKE_FIND_ROOT_PATH /opt/pi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

