# ARM_GCC_BIN_FOLDER needs to be set as part of your environment variables 
# export ARM_GCC_BIN_FOLDER="/home/cedric/workspace_hw/gcc-arm-none-eabi-10.3-2021.10/bin"

CURRENT_DIR=$(shell pwd)

ARM_TOOLCHAIN_FILE = $(CURRENT_DIR)/board/arm-none-eabi-gcc.cmake


# Default config relax                                                                                                                                                                                   
config: config-relax

# Default build relax
relax: build-relax

ankle: build-ankle

# Default clean relax                                                                                                                                                                                    
clean:
	rm -rf build

# Config and build for relax
config-relax: build/relax/Makefile
build/relax/Makefile:
	mkdir -p build/relax
	cd build/relax && cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$(ARM_TOOLCHAIN_FILE) -DTOP_BIN_DIR:STRING=$(CURRENT_DIR)/build/relax -DBOARD_NAME:STRING=Relax -DPRODUCT_NAME:STRING=Blinker -DMCU_NAME:STRING=XMC4800_F144x2048 $(CURRENT_DIR)

config-ankle: build/ankle/Makefile
build/ankle/Makefile:
	mkdir -p build/ankle
	cd build/ankle && cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$(ARM_TOOLCHAIN_FILE) -DTOP_BIN_DIR:STRING=$(CURRENT_DIR)/build/ankle -DPRODUCT_NAME:STRING=Ankle -DBOARD_NAME:STRING=Ankle -DMCU_NAME:STRING=XMC4800_F144x2048 $(CURRENT_DIR)

build-relax: config-relax
	cd build/relax && $(MAKE) -j8
	
build-ankle: config-ankle
	cd build/ankle && $(MAKE) -j8

clean-relax:
	rm -rf build/relax
