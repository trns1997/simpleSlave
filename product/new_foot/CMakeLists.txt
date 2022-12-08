project(new_foot)
set(EXECUTABLE ${PROJECT_NAME}.elf)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_NAME}.map")

if(BOARD_NAME STREQUAL "Ankle" OR BOARD_NAME STREQUAL "Relax")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/board/XMC/Common/XMC4800x2048.ld ")
	# NEEDED AS MAIN STILL NEEDS ACCESS TO XMC HEADER FILES
	add_definitions(-DXMC4800_F144x2048)
endif()


add_executable(
    ${EXECUTABLE}
    main.cc
    soes_hooks.cc
    objectlist.c
    ${CMAKE_BINARY_DIR}/sii_eeprom.o
)

execute_process(
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sii_eeprom.bin ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_OBJCOPY} -I binary -O elf32-littlearm -B arm sii_eeprom.bin sii_eeprom.o
)

target_include_directories(${EXECUTABLE} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${EXECUTABLE} board soes hal)


add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${SIZE_CMD} ${EXECUTABLE}
)
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND cp ${EXECUTABLE} ${CMAKE_BINARY_DIR}/
        COMMAND ${OBJCOPY_CMD} -O ihex   ${CMAKE_BINARY_DIR}/${EXECUTABLE} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
        COMMAND ${OBJCOPY_CMD} -O binary ${CMAKE_BINARY_DIR}/${EXECUTABLE} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
) 
