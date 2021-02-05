add_executable(WaterScene source.cpp)

target_link_libraries(WaterScene OpenGLRendererLib)

if(WIN32)
	add_custom_command(TARGET WaterScene POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
					$<TARGET_FILE_DIR:WaterScene>)
					
	add_custom_command(TARGET WaterScene POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${FREETYPE_LIB_DIR}/freetype.dll"
					$<TARGET_FILE_DIR:WaterScene>)
endif()