project(soes)

add_library (${PROJECT_NAME}
  esc.c
  esc.h
  esc_coe.c
  esc_coe.h
  esc_foe.c
  esc_foe.h
  esc_eoe.c
  esc_eoe.h
  esc_eep.c
  esc_eep.h
  ecat_slv.c
  ecat_slv.h
  options.h
  esc_hw.c
  esc_hw_eep.c
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC xmclib)




