set(PROJECT imu)

set(APP_SOURCES
	${APP_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/imu.cpp
    PARENT_SCOPE
	)

IF(TEST)

set(TEST_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/imu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unit/imu_t.cpp
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_link_libraries(${PROJECT}_test gtest_main infra hal data_model_imu)
add_test(${PROJECT}_test ${PROJECT}_test) 

add_subdirectory(unit/data_model)

ENDIF()