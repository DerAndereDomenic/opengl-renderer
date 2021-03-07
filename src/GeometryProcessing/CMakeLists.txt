add_executable(GeometryProcessing source.cpp)

target_link_libraries(GeometryProcessing OpenGLRendererLib)

if(WIN32)
	add_custom_command(TARGET GeometryProcessing POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
					$<TARGET_FILE_DIR:GeometryProcessing>)
					
	add_custom_command(TARGET GeometryProcessing POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${FREETYPE_LIB_DIR}/freetype.dll"
					$<TARGET_FILE_DIR:GeometryProcessing>)
endif()
