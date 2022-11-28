cmake_minimum_required(VERSION 3.6)

set(CMAKE_TOOLCHAIN_FILE arm_toolchain.cmake)

set(SOURCE_FILES "")

project(xmc4800_simple_soes_slave LANGUAGES C CXX ASM)

add_subdirectory(xmclib)
add_subdirectory(soes)

add_executable(
    ${PROJECT_NAME}.elf
    main.cc
    objectlist.c
    syscalls.c
    XMC_Slave.cc
    XMC_Timer.cc
    XMC_SPI.cc
    LSM6DSM.cc
    ForceSensor.cc
    ${CMAKE_BINARY_DIR}/sii_eeprom.o
)
target_link_libraries(${PROJECT_NAME}.elf xmclib soes)

execute_process(
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sii_eeprom.bin ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_OBJCOPY} -I binary -O elf32-littlearm -B arm sii_eeprom.bin sii_eeprom.o
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
