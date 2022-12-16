project(soes)

add_library (${PROJECT_NAME}
  src/esc.c
  src/esc_coe.c
  src/esc_foe.c
  src/esc_eoe.c
  src/esc_eep.c
  src/ecat_slv.c
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC soes_xmc4)




