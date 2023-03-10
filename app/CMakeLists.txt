set(PROJECT app)

add_library(${PROJECT} SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BlinkLedFibre"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TimerFibre"
)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(app infra hal data_model)
