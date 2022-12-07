set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX            arm-none-eabi )
set(CMAKE_C_COMPILER 			"${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-gcc" )
set(CMAKE_CXX_COMPILER 			"${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-g++" )
set(CMAKE_ASM_COMPILER 			"${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-g++" )
set(OBJCOPY_CMD                 "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-objcopy" )
set(SIZE_CMD                    "${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-size" )

set(OBJFLAGS "-Wall -nostartfiles -mfloat-abi=softfp -mcpu=cortex-m4 -mthumb ")
set(CPPFLAGS "${OBJFLAGS} -g3 -O0 -ffunction-sections -fdata-sections -std=c++11 -fpermissive ")
set(CFLAGS "${OBJFLAGS} -g3 -O0 -ffunction-sections -fdata-sections -std=gnu99 ")
set(ASMFLAGS "${OBJFLAGS} -x assembler-with-cpp ")

set(LINKERFLAGS "-nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs ")
                
set(CMAKE_C_FLAGS               ${CFLAGS})
set(CMAKE_CXX_FLAGS             ${CPPFLAGS})
set(CMAKE_ASM_FLAGS             ${ASMFLAGS})
set(CMAKE_EXE_LINKER_FLAGS      ${LINKERFLAGS})


