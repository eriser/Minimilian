
project(maximilian)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(stb_vorbis SHARED deps/github.com/kalven/stb_vorbis/stb_vorbis.c)
target_include_directories(stb_vorbis PRIVATE deps/github.com/kalven/stb_vorbis)

add_library(maximilian SHARED 
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

target_link_libraries(maximilian stb_vorbis)
target_include_directories(maximilian PRIVATE 
        include/maximilian 
        deps/github.com/kalven/stb_vorbis)

set_target_properties(maximilian PROPERTIES CXX_STANDARD 17)

add_subdirectory(lua)

