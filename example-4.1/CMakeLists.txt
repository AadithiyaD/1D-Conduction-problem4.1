cmake_minimum_required(VERSION 3.10)
project(FVM-1D-conduction CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally specify where to look for Armadillo (MinGW/MSYS2 install)
set(ARMADILLO_INCLUDE_DIR "C:/msys64/mingw64/include")
set(ARMADILLO_LIBRARY "C:/msys64/mingw64/lib/libarmadillo.dll.a")
include_directories(${ARMADILLO_INCLUDE_DIR})

# Find the Armadillo package
# Use regular mode (not CONFIG) for MinGW / MSYS2
find_package(Armadillo REQUIRED)

# Add the main source file
add_executable(FVM-1D-conduction main.cpp)

# Link your executable to the Armadillo library
target_link_libraries(FVM-1D-conduction PRIVATE ${ARMADILLO_LIBRARY})
