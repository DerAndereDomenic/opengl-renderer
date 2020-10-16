cmake_minimum_required(VERSION "3.10")

project(OpenGLRenderer LANGUAGES CXX VERSION 1.0)

option(BUILD_TESTSCENE "Build the test scene for this renderer" ON)

#==================================================================#
#							LIBRARIES							   #
#==================================================================#
set(OPENGL_RENDERER_INCLUDE_DIR "lib/OpenGL Renderer/src")
set(ASSIMP_INCLUDE_DIR "Dependencies/assimp/include")
set(FREETYPE_INCLUDE_DIR "Dependencies/freetype/include")
set(GLEW_INCLUDE_DIR "Dependencies/glew/include")
set(GLFW_INCLUDE_DIR "Dependencies/glfw/include")
set(GLM_INCLUDE_DIR "Dependencies/glm")
set(STB_INCLUDE_DIR "Dependencies/stb")

set(ASSIMP_LIB_DIR "Dependencies/assimp/lib")
set(FREETYPE_LIB_DIR "Dependencies/freetype/win64")
set(GLEW_LIB_DIR "Dependencies/glew/lib/Release/x64")
set(GLFW_LIB_DIR "Dependencies/glfw/lib-vc2019")

set(LIBS glfw3 opengl32 assimp-vc142-mtd glew32s freetype)

include_directories(${OPENGL_RENDERER_INCLUDE_DIR}
					${ASSIMP_INCLUDE_DIR}
					${FREETYPE_INCLUDE_DIR}
					${GLEW_INCLUDE_DIR}
					${GLFW_INCLUDE_DIR}
					${GLM_INCLUDE_DIR}
					${STB_INCLUDE_DIR})
													
link_directories(${ASSIMP_LIB_DIR}
				 ${FREETYPE_LIB_DIR}
				 ${GLEW_LIB_DIR}
				 ${GLFW_LIB_DIR})
												  
link_libraries("${LIBS}")

add_definitions(-DGLEW_STATIC)

add_subdirectory(lib)

#==================================================================#
#							EXECUTABLES							   #
#==================================================================#
add_subdirectory(src)



