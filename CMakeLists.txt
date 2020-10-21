
project(minimilian)

cmake_minimum_required(VERSION 3.18)

add_library(minimilian STATIC src/minimilian.cpp)

target_include_directories(minimilian PRIVATE include/minimilian)

set_target_properties(minimilian PROPERTIES CXX_STANDARD 17)

