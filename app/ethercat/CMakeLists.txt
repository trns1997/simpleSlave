set(PROJECT ethercat)

set(APP_SOURCES
	${APP_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ethercat.cpp
    PARENT_SCOPE
	)

IF(TEST)

set(TEST_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ethercat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unit/ethercat_t.cpp
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_link_libraries(${PROJECT}_test gtest_main infra hal soes_interface data_model_ethercat)
add_test(${PROJECT}_test ${PROJECT}_test) 

add_subdirectory(unit/data_model)

ENDIF()