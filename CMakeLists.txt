cmake_minimum_required(VERSION 3.12)
project(flash)

add_library(
    flash_module
    flash/flash.h
    flash/flash.c
    )

add_executable(${PROJECT_NAME} "flash_example.c")
target_link_libraries(${PROJECT_NAME} PRIVATE flash_module)
