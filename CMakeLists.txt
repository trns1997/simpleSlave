cmake_minimum_required(VERSION 3.15.3)

project(simple_slave C CXX ASM)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_NAME}.map")

set(BIN_PATH ${CMAKE_SOURCE_DIR}/build)

add_definitions(
	-DXMC4800_F144x2048
)
	
add_subdirectory (board)
add_subdirectory (product)
add_subdirectory (lib)




