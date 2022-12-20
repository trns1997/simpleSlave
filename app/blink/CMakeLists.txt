set(PROJECT blink)

set(APP_SOURCES
	${APP_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/blink_led.cpp
    PARENT_SCOPE
	)

IF(TEST)

set(TEST_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/blink_led.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unit/blink_led_t.cpp
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_link_libraries(${PROJECT}_test gtest_main infra hal data_model_blink)
target_include_directories (${PROJECT}_test PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/unit/data_model 
	)
add_test(${PROJECT}_test ${PROJECT}_test) 

add_subdirectory(unit/data_model)

ENDIF()

