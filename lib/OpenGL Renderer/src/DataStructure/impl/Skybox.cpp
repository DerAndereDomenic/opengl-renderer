#include <DataStructure/Skybox.h>
#include <DataStructure/MeshHelper.h>
#include <OpenGLRendererConfig.h>

Skybox 
Skybox::createObject(Texture cubemap)
{
	Skybox result;
	result._cubemap = cubemap;
	result._cube = MeshHelper::cubeMesh(glm::vec4(1));
	result._cube.create();
	result._shader = Shader::createObject((SHADER_SOURCE_PATH + "Skybox.vert").c_str(),
		(SHADER_SOURCE_PATH + "Skybox.frag").c_str());
	result._shader.setInt("skybox", 0);
	return result;
}

void 
Skybox::destroyObject(Skybox& skybox)
{
	Texture::destroyObject(skybox._cubemap);
	Mesh::destroyObject(skybox._cube);
	Shader::destroyObject(skybox._shader);
}

void
Skybox::render(Camera camera) 
{
	glDepthMask(GL_FALSE);
	_shader.bind();
	_cubemap.bind(0);
	_shader.setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(camera.getView())),
		camera.getProjection());
	_cube.render();
	glDepthMask(GL_TRUE);
}
