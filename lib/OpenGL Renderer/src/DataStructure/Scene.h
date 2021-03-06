#ifndef __OPENGLRENDERER_DATASTRUCTURE_SCENE_H
#define __OPENGLRENDERER_DATASTRUCTURE_SCENE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <DataStructure/Mesh.h>
#include <DataStructure/Material.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Light.h>
#include <DataStructure/Model.h>
#include <Shader/Shader.h>
#include <glm/glm.hpp>


class Scene
{
public:
	/**
	*	\brief Creates an empty scene
	*/
	Scene() = default;

	/**
	*	\brief Creates a scene with the given data to create RenderObjects
	*	\param[in] names The names of the objects (used to access them later from the scene)
	*	\param[in] meshes The vector with all the meshes from the scene
	*	\param[in] materials The material from the corresponding object
	*	\param[in] models The model matrix of the objects
	*	\note: The indices have to coincide in all vectors with the given object
	*		   So (names[i], meshes[i], materials[i], models[i]) defines one object
	*/
	Scene(const std::vector<std::string>& names,
		  const std::vector<std::shared_ptr<Mesh>>& meshes,
		  const std::vector<Material>& materials,
		  const std::vector<glm::mat4>& models);

	/**
	*	\brief Creates a scene with the given data to create RenderObjects
	*	\param[in] names The names of the objects (used to access them later from the scene)
	*	\param[in] models The vector with all the models from the scene
	*	\note: The indices have to coincide in all vectors with the given object
	*		   So (names[i], models[i]) defines one object
	*/
	Scene(const std::vector<std::string>& names,
		  const std::vector<std::shared_ptr<Model>>& models);

	/**
	*	\brief Destroys the scene by clearing all buffers and destroying all internal objects like meshes
	*/
	~Scene();

	/**
	*	\brief Renders the scene with the given shader
	*	\param[in] shader The shader to render the scene
	*/
	void render(const std::shared_ptr<Shader>& shader);

	/**
	*	\brief Add a light source to the scene
	*	\param[in] light The light source to add 
	*/
	void addLight(Light* light);

	/**
	*	\brief Initializes the given shader with the light sources of the scene
	*	\param[in] shader The shader where we want to pass the light information to
	*/
	void passLights2Shader(const std::shared_ptr<Shader>& shader);

	/**
	*	\brief Updates the shadow maps of the light sources in the scene
	*	\note: The viewport has to be set accordingly first
	*/
	void updateShadowMaps();

	/**
	*	\brief Returns the RenderObject with the given name
	*	\param[in] name The name of the object given when creating the scene
	*	\return The corresponding object;
	*/
	std::shared_ptr<RenderObject> getObject(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<RenderObject>> _objects = {};		/**<< Hash Map to maintain the objects in this scene*/
	std::unordered_map<std::string, std::shared_ptr<Model>> _models = {};				/**<< The models */
	std::vector<Light*> _lights = {};													/**<< The lights in the scene */
};

#endif