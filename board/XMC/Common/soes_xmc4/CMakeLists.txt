project(board)

add_library (${PROJECT_NAME}
  src/esc_hw_eep.c
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC board_common soes)




