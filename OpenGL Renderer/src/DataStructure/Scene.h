#ifndef DATASTRUCTURE_SCENE_H
#define DATASTRUCTURE_SCENE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <DataStructure/Mesh.h>
#include <DataStructure/Material.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Light.h>
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
	*	\return The scene with initialized with the given data
	*	\note: The indices have to coincide in all vectors with the given object
	*		   So (names[i], meshes[i], materials[i], models[i]) defines one object
	*/
	static Scene createObject(std::vector<std::string> names,
							  std::vector<Mesh> meshes,
							  std::vector<Material> materials,
							  std::vector<glm::mat4> models);

	/**
	*	\brief Destroys the scene by clearing all buffers and destroying all internal objects like meshes
	*/
	static void destroyObject(Scene& scene);

	/**
	*	\brief Renders the scene with the given shader
	*	\param[in] shader The shader to render the scene
	*/
	void render(Shader shader);

	/**
	*	\brief Returns the RenderObject with the given name
	*	\param[in] name The name of the object given when creating the scene
	*	\return The corresponding object;
	*/
	RenderObject& getObject(std::string name);

private:
	std::unordered_map<std::string, RenderObject> _objects = {}; /**<< Hash Map to maintain the objects in this scene*/
	std::vector<Light*> _lights = {};
};

#endif