set(PROJECT app)

set(APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/time.cpp
)	

IF(NOT TEST)
if(PRODUCT_NAME STREQUAL "ankle") 
	add_subdirectory(imu)
	add_subdirectory(foot_sensor)
	add_subdirectory(ethercat)
elseif(PRODUCT_NAME STREQUAL "fallsafe")
	add_subdirectory(imu)
	add_subdirectory(blink)
elseif(PRODUCT_NAME STREQUAL "blinker")
	add_subdirectory(blink)
endif()

add_library (${PROJECT} OBJECT ${APP_SOURCES})
target_include_directories (${PROJECT} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/inc 
	)
target_link_libraries (${PROJECT} LINK_PUBLIC infra hal data_model)
	
ELSE()
	#add_subdirectory(imu)
	add_subdirectory(foot_sensor)
	#add_subdirectory(ethercat)
	add_subdirectory(blink)
	
	#add_executable (infra_test ${APP_SOURCES})
	#target_link_libraries(infra_test gtest_main ${PROJECT})
	#add_test(infra_test infra_test) 
ENDIF()
