set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

add_compile_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork -mfpu=fpv5-d16 -mfloat-abi=hard --specs=nano.specs --specs=nosys.specs)
add_compile_options(-ffunction-sections -fdata-sections -fno-common)

add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

add_link_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork -mfpu=fpv5-d16 -mfloat-abi=hard --specs=nano.specs --specs=nosys.specs)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    message(STATUS "Release build")
    add_compile_options(-Ofast)
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    message(STATUS "Release build with debug info")
    add_compile_options(-Ofast -g)
elseif (CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    message(STATUS "Release build optimised for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Debug build")
    add_compile_options(-Og -g)
endif ()

add_link_options(-Wl,-gc-sections,--print-memory-usage)
add_link_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
