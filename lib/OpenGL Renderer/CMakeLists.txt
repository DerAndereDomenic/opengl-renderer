#set(OPENGL_RENDERER_RES_DIR "OpenGL Renderer/res")
#set(OPENGL_RENDERER_SHADER_DIR "OpenGL Renderer/src/Shader/GLShaders")

set(OPENGL_RENDERER_RELATIVE_PATH src)

file(GLOB_RECURSE _source_list LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.c*"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.h*")

add_library(OpenGLRendererLib "${_source_list}")
								 
#configure_file(OpenGLRendererConfig.h.in OpenGLRendererConfig.h)
#target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}")
								 


#file(COPY ${ASSIMP_LIB_DIR}/assimp-vc142-mtd.dll DESTINATION Debug)
#file(COPY ${FREETYPE_LIB_DIR}/freetype.dll DESTINATION Debug)
#file(COPY ${OPENGL_RENDERER_RES_DIR} DESTINATION Debug)
#file(COPY ${OPENGL_RENDERER_SHADER_DIR} DESTINATION Debug/src/Shader)
#file(COPY ${OPENGL_RENDERER_RES_DIR} DESTINATION /)
#file(COPY ${OPENGL_RENDERER_SHADER_DIR} DESTINATION src/Shader)

