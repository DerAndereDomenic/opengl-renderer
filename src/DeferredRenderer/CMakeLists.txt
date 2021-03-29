add_executable(DeferredRenderer source.cpp)

target_link_libraries(DeferredRenderer OpenGLRendererLib)

if(WIN32)
	add_custom_command(TARGET DeferredRenderer POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
					$<TARGET_FILE_DIR:DeferredRenderer>)
					
	add_custom_command(TARGET DeferredRenderer POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${FREETYPE_LIB_DIR}/freetype.dll"
					$<TARGET_FILE_DIR:DeferredRenderer>)
endif()