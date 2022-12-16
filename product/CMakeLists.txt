
if(PRODUCT_NAME STREQUAL "ankle") 
	add_subdirectory (ankle)
elseif(PRODUCT_NAME STREQUAL "fallsafe")
	add_subdirectory (fallsafe)
elseif(PRODUCT_NAME STREQUAL "blinker")
	add_subdirectory (blinker)
endif()

