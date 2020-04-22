#include <DataStructure/Skybox.h>
#include <DataStructure/MeshHelper.h>

Skybox 
Skybox::createObject(Texture cubemap)
{
	Skybox result;
	result._cubemap = cubemap;
	result._cube = MeshHelper::cubeMesh(glm::vec4(1));
	result._cube.create();
	result._shader = Shader::createObject("src/Shader/GLShaders/Skybox.vert",
		"src/Shader/GLShaders/Skybox.frag");
	return result;
}

void 
Skybox::destroyObject(Skybox& skybox)
{

}

void
Skybox::render(Camera camera) 
{

}
