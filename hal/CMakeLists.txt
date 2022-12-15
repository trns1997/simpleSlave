project(hal)

add_definitions(-DXMC4800_F144x2048)

add_library (${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SPI_Slave.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ForceSensor.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/LSM6DSM.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/soes_hooks.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/GPIO_XMC.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/SPI_XMC.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/TIMER_XMC.cc
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC board)


