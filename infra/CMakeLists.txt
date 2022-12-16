set(PROJECT infra)

set(APP_SOURCES
    src/Fibre.cpp
    src/Threads.cpp
    src/DataItem.cpp
    src/crc.cpp
	)

add_library (${PROJECT} STATIC ${APP_SOURCES})
target_include_directories (${PROJECT} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/inc
	)
	
target_link_libraries(${PROJECT} data_model)	
	
IF(TEST)
	set(TEST_SOURCES
	    unit/Fibre_t.cpp
		)	
	add_executable (infra_test ${TEST_SOURCES} ${APP_SOURCES})
	target_link_libraries(infra_test gtest_main ${PROJECT})
	add_test(infra_test infra_test) 
ENDIF()

