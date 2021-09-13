cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall")

# generate file required by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

project(main)

add_executable(main ./src/main.cpp ./src/board.cpp)
target_include_directories(main $ENV{INCLUDE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
