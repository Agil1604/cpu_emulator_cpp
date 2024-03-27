cmake_minimum_required(VERSION 3.10)

project(cpu_emulator VERSION 2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("test")
add_subdirectory("include")
add_subdirectory("src")

set(SOURCE_LIB src/arch.cpp src/command.cpp src/parser.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(parser STATIC ${SOURCE_LIB})

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
