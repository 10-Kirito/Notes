#!/bin/bash

# Set the build directory
BUILD_DIR="build"

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Navigate to the build directory
cd $BUILD_DIR

# Run CMake to generate the build files
cmake ..

# Build the project
make
# Clear all compile output
clear

# Run the executable
./jsontest