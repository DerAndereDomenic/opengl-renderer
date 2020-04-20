#include <DataStructure/Scene.h>

Scene 
Scene::createObject(std::vector<std::string> names,
					std::vector<Mesh> meshes,
					std::vector<Material> materials,
					std::vector<glm::mat4> models)
{
	unsigned int size_names = names.size();
	unsigned int size_meshes = meshes.size();
	unsigned int size_materials = materials.size();
	unsigned int size_models = models.size();

	if (size_names != size_meshes || size_names != size_materials || size_names != size_models)
	{
		std::cerr << "ERROR::SCENE: The sizes of the given buffers is not equal: ("
			<< size_names << ", " << size_meshes << ", " << size_materials << ", " << size_models << ")" << std::endl;
	}

	Scene result;
	for (unsigned int i = 0; i < size_names; ++i)
	{
		meshes[i].create();
		result._objects.insert(std::make_pair(names[i], RenderObject::createObject(meshes[i], materials[i], models[i])));
	}

	return result;
}

void 
Scene::destroyObject(Scene& scene)
{
	for (auto it = scene._objects.begin(); it != scene._objects.end(); ++it) 
	{
		RenderObject::destroyObject(it->second);
	}
	scene._objects.clear();
}

void 
Scene::render(RenderWindow window, Shader shader)
{
	for (auto it = _objects.begin(); it != _objects.end(); ++it)
	{
		it->second.render(window, shader);
	}
}

RenderObject 
Scene::getObject(std::string name)
{
	return _objects[name];
}