project(board_common)

add_library(${PROJECT_NAME}
	syscalls.c
	startup_XMC4800.S
)

target_link_libraries(${PROJECT_NAME} PUBLIC board mtb-xmclib-cat3::mtb-xmclib-cat3)

add_subdirectory (soes_xmc4)