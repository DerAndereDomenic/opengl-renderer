#ifndef DATASTRUCTURE_RENDEROBJECT_H
#define DATASTRUCTURE_RENDEROBJECT_H

#include "DataStructure/Material.h"
#include "DataStructure/Mesh.h"
#include "Shader/Shader.h"

class RenderObject
{
public:
	/**
	*	\brief Creates an empty RenderObject
	*/
	RenderObject() = default;
	
	/**
	*	\brief Creates an object and sets the mesh, material and model
	*	\param[in] mesh The Mesh of the object
	*	\param[in] material The material of the object
	*	\param[in] model The model matrix
	*	\return The RenderObject
	*/
	static RenderObject createObject(Mesh mesh, Material material, glm::mat4 model);
	
	/**
	*	\brief Destroy the given RenderObject
	*	\param[in] object The RenderObject to be destroyed
	*/
	static void destroyObject(RenderObject& object);

	/**
	*	\brief Renders the object
	*	\param[in] The shader that should be used for rendering
	*/
	void render(Shader shader);
	
private:
	Mesh _mesh; /**<< The mesh of the object*/
	Material _material; /**<< The material of the object*/
	glm::mat4 _model; /**<< The model of the object*/
};

#endif