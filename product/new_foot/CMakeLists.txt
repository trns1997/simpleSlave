project(new_foot)
set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(
    ${EXECUTABLE}
    main.cc
    objectlist.c
    XMC_Slave.cc
    XMC_Timer.cc
    XMC_SPI.cc
    LSM6DSM.cc
    ForceSensor.cc
    ${CMAKE_BINARY_DIR}/sii_eeprom.o
)

execute_process(
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sii_eeprom.bin ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_OBJCOPY} -I binary -O elf32-littlearm -B arm sii_eeprom.bin sii_eeprom.o
)

target_include_directories(${EXECUTABLE} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${EXECUTABLE} board soes)


add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${SIZE_CMD} ${EXECUTABLE}
)
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND cp ${EXECUTABLE} ${BIN_PATH}/
        COMMAND ${OBJCOPY_CMD} -O ihex   ${BIN_PATH}/${EXECUTABLE} ${BIN_PATH}/${PROJECT_NAME}.hex
        COMMAND ${OBJCOPY_CMD} -O binary ${BIN_PATH}/${EXECUTABLE} ${BIN_PATH}/${PROJECT_NAME}.bin
) 
