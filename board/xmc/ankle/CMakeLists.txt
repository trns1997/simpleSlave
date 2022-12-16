project(board)

add_library(${PROJECT_NAME}
	system_XMC4800.c
	esc_hw.c
)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC board_common soes_xmc4)
