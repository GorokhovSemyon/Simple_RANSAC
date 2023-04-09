cmake_minimum_required(VERSION 3.1)
project(RANSAC)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
find_package(Eigen3 REQUIRED)

add_executable(RANSAC src/main.cpp src/Model.cpp src/Model.h src/Ransac.cpp src/Ransac.h)

target_include_directories(RANSAC PRIVATE ${EIGEN3_INCLUDE_DIR})
