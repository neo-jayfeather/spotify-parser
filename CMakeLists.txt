cmake_minimum_required(VERSION 3.15)
project(SpotifyParser CXX)

# may set to an earlier standard, depends on what I do with this
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# TODO:
# change march=native when release build
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native -pthread")

include_directories(include ${LIBGIT2_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(parser ${SOURCES})
