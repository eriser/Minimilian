
project(maximilian)

cmake_minimum_required(VERSION 3.18)

add_library(maximilian STATIC 
                        src/chorus.cpp
                        src/delayline.cpp
                        src/distortion.cpp
                        src/dynamic.cpp
                        src/env.cpp
                        src/envelope.cpp
                        src/envelopefollower.cpp
                        src/filter.cpp
                        src/flanger.cpp
                        src/map.cpp
                        src/maximilian.cpp
                        src/mix.cpp
                        src/oscillator.cpp
                        src/sample.cpp)

target_include_directories(maximilian PRIVATE include/maximilian)

set_target_properties(maximilian PROPERTIES CXX_STANDARD 17)

