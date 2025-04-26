set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)
if (CMAKE_CROSSCOMPILING)
    set(FREERTOS_PORT "GCC_ARM_CM7" CACHE STRING "" FORCE)
endif()

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/include/freertos)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)

FetchContent_MakeAvailable(freertos_kernel)
