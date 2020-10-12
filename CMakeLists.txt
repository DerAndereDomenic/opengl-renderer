cmake_minimum_required(VERSION "3.10")

project(OpenGLRenderer LANGUAGES CXX)

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
								 "OpenGL Renderer/src/IO/impl/PerlinNoise.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/FrameBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/IndexBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/RenderBuffer.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/Texture.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/VertexArray.cpp"
								 "OpenGL Renderer/src/OpenGLObjects/impl/VertexBuffer.cpp"
								 "OpenGL Renderer/src/Renderer/impl/Camera.cpp"
								 "OpenGL Renderer/src/Renderer/impl/ParticleRenderer.cpp"
								 "OpenGL Renderer/src/Renderer/impl/RenderWindow.cpp"
								 "OpenGL Renderer/src/Renderer/impl/TerrainCreator.cpp"
								 "OpenGL Renderer/src/Renderer/impl/TextRenderer.cpp"
								 "OpenGL Renderer/src/Shader/impl/Shader.cpp"
								 "OpenGL Renderer/src/Shader/impl/ShaderManager.cpp")