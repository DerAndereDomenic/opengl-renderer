cmake_minimum_required(VERSION "3.8")

project(OpenGLRenderer LANGUAGES C CXX VERSION 1.0)

#==================================================================#
#							OPTIONS							   	   #
#==================================================================#
option(BUILD_TESTSCENE "Build the test scene for this renderer" ON)
option(BUILD_DANCINGBALL "Build the dancing ball animation" ON)
#This cant be enabled at the moment
option(BUILD_VR_VIEWER "Build a VR test viewer" OFF)
option(BUILD_WATERSCENE "Build a test scene displaying water rendering" ON)
option(BUILD_GEOMETRYPROCESSING "Build the geometry processing application" ON)
option(BUILD_DEFERREDRENDERER "Build the deferred rendering application" ON)
option(BUILD_DUMPPROJECT "Build a dump project to test different features" ON)
option(BUILD_PBR "Build the pbr application" ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(external/assimp)
add_subdirectory(external/freetype)
add_subdirectory(external/glfw)
add_subdirectory(external/DLogger)
if(BUILD_VR_VIEWER)
	set(OPENVR_LIB_DIR "external/openvr/lib/win64")
	set(OPENVR_BIN_DIR "external/openvr/bin/win64")
endif()

add_library(glad STATIC external/glad/src/glad.c)

include_directories("lib/OpenGL Renderer/src"
					${PROJECT_BINARY_DIR}
					${PROJECT_BINARY_DIR}/external/assimp/include
					external/assimp/include
					external/freetype/include
					external/glfw/include
					external/openvr/headers
					external/glm
					external/stb
					external/glad/include
					external/DLogger/include)
					
if(BUILD_VR_VIEWER)
	include_directories(external/openvr/headers)
endif()


link_directories(${OPENVR_LIB_DIR})
link_libraries(OpenGL::GL glad glfw assimp freetype DLogger)	
if(BUILD_VR_VIEWER)
	link_libraries(openvr_api.lib)
endif()
add_subdirectory(lib)

add_subdirectory(src)	
#link_directories("$CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")

set_target_properties(OpenGLRendererLib PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")