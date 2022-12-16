
if(BOARD_NAME STREQUAL "relax")
	add_subdirectory (xmc/common)
	add_subdirectory (xmc/relax)
elseif(PRODUCT_NAME STREQUAL "ankle")
	add_subdirectory (xmc/common)
	add_subdirectory (xmc/ankle)
endif()

