#include <DataStructure/Skybox.h>
#include <DataStructure/MeshHelper.h>
#include <Shader/ShaderManager.h>
#include <Core/GLFunctions.h>

Skybox 
Skybox::createObject(std::shared_ptr<Texture> cubemap)
{
	Skybox result;
	result._cubemap = cubemap;
	result._cube = MeshHelper::cubeMesh(glm::vec4(1));
	result._cube.create();

	ShaderManager::instance()->addShader("Skybox");
	ShaderManager::instance()->getShader("Skybox")->bind();
	ShaderManager::instance()->getShader("Skybox")->setInt("skybox", 0);

	return result;
}

void 
Skybox::destroyObject(Skybox& skybox)
{
	Mesh::destroyObject(skybox._cube);
}

void
Skybox::render(Camera camera) 
{
	GL::disableDepthWriting();
	ShaderManager::instance()->getShader("Skybox")->bind();
	_cubemap->bind(0);
	ShaderManager::instance()->getShader("Skybox")->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(camera.getView())),
		camera.getProjection());
	_cube.render();
	GL::enableDepthWriting();
}

void
Skybox::render(const glm::mat4& view, const glm::mat4& projection)
{
	GL::disableDepthWriting();
	ShaderManager::instance()->getShader("Skybox")->bind();
	_cubemap->bind(0);
	ShaderManager::instance()->getShader("Skybox")->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(view)),
		projection);
	_cube.render();
	GL::enableDepthWriting();
}
