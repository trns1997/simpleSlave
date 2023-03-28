set(PROJECT app)

IF(NOT TEST)

add_library(${PROJECT} SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TimerFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EtherCatFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/IMUFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ForceSensorFibre"
)

target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT} infra hal data_model)

ELSE()

add_subdirectory(unit/data_model)

set(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/BlinkLedFibre_t.cc"
)

add_executable (${PROJECT}_test ${TEST_SOURCES})
target_include_directories(${PROJECT}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT}_test gtest_main infra hal data_model)

add_test(${PROJECT}_test ${PROJECT}_test) 

ENDIF()