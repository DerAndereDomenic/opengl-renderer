add_executable(TestScene source.cpp)

target_link_libraries(TestScene OpenGLRendererLib)

add_custom_command(TARGET TestScene POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_if_different
				   "${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
				   $<TARGET_FILE_DIR:TestScene>)
				   
add_custom_command(TARGET TestScene POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_if_different
				   "${FREETYPE_LIB_DIR}/freetype.dll"
				   $<TARGET_FILE_DIR:TestScene>)