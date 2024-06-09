cmake_minimum_required(VERSION 3.10)

project(AmadeusEmployee VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(AmadeusEmployee src/main.cpp src/Employee.cpp src/tinyxml2.cpp)