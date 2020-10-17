#include <DataStructure/Skybox.h>
#include <DataStructure/MeshHelper.h>
#include <Shader/ShaderManager.h>

Skybox 
Skybox::createObject(Texture cubemap)
{
	Skybox result;
	result._cubemap = cubemap;
	result._cube = MeshHelper::cubeMesh(glm::vec4(1));
	result._cube.create();

	ShaderManager::instance()->addShader("Skybox");
	ShaderManager::instance()->getShader("Skybox").bind();
	ShaderManager::instance()->getShader("Skybox").setInt("skybox", 0);

	return result;
}

void 
Skybox::destroyObject(Skybox& skybox)
{
	Texture::destroyObject(skybox._cubemap);
	Mesh::destroyObject(skybox._cube);
}

void
Skybox::render(Camera camera) 
{
	glDepthMask(GL_FALSE);
	ShaderManager::instance()->getShader("Skybox").bind();
	_cubemap.bind(0);
	ShaderManager::instance()->getShader("Skybox").setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(camera.getView())),
		camera.getProjection());
	_cube.render();
	glDepthMask(GL_TRUE);
}
