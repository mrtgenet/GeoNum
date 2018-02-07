cmake_minimum_required(VERSION 3.0)
project(GeoNum-HalfEdge LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file ( GLOB HEADERS *.h *.hpp)
file ( GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
