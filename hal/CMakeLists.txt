project(hal)

IF (NOT TEST)

	add_library (${PROJECT_NAME}
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SPI_Slave.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/ForceSensor.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/LSM6DSM.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/BMI088.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/SOES_hooks.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/GPIO_XMC.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/SPI_XMC.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/xmc/TIMER_XMC.cc
	  )
	  
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
	target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hw_mapping board infra)
	
ELSE()

	add_library (${PROJECT_NAME}
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/GPIO.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/ForceSensor.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/SPI_Slave.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/SPI.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/LSM6DSM.cc
	  ${CMAKE_CURRENT_SOURCE_DIR}/mock/SOES_hooks.cc
	  )
	  
	  target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
	  target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hw_mapping soes_interface)
	  
	  add_subdirectory(mock/mock_board)
ENDIF()
	





