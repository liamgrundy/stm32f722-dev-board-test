cmake_minimum_required(VERSION 3.30)
project(stm32f722_dev_board_test C CXX ASM)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DSTM32F722xx)
add_compile_options(-Wall -Wextra -Werror)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F722RETX_FLASH.ld)
add_link_options(-T ${LINKER_SCRIPT})

FetchContent_Declare( freertos_kernel
        GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        GIT_TAG        main
)

add_subdirectory(lib)

add_executable(stm32f722_dev_board_test.elf main.cpp)
target_link_libraries(stm32f722_dev_board_test.elf PRIVATE cmsis_core cmsis_device_f7 freertos_kernel)
