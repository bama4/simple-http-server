cmake_minimum_required(VERSION 3.10)

project(utils VERSION 0.1)

include_directories(include)

# Add all source files in src
file(GLOB SOURCES src/*.c)

# Enable all compile options
add_compile_options(-Wall -Wextra -pedantic -Werror)

# Options for test run
OPTION(TEST "Test mode" OFF)

# Places output in bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add utils_test
if(TEST)
	file(GLOB TEST_SOURCES test/*.c)
	include_directories(test)
	add_executable(utils_test ${SOURCES} ${TEST_SOURCES})

	enable_testing()
	add_test(utils_test ${CMAKE_BINARY_DIR}/bin/utils_test)
	set_tests_properties(utils_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
endif()

add_library(utils SHARED ${SOURCES})
