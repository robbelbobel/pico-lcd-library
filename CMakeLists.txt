cmake_minimum_required(VERSION 3.13)

include(cmake/pico_sdk_import.cmake)

project(lcd C CXX ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/lcd.cpp
	)

target_link_libraries(${PROJECT_NAME} pico_stdlib)

pico_add_extra_outputs(${PROJECT_NAME})