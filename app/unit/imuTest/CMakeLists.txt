set(PROJECT imu)

add_subdirectory(data_model)

set(TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/app/src/IMUFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/IMUFibre_t"
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_include_directories(${PROJECT}_test PUBLIC ${CMAKE_SOURCE_DIR}/app/inc)
target_link_libraries(${PROJECT}_test gtest_main infra hal data_model_imu)

add_test(${PROJECT}_test ${PROJECT}_test) 