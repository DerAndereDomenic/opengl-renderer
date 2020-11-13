set(OPENGL_RENDERER_RELATIVE_PATH src)

#file(GLOB_RECURSE _source_list LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.c*"
#													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.h*"
#													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.vert"
#													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.frag"
#													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.geom"
#													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.glsl")

file(GLOB_RECURSE source_files LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.c*"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*Detail.h*")
file(GLOB_RECURSE header_files LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.h*")
file(GLOB_RECURSE shader_files LIST_DIRECTORIES false "${OPENGL_RENDERER_RELATIVE_PATH}/*.vert"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.frag"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.geom"
													  "${OPENGL_RENDERER_RELATIVE_PATH}/*.glsl")

source_group("Source" FILES ${source_files})
source_group("Header" FILES ${header_files})
source_group("Shader" FILES ${shader_files})

add_library(OpenGLRendererLib "${source_files}"
							  "${header_files}"
							  "${shader_files}")
								 

