cmake_minimum_required(VERSION 3.1)
project(RANSAC)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)

include_directories(.)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(RANSAC src/main.cpp src/Model.cpp src/Model.h src/Ransac.cpp src/Ransac.h)

target_include_directories(RANSAC PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(RANSAC ${Boost_LIBRARIES})
