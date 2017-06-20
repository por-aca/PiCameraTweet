SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)
cmake_minimum_required (VERSION 2.8) 
project (PiCameraTweet)

#Bring the headers into the project
include_directories(interface)

# Add the source files (Another option: file(GLOB SOURCES "source/*.cpp"))
set(SOURCES source/PiCameraTweet.cpp source/clearscreen.cpp)

# Add Libraries
find_package(raspicam REQUIRED)
find_package(OpenCV)

IF (OpenCV_FOUND AND raspicam_CV_FOUND)
MESSAGE(STATUS "Compiling PiCameraTweet...")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries (PiCameraTweet ${raspicam_CV_LIBS} curses )

ELSE()
MESSAGE(FATAL_ERROR "OpenCV Not Found in your System!")
ENDIF()
