cmake_minimum_required(VERSION 3.20)
project(scads VERSION 0.1 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(blinky
    app/src/main.c
    third_party/tivaware/startup_gcc.c
)

set_target_properties(blinky PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS ${CMAKE_SOURCE_DIR}/third_party/tivaware/blinky.ld
)

target_compile_definitions(blinky PRIVATE PART_TM4C123GH6PM)
target_compile_options(blinky PRIVATE -O0 -g -Wall -Wextra)
target_include_directories(blinky PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/tivaware
    ${CMAKE_SOURCE_DIR}/app/include
)
target_link_options(blinky PRIVATE
    -T${CMAKE_SOURCE_DIR}/third_party/tivaware/blinky.ld
    -nostartfiles
)

add_custom_command(TARGET blinky POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "OBJCOPY=${CMAKE_OBJCOPY}"
    COMMAND ${CMAKE_COMMAND} -E echo "SIZE=${CMAKE_SIZE}"
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:blinky> $<TARGET_FILE_DIR:blinky>/blinky.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:blinky>
    COMMENT "Generating blinky.bin and printing size"
)

add_custom_target(flash
    COMMAND openocd -f board/ti_ek-tm4c123gxl.cfg
        -c "program $<TARGET_FILE:blinky> verify reset exit"
    DEPENDS blinky
    COMMENT "Flashing blinky.elf to tiva c launchpad via OpenOCD"
)
