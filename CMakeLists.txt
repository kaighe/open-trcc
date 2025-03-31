cmake_minimum_required(VERSION 3.20)
project(open-trcc VERSION 1.0.0)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${INCLUDE_DIR})

add_library(trcc SHARED ${SRC_DIR}/trcc.cpp)
target_link_libraries(trcc ${LIBRARY_DIR}/libusb-1.0.a)