set(PROJECT app)

IF(NOT TEST)

add_library(${PROJECT} SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TimerFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EtherCatFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/IMUFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BMI088Fibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BMI323Fibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ForceSensorFibre"
)

target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT} infra hal data_model)

ELSE()

add_subdirectory(unit)

ENDIF()