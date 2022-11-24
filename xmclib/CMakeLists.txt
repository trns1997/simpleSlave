project(xmclib)

add_compile_options(-nostartfiles)

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
	CMSIS/Infineon/XMC4800_series/Source/system_XMC4800.c
	CMSIS/Infineon/XMC4800_series/Source/GCC/startup_XMC4800.S
)

target_include_directories(${PROJECT_NAME} PUBLIC XMCLib/inc CMSIS/Include CMSIS/Infineon/XMC4800_series/Include)
