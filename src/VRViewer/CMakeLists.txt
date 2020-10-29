add_executable(VRViewer source.cpp)

target_link_libraries(VRViewer OpenGLRendererLib)

if(WIN32)
	add_custom_command(TARGET VRViewer POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll"
					$<TARGET_FILE_DIR:VRViewer>)
					
	add_custom_command(TARGET VRViewer POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${FREETYPE_LIB_DIR}/freetype.dll"
					$<TARGET_FILE_DIR:VRViewer>)
					
	add_custom_command(TARGET VRViewer POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${OPENVR_BIN_DIR}/openvr_api.dll"
					$<TARGET_FILE_DIR:VRViewer>)
endif()