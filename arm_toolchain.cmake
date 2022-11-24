set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_EXECUTABLE_SUFFIX "")
set(BAREMETAL_ARM_TOOLCHAIN_PATH "")

set(CMAKE_C_COMPILER ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY ${BAREMETAL_ARM_TOOLCHAIN_PATH}arm-none-eabi-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

set(DEVICE "XMC4800")
set(VARIANT "F144x2048")
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/xmclib/CMSIS/Infineon/XMC4800_series/Source/GCC/XMC4800x2048.ld")
set(GLOBALFLAGS "-D${DEVICE}_${VARIANT} -MP -MD -MT -g ")
set(ARCHFLAGS "-nostartfiles -mfloat-abi=softfp -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g3 -O0 -ffunction-sections -fdata-sections -pipe")
set(OBJFLAGS "-Wall -fmessage-length=0 -Wa,-adhlns=${CMAKE_BINARY_DIR}/@.lst ${ARCHFLAGS}")
set(CPPFLAGS "${GLOBALFLAGS} ${OBJFLAGS} -std=gnu17")
set(CFLAGS "${GLOBALFLAGS} ${OBJFLAGS} -std=gnu99")
set(ASMFLAGS "${GLOBALFLAGS} ${OBJFLAGS} -x assembler-with-cpp")
set(OBJCPYFLAGS "-I binary -O elf32-littlearm -B arm")
set(LINKERFLAGS "-nostartfiles -T${LINKER_SCRIPT}  -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map")

set(CMAKE_CXX_FLAGS "${CPPFLAGS}" CACHE INTERNAL "")
set(CMAKE_ASM_FLAGS "${ASMFLAGS}" CACHE INTERNAL "")
set(CMAKE_C_FLAGS "${CFLAGS}" CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS "${LINKERFLAGS}" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
