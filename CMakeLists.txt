cmake_minimum_required(VERSION 3.10)

# Sets the project name
project(simple-http-server VERSION 0.1)


include_directories(include)

# Manually add source files
set(SOURCES src/main.c)

# Wildcard add source files
# file(GLOB SOURCES src/*.c)

# Compile sources 
add_executable(simple-http-server ${SOURCES})
