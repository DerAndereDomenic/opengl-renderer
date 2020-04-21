#include "DataStructure/RenderObject.h"


RenderObject 
RenderObject::createObject(Mesh mesh, Material material, glm::mat4 model)
{
	RenderObject result;
	result._mesh = mesh;
	result._material = material;
	result._model = model;

	return result;
}

void 
RenderObject::destroyObject(RenderObject& object)
{
	Mesh::destroyObject(object._mesh);
	Material::destroyObject(object._material);
	object._model = glm::mat4(1);
}

void 
RenderObject::render(RenderWindow window, Shader shader)
{
	_material.bind(shader);
	shader.setMat4("M", _model);
	_mesh.render();
}

void 
RenderObject::setModel(glm::mat4 model)
{
	_model = model;
}