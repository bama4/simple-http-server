cmake_minimum_required(VERSION 3.10)

project(socket_tcp_manager VERSION 0.1)

include_directories(include)

# Add all source files in src
file(GLOB SOURCES src/*.c)

# Enable all compile options
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(socket_tcp_manager STATIC ${SOURCES})
