# ARM_GCC_BIN_FOLDER needs to be set as part of your environment variables 
# export ARM_GCC_BIN_FOLDER="/home/cedric/workspace_hw/gcc-arm-none-eabi-10.3-2021.10/bin"

CURRENT_DIR=$(shell pwd)

ARM_TOOLCHAIN_FILE = $(CURRENT_DIR)/board/arm-none-eabi-gcc.cmake

help:
	echo "make project product_name=(blinker/ankle) board_name=(relax/ankle)" 

project:
	mkdir -p build/$(board_name)
	cd build/$(board_name) && cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$(ARM_TOOLCHAIN_FILE) -DTOP_BIN_DIR:STRING=$(CURRENT_DIR)/build/$(board_name) -DBOARD_NAME:STRING=$(board_name) -DPRODUCT_NAME:STRING=$(product_name) -DMCU_NAME:STRING=XMC4800_F144x2048 $(CURRENT_DIR)
	cd build/$(board_name) && $(MAKE) -j8

unit:
	mkdir -p build/unit
	cd build/unit && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DTEST:BOOL=True $(CURRENT_DIR)
	cd build/unit && $(MAKE) -j8
	cd build/unit && ctest
	
clean:
	rm -rf build
