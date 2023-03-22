set(PROJECT app)

add_library(${PROJECT} SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TimerFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EtherCatFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/IMUFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ForceSensorFibre"
)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(app infra hal data_model)
