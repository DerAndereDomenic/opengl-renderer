set(OPENGL_RENDERER_RELATIVE_PATH src)

file(GLOB_RECURSE _source_list LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.c*"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.h*"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.vert"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.frag"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.geom"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.glsl")

add_library(OpenGLRendererLib "${_source_list}")
								 

