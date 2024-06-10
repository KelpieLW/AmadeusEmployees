#!/bin/bash

# Navigate to the directory of the script
cd "$(dirname "$0")"

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate to the build directory
cd build

# Remove previous CMake configuration files if they exist
if [ -f "CMakeCache.txt" ]; then
  rm CMakeCache.txt
fi

if [ -d "CMakeFiles" ]; then
  rm -rf CMakeFiles
fi

# Set the paths to the MSYS2 compilers
export CC=/c/msys64/ucrt64/bin/gcc.exe
export CXX=/c/msys64/ucrt64/bin/g++.exe

# Run CMake to configure the project with the MinGW Makefiles generator
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=$CC -DCMAKE_CXX_COMPILER=$CXX ..

# Check if CMake was successful
if [ $? -ne 0 ]; then
  echo "CMake configuration failed."
  exit 1
fi

# Build the project using the MinGW Makefiles generator
cmake --build .

# Check if the build was successful
if [ $? -ne 0 ]; then
  echo "Build failed."
  exit 1
fi



