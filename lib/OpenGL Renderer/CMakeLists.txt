set(OPENGL_RENDERER_RELATIVE_PATH src)

file(GLOB_RECURSE _source_list LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.c*"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.h*")

add_library(OpenGLRendererLib "${_source_list}")
								 

