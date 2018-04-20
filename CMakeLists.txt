cmake_minimum_required (VERSION 2.6)

project (security)

set (security_VERSION_MAJOR 0)
set (security_VERSION_MINOR 1)
set (CMAKE_CXX_STANDAR 11)
set (CMAKE_BUILD_TYPE Debug)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(security main.cpp include/encode.h include/encode.cpp include/correction.cpp include/correction.h)

