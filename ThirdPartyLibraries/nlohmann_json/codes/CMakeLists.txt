cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(jsontest)

add_executable(jsontest src/main.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/files/data.json
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/files/)

target_include_directories(jsontest PUBLIC ${CMAKE_SOURCE_DIR}/header/json/)