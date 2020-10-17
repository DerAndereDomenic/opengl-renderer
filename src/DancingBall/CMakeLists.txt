add_executable(DancingBall source.cpp)

target_link_libraries(DancingBall OpenGLRendererLib)

if(WIN32)
	add_custom_command(TARGET DancingBall POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
					$<TARGET_FILE_DIR:DancingBall>)
					
	add_custom_command(TARGET DancingBall POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${FREETYPE_LIB_DIR}/freetype.dll"
					$<TARGET_FILE_DIR:DancingBall>)
endif()