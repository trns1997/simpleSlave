project(hal)

add_definitions(-DXMC4800_F144x2048)

add_library (${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/GPIO_XMC.cc
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC board)


