set(PROJECT app)

set(APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/time.cpp
)	

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
target_link_libraries (${PROJECT} LINK_PUBLIC infra hal)
	
IF(TEST)
	#set(TEST_SOURCES
	#    unit/test_t.cpp
	#	)	
	#add_executable (app_test ${TEST_SOURCES} ${APP_SOURCES})
	#target_link_libraries(app_test gtest_main ${PROJECT} infra)
	#add_test(app_test app_test) 
ENDIF()