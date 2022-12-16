project(ankle)

set(EXECUTABLE ${PROJECT_NAME}.elf)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_NAME}.map")

if(BOARD_NAME STREQUAL "ankle" OR BOARD_NAME STREQUAL "relax")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/board/xmc/common/XMC4800x2048.ld ")
endif()

add_executable(
    ${EXECUTABLE}
    main.cc
    objectlist.c
)

target_include_directories(${EXECUTABLE} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    data/${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${EXECUTABLE} board soes hal infra data_model app)

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

add_subdirectory (data_model)
