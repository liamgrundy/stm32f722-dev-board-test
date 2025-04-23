cmake_minimum_required(VERSION 3.30)
project(stm32f722_dev_board_test C CXX ASM)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DSTM32F722xx)
add_compile_options(-Wall -Wextra -Werror $<$<COMPILE_LANGUAGE:CXX>:-Wno-volatile>)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F722RETX_FLASH.ld)
add_link_options(-T ${LINKER_SCRIPT})

add_subdirectory(lib)

add_executable(stm32f722_dev_board_test.elf main.cpp)
target_link_libraries(stm32f722_dev_board_test.elf PRIVATE cmsis_core cmsis_device_f7)
