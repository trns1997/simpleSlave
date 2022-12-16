set(PROJECT app)

set(APP_SOURCES
	src/time.cpp
    src/blink_led.cpp
    src/imu.cpp
    src/footsensor.cpp
    src/ethercat.cpp
	)

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