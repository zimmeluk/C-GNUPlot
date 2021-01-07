# ------------------------------------ #
#                USAGE                 #
# ------------------------------------ #
# $ mkdir CPPlot_build                 #
# $ cd CPPlot_build                    #
# $ cmake ../src                       #
# $ cmake --build .                    #
# ------------------------------------ #

cmake_minimum_required(VERSION 3.10)

# project name
project(CPPlot VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# require out-of-source build
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# GLUT
find_package(GLUT REQUIRED)
message(STATUS "Found GLUT in ${GLUT_INCLUDE_DIR}")

# add include directory
set(INC_DIR "../include")

# add the executable
add_executable(CPPlot climate.cpp texture.cpp Menu.cpp ${INC_DIR}/Menu.h ${INC_DIR}/MenuItem.h ${INC_DIR}/texture.h)
target_include_directories(CPPlot PUBLIC ${INC_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(CPPlot PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})