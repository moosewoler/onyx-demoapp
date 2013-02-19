cmake_minimum_required (VERSION 2.6)
# Project Name.
project (onyx-demoapp)

# Additional cmake modules
set     (CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake_modules")

# pre-configure
include (mymacro)

message (STATUS "by MWO: CMAKE_SOURCE_DIR  = ${CMAKE_SOURCE_DIR}")
message (STATUS "by MWO: PROJECT_BINARY_DIR= ${PROJECT_BINARY_DIR}")
message (STATUS "by MWO: CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
# configure source code
add_subdirectory(src)
