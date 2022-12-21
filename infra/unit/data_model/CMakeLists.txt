set(PROJECT data_model_infra)

set(APP_SOURCES
    DataModel.cpp
	)

add_library (${PROJECT} STATIC ${APP_SOURCES})
target_include_directories (${PROJECT} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc
	)
