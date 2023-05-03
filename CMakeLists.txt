cmake_minimum_required(VERSION 3.15.3)

project(simple_slave C CXX ASM)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(mtb-xmclib-cat3)

IF(TEST)
	enable_testing()

	# GoogleTest requires at least C++14
	set(CMAKE_CXX_STANDARD 14)
	include(FetchContent)
	FetchContent_Declare(
	  googletest
	  GIT_REPOSITORY https://github.com/google/googletest.git
	  GIT_TAG release-1.12.1
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
	include(CTest)
	
	add_subdirectory (infra)
	add_subdirectory (app)
	add_subdirectory (hal)
	add_subdirectory (board)
	add_subdirectory (lib)
	
ELSE()

add_subdirectory (board)
add_subdirectory (product)
add_subdirectory (lib)
add_subdirectory (hal)
add_subdirectory (infra)
add_subdirectory (app)

ENDIF()


