set(PROJECT data_model)

add_library (${PROJECT} INTERFACE)
target_include_directories ( ${PROJECT} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
