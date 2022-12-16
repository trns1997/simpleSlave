project(board_common)

add_library(${PROJECT_NAME}
	XMCLib/src/xmc_gpio.c
	XMCLib/src/xmc4_gpio.c
	XMCLib/src/xmc4_scu.c
	XMCLib/src/xmc_ecat.c
	XMCLib/src/xmc_spi.c
	XMCLib/src/xmc_usic.c
	XMCLib/src/xmc4_flash.c
	XMCLib/src/xmc_fce.c
	XMCLib/src/xmc_ccu4.c
	XMCLib/src/xmc_eth_mac.c
	XMCLib/src/xmc_eth_phy_ksz8081rnb.c
	syscalls.c
	startup_XMC4800.S
)

target_include_directories(${PROJECT_NAME} PUBLIC 
	XMCLib/inc 
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_CURRENT_SOURCE_DIR}/XMC4800x2048.ld")

add_subdirectory (soes_xmc4)