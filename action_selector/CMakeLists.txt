# cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

PROJECT(ICUB_ACTION_SELECTOR C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
FIND_PACKAGE(YARP REQUIRED)
# add include directories
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS})
ADD_EXECUTABLE(action_selector action_selector.cpp ../class/YarpPortReader.cpp ../class/MotorController.cpp ../class/StringServer.cpp)
ADD_EXECUTABLE(action_selector_demo action_selector_demo.cpp ../class/YarpPortReader.cpp ../class/MotorController.cpp ../class/StringServer.cpp ../class/face_controller.cpp)
# we now add the YARP libraries to our project.
TARGET_LINK_LIBRARIES(action_selector ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(action_selector_demo ${YARP_LIBRARIES})
