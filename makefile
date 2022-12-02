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
	cd build/relax && cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$(ARM_TOOLCHAIN_FILE) -DCMAKE_BUILD_TYPE:STRING=release -DBOARD_NAME:STRING=Relax $(CURRENT_DIR)


config-ankle: build/ankle/Makefile
build/ankle/Makefile:
	mkdir -p build/ankle
	cd build/ankle && cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$(ARM_TOOLCHAIN_FILE) -DCMAKE_BUILD_TYPE:STRING=release -DBOARD_NAME:STRING=Ankle $(CURRENT_DIR)

build-relax: config-relax
	cd build/relax && $(MAKE) VERBOSE=1 -j8
	
build-ankle: config-ankle
	cd build/ankle && $(MAKE) VERBOSE=1 -j8

clean-relax:
	rm -rf build/relax
