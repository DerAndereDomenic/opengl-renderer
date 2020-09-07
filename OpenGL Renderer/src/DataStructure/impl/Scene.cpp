#include <DataStructure/Scene.h>
#include <Shader/ShaderManager.h>
#include <glm/gtx/transform.hpp>

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
	scene._lights.clear();
}

void 
Scene::render(Shader shader)
{
	for (auto it = _objects.begin(); it != _objects.end(); ++it)
	{
		it->second.render(shader);
	}
}

void 
Scene::addLight(Light* light)
{
	_lights.push_back(light);
}

void
Scene::passLights2Shader(Shader shader)
{
	for (unsigned int i = 0; i < _lights.size(); ++i)
	{
		_lights[i]->addToShader(shader, i);
	}
}

void 
Scene::updateShadowMaps()
{
	for (unsigned int i = 0; i < _lights.size(); ++i)
	{
		if (!_lights[i]->castShadows) continue;
		_lights[i]->shadow_map.bind();
		_lights[i]->shadow_map.clear();
		_lights[i]->lightView = glm::lookAt(_lights[i]->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_lights[i]->lightSpace = _lights[i]->lightProjection * _lights[i]->lightView;

		ShaderManager::instance()->getShader("Shadow").bind();
		ShaderManager::instance()->getShader("Shadow").setMat4("P", _lights[i]->lightProjection);
		ShaderManager::instance()->getShader("Shadow").setMat4("V", _lights[i]->lightView);
		this->render(ShaderManager::instance()->getShader("Shadow"));
	}
}

RenderObject&
Scene::getObject(std::string name)
{
	return _objects[name];
}