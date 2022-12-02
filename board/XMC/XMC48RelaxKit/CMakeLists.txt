project(XMC48RelaxKit)

add_library(${PROJECT_NAME}
	system_XMC4800.c
	esc_hw.c
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC board)