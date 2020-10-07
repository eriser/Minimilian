
project(minimilian)

cmake_minimum_required(VERSION 3.18)

add_library(minimilian STATIC 
                        src/chorus.cpp
                        src/distortion.cpp
                        src/dynamic.cpp
                        src/env.cpp
                        src/envelope.cpp
                        src/envelopefollower.cpp
                        src/filter.cpp
                        src/flanger.cpp
                        src/map.cpp
                        src/minimilian.cpp
                        src/mix.cpp
                        src/oscillator.cpp
                        src/sample.cpp)

target_include_directories(minimilian PRIVATE include/minimilian)

set_target_properties(minimilian PROPERTIES CXX_STANDARD 17)

