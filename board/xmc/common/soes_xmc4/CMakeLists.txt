project(soes_xmc4)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sii_eeprom.bin DESTINATION ${TOP_BIN_DIR}/)

add_custom_command( 
	OUTPUT  ${TOP_BIN_DIR}/sii_eeprom.o
	PRE_BUILD
	WORKING_DIRECTORY ${TOP_BIN_DIR}
    COMMAND ${CMAKE_OBJCOPY} -I binary -O elf32-littlearm -B arm sii_eeprom.bin sii_eeprom.o
    COMMENT "${TOP_BIN_DIR}"
    DEPENDS ${TOP_BIN_DIR}/sii_eeprom.bin
)

add_library (${PROJECT_NAME}
  src/esc_hw_eep.c
  ${TOP_BIN_DIR}/sii_eeprom.o
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC board_common soes::soes)




