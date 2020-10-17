cmake_minimum_required(VERSION "3.10")

project(OpenGLRenderer LANGUAGES CXX VERSION 1.0)

#==================================================================#
#							OPTIONS							   	   #
#==================================================================#
option(BUILD_TESTSCENE "Build the test scene for this renderer" ON)
set(SHADER_SOURCE_PATH "\"${CMAKE_SOURCE_DIR}/lib/OpenGL Renderer/src/Shader/GLShaders/\"")
set(RESOURCE_PATH "\"${CMAKE_SOURCE_DIR}/lib/OpenGL Renderer/res/\"")

#==================================================================#
#							LIBRARIES							   #
#==================================================================#

set(OPENGL_RENDERER_INCLUDE_DIR "lib/OpenGL Renderer/src")
set(GLM_INCLUDE_DIR "Dependencies/glm")
set(STB_INCLUDE_DIR "Dependencies/stb")
set(FREETYPE_INCLUDE_DIR "Dependencies/freetype/include")
set(ASSIMP_INCLUDE_DIR "Dependencies/assimp/include")
set(GLEW_INCLUDE_DIR "Dependencies/glew/include")
set(GLFW_INCLUDE_DIR "Dependencies/glfw/include")

if(WIN32)
	if(MSVC)
		set(ASSIMP_LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/assimp/lib")
		set(FREETYPE_LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/freetype/win64")
		set(GLEW_LIB_DIR "Dependencies/glew/lib/Release/x64")
		set(GLFW_LIB_DIR "Dependencies/glfw/lib-vc2019")

		set(LIBS glfw3 opengl32 assimp-vc142-mtd glew32s freetype)
															
		link_directories(${ASSIMP_LIB_DIR}
						 ${FREETYPE_LIB_DIR}
						 ${GLEW_LIB_DIR}
						 ${GLFW_LIB_DIR})
														  
		link_libraries("${LIBS}")

		add_definitions(-DGLEW_STATIC)
	else()
		message(ONLY MSVC SUPPORTED)
	endif()

	set(WIN32_DEFINE define)
	set(UNIX_DEFINE undef)
elseif(UNIX)
	find_package(GLEW REQUIRED)

	set(OpenGL_GL_PREFERENCE GLVND)
	find_package(OpenGL REQUIRED)

	find_package(ASSIMP REQUIRED)

	find_package(PkgConfig REQUIRED)

	pkg_search_module(GLFW REQUIRED glfw3)

	find_package(Freetype REQUIRED)

	find_package(PNG REQUIRED)


	link_libraries(${GLFW_STATIC_LIBRARIES})
	link_libraries(-lpthread -lm)

	link_libraries(${GLEW_LIBRARIES})
	link_libraries(OpenGL::GL)

	link_libraries(${FREETYPE_LIBRARIES})

	link_libraries(${ASSIMP_LIBRARIES})

	link_libraries(${PNG_LIBRARY})
	link_libraries(-lz)

	set(WIN32_DEFINE undef)
	set(UNIX_DEFINE define)
else()
	message(NOT SUPPORTED)
endif()

include_directories(${OPENGL_RENDERER_INCLUDE_DIR}
					${ASSIMP_INCLUDE_DIR}
					${FREETYPE_INCLUDE_DIR}
					${GLEW_INCLUDE_DIR}
					${GLFW_INCLUDE_DIR}
					SYSTEM PRIVATE ${GLM_INCLUDE_DIR}
					${STB_INCLUDE_DIR}
					${PROJECT_BINARY_DIR})

add_subdirectory(lib)

#==================================================================#
#							EXECUTABLES							   #
#==================================================================#
add_subdirectory(src)



configure_file(OpenGLRendererConfig.h.in OpenGLRendererConfig.h)