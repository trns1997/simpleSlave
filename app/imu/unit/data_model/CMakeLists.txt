set(PROJECT data_model_imu)

set(DATA_SOURCES
    DataModel.cpp
	)

add_library (${PROJECT} STATIC ${DATA_SOURCES})
target_include_directories (${PROJECT} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	)
target_link_libraries(${PROJECT} infra)