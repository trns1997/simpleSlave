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
	
IF(NOT TEST)

target_link_libraries(${PROJECT} data_model)	
	
ELSE()
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unit/data_model)

	set(TEST_SOURCES
	    unit/Fibre_t.cpp
	    unit/DataItem_t.cpp
		)	
	add_executable (${PROJECT}_test ${APP_SOURCES} ${TEST_SOURCES})
	target_link_libraries(${PROJECT}_test gtest_main data_model_infra)
	add_test(${PROJECT}_test ${PROJECT}_test) 
	
	target_include_directories (${PROJECT}_test PUBLIC
	    ${CMAKE_CURRENT_SOURCE_DIR}/inc 
	)
	
ENDIF()

