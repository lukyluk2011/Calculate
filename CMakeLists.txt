cmake_minimum_required(VERSION 3.10)

project(Calculate)

set(CMAKE_CXX_STANDARD 11)
set(SOURCES
    src/main.cpp
    api/calculate.cpp
)

# Sestavení spustitelného souboru
add_executable(Calculate ${SOURCES})

install(TARGETS Calculate DESTINATION /usr/local/bin)

message(STATUS "CMake configuration complete.")
