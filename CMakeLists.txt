cmake_minimum_required(VERSION 3.12)
project(flash_project)

add_library(
    flash
    flash/flash.h
    flash/flash.c
    )

add_library(
    flash_driver
    flash/flash_driver.h
    flash/flash_driver.c
    )

add_executable(${PROJECT_NAME} "flash_example.c")
target_link_libraries(${PROJECT_NAME} PRIVATE flash flash_driver)
