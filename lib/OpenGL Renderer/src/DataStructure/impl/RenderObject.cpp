#include "DataStructure/RenderObject.h"

 
RenderObject::RenderObject(std::shared_ptr<Mesh> mesh, Material material, glm::mat4 model)
{
	_mesh = mesh;
	_material = material;
	_model = model;
}
 
RenderObject::~RenderObject()
{
	_model = glm::mat4(1);
}

void 
RenderObject::render(std::shared_ptr<Shader> shader)
{
	_material.bind(shader);
	shader->setMat4("M", _model);
	_mesh->render();
}

void 
RenderObject::setModel(glm::mat4 model)
{
	_model = model;
}