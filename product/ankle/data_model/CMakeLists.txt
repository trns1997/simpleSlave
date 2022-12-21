set(PROJECT data_model)

set(APP_SOURCES
    DataModel.cpp
	)

add_library (${PROJECT} STATIC ${APP_SOURCES})
target_include_directories (${PROJECT} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	)
target_link_libraries(${PROJECT} infra)