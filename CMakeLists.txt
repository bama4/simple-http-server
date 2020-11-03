cmake_minimum_required(VERSION 3.10)

project(simple_http_server VERSION 0.1)

add_subdirectory(http)
add_subdirectory(socket_tcp_manager)

include_directories(http/include socket_tcp_manager/include simple_http_server/include)

# Places output in bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCES simple_http_server/src/*.c)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(simple_http_server ${SOURCES})

target_link_libraries(simple_http_server socket_tcp_manager)
target_link_libraries(simple_http_server http)
