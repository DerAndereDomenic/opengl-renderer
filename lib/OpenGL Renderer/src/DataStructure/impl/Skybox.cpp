#include <DataStructure/Skybox.h>
#include <DataStructure/MeshHelper.h>
#include <Shader/ShaderManager.h>
#include <Core/GLFunctions.h>

 Skybox::Skybox(std::shared_ptr<Texture> cubemap)
{
	_cubemap = cubemap;
	_cube = MeshHelper::cubeMesh(glm::vec4(1));
	_cube->create();

	ShaderManager::addShader("Skybox");
	ShaderManager::getShader("Skybox")->bind();
	ShaderManager::getShader("Skybox")->setInt("skybox", 0);
}

void
Skybox::render(std::shared_ptr<Camera> camera) 
{
	GL::disableDepthWriting();
	ShaderManager::getShader("Skybox")->bind();
	_cubemap->bind(0);
	ShaderManager::getShader("Skybox")->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(camera->getView())),
		camera->getProjection());
	_cube->render();
	GL::enableDepthWriting();
}

void
Skybox::render(const glm::mat4& view, const glm::mat4& projection)
{
	GL::disableDepthWriting();
	ShaderManager::getShader("Skybox")->bind();
	_cubemap->bind(0);
	ShaderManager::getShader("Skybox")->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(view)),
		projection);
	_cube->render();
	GL::enableDepthWriting();
}
