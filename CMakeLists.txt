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
set(SHADER_SOURCE_PATH "\"${CMAKE_SOURCE_DIR}/lib/OpenGL Renderer/src/Shader/GLShaders/\"")
set(RESOURCE_PATH "\"${CMAKE_SOURCE_DIR}/res/\"")
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


link_libraries(OpenGL::GL glad glfw assimp freetype DLogger)	
add_subdirectory(lib)

add_subdirectory(src)	
#link_directories("$CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")

configure_file(OpenGLRendererConfig.h.in OpenGLRendererConfig.h)