# cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

PROJECT(ICUB_HEAD_TURNER C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
FIND_PACKAGE(YARP REQUIRED)
# add include directories
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
ADD_EXECUTABLE(head_motor_calculator head_motor_calculator.cpp ../class/ObjPosServer.cpp ../class/MotorCommandGenerator.cpp)
# we now add the YARP libraries to our project.
TARGET_LINK_LIBRARIES(head_motor_calculator ${YARP_LIBRARIES})
