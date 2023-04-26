set(PROJECT blink)

add_subdirectory(data_model)

set(TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/app/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/BlinkLedFibre_t"
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_include_directories(${PROJECT}_test PUBLIC ${CMAKE_SOURCE_DIR}/app/inc)
target_link_libraries(${PROJECT}_test gtest_main infra hal data_model_blink)

add_test(${PROJECT}_test ${PROJECT}_test) 