IF (NOT TEST)

	add_subdirectory(xmc/common)
	add_subdirectory(xmc/${BOARD_NAME})

ELSE()
  	add_subdirectory(mock)
ENDIF()