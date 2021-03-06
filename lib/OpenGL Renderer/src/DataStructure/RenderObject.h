#ifndef __OPENGLRENDERER_DATASTRUCTURE_RENDEROBJECT_H
#define __OPENGLRENDERER_DATASTRUCTURE_RENDEROBJECT_H

#include "DataStructure/Material.h"
#include "DataStructure/Mesh.h"
#include "Shader/Shader.h"
#include <memory>

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
	*/
	RenderObject(const std::shared_ptr<Mesh>& mesh, const Material& material, const glm::mat4& model);
	
	/**
	*	\brief Destroy the given RenderObject
	*/
	~RenderObject();

	/**
	*	\brief Renders the object
	*	\param[in] shader The shader that should be used for rendering
	*/
	void render(const std::shared_ptr<Shader>& shader);

	/**
	*	\brief Update the model matrix
	*	\param[in] model The new model matrix
	*/
	void setModel(const glm::mat4& model);

	/**
	*	\brief Returns the attached material
	*/
	inline Material& getMaterial() { return _material; }
	
private:
	std::shared_ptr<Mesh> _mesh; /**<< The mesh of the object*/
	Material _material; /**<< The material of the object*/
	glm::mat4 _model = glm::mat4(1); /**<< The model of the object*/
};

#endif