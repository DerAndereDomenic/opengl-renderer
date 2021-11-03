#include "DataStructure/RenderObject.h"

 
RenderObject::RenderObject(const std::shared_ptr<Mesh>& mesh, const Material& material, const glm::mat4& model)
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
RenderObject::render(const std::shared_ptr<Shader>& shader)
{
	_material.bind(shader);
	shader->setMat4("M", _model);
	_mesh->render();
}

void 
RenderObject::setModel(const glm::mat4& model)
{
	_model = model;
}