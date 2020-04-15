#include "DataStructure/RenderObject.h"


RenderObject 
RenderObject::createObject(Mesh mesh, Material material, glm::mat4 model)
{

}

void 
RenderObject::destroyObject(RenderObject& object)
{

}

void 
RenderObject::render(Shader shader)
{

}

void 
RenderObject::setModel(glm::mat4 model)
{
	_model = model;
}