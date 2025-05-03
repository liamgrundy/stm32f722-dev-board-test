add_executable(stm32f722_dev_board_test.elf main.c clock.c gpio.c)
target_link_libraries(stm32f722_dev_board_test.elf PRIVATE cmsis_core cmsis_device_f7 freertos_kernel)
