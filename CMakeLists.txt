cmake_minimum_required(VERSION 3.8)
project(QtTemplate)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
#list(FILTER SOURCE_FILES EXCLUDE REGEX "/test/")

## Search for all QT packages that are needed
##
find_package(Qt5Core REQUIRED)

## All public headers (for a library) must go into the directory include
##
include_directories(include)

## Choose if you want to build an executable or a library
##
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
