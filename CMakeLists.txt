cmake_minimum_required(VERSION "3.10")

project(OpenGLRenderer LANGUAGES CXX)

set(OPENGL_RENDERER_INCLUDE_DIR "OpenGL Renderer/src")
set(ASSIMP_INCLUDE_DIR "Dependencies/assimp/include")
set(FREETYPE_INCLUDE_DIR "Dependencies/freetype/include")
set(GLEW_INCLUDE_DIR "Dependencies/glew/include")
set(GLFW_INCLUDE_DIR "Dependencies/glfw/include")
set(GLM_INCLUDE_DIR "Dependencies/glm")
set(STB_INCLUDE_DIR "Dependencies/stb")

set(ASSIMP_LIB_DIR "Dependencies/assimp/lib")
set(FREETYPE_LIB_DIR "Dependencies/freetype/win64")
set(GLEW_LIB_DIR "Dependencies/glew/lib/x64")
set(GLFW_LIB_DIR "Dependencies/glfw/lib-vc2019")

set(LIBS glfw3 opengl32 assimp-vc142-mtd glew32s freetype)

add_executable("${PROJECT_NAME}" "OpenGL Renderer/src/source.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/EnvironmentMap.cpp" 
								 "OpenGL Renderer/src/DataStructure/impl/Light.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/Material.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/Mesh.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/MeshHelper.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/RenderObject.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/Scene.cpp"
								 "OpenGL Renderer/src/DataStructure/impl/Skybox.cpp"
								 "OpenGL Renderer/src/IO/impl/KeyManager.cpp"
								 "OpenGL Renderer/src/IO/impl/ObjLoader.cpp"
								 "OpenGL Renderer/src/Math/impl/PerlinNoise.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/FrameBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/IndexBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/RenderBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/Texture.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/VertexArray.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/VertexBuffer.cpp"
								 "OpenGL Renderer/src/Renderer/impl/Camera.cpp"
								 "OpenGL Renderer/src/Renderer/impl/ParticleRenderer.cpp"
								 "OpenGL Renderer/src/Renderer/impl/RenderWindow.cpp"
								 "OpenGL Renderer/src/Renderer/impl/TerrainCreater.cpp"
								 "OpenGL Renderer/src/Renderer/impl/TextRenderer.cpp"
								 "OpenGL Renderer/src/Shader/impl/Shader.cpp"
								 "OpenGL Renderer/src/Shader/impl/ShaderManager.cpp")
								 
target_include_directories("${PROJECT_NAME}" PRIVATE "${OPENGL_RENDERER_INCLUDE_DIR}"
													 "${ASSIMP_INCLUDE_DIR}"
													 "${FREETYPE_INCLUDE_DIR}"
													 "${GLEW_INCLUDE_DIR}"
													 "${GLFW_INCLUDE_DIR}"
													 "${GLM_INCLUDE_DIR}"
													 "${STB_INCLUDE_DIR}")
													 
target_link_directories("${PROJECT_NAME}" PRIVATE "${ASSIMP_LIB_DIR}"
												  "${FREETYPE_LIB_DIR}"
												  "${GLEW_LIB_DIR}"
												  "${GLFW_LIB_DIR}")
												  
target_link_libraries("${PROJECT_NAME}" "${LIBS}")

add_definitions(-DGLEW_STATIC)

