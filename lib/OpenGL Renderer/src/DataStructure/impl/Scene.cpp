#include <DataStructure/Scene.h>
#include <Shader/ShaderManager.h>
#include <glm/gtx/transform.hpp>
#include <DLogger/Logger.h>
 
Scene::Scene(std::vector<std::string> names,
			 std::vector<std::shared_ptr<Mesh>> meshes,
			 std::vector<Material> materials,
			 std::vector<glm::mat4> models)
{
	uint32_t size_names = names.size();
	uint32_t size_meshes = meshes.size();
	uint32_t size_materials = materials.size();
	uint32_t size_models = models.size();

	if (size_names != size_meshes || size_names != size_materials || size_names != size_models)
	{
		LOGGER::ERROR("ERROR::SCENE: The sizes of the given buffers is not equal: ("
			+ std::to_string(size_names) + ", " + std::to_string(size_meshes) + ", " + std::to_string(size_materials) + ", " + std::to_string(size_models) + ")\n");
		return;
	}

	for (uint32_t i = 0; i < size_names; ++i)
	{
		meshes[i]->create();
		_objects.insert(std::make_pair(names[i], std::make_shared<RenderObject>(meshes[i], materials[i], models[i])));
	}

	ShaderManager::addShader("Shadow");
}

Scene::Scene(std::vector<std::string> names,
			 std::vector<std::shared_ptr<Model>> models)
{
	uint32_t size_names = names.size();
	uint32_t size_meshes = models.size();

	if (size_names != size_meshes)
	{
		LOGGER::ERROR("ERROR::SCENE: The sizes of the given buffers is not equal: ("
			+ std::to_string(size_names) + ", " + std::to_string(size_meshes) + ")\n");
		return;
	}

	for (uint32_t i = 0; i < size_names; ++i)
	{
		_models.insert(std::make_pair(names[i], models[i]));
	}

	ShaderManager::addShader("Shadow");
}
 
Scene::~Scene()
{
	_objects.clear();
	_lights.clear();
}

void 
Scene::render(std::shared_ptr<Shader> shader)
{
	for (uint32_t i = 0; i < _lights.size(); ++i)
	{
		if (!_lights[i]->castShadows) continue;
		_lights[i]->shadow_map->getTexture()->bind(11 + i);
	}

	for (auto it = _objects.begin(); it != _objects.end(); ++it)
	{
		if(it->second->getMaterial()._type != GLASS)
			it->second->render(shader);
	}

	for(auto it = _models.begin(); it != _models.end(); ++it)
	{
		it->second->render(shader);
	}
}

void 
Scene::addLight(Light* light)
{
	_lights.push_back(light);
}

void
Scene::passLights2Shader(std::shared_ptr<Shader> shader)
{
	for (uint32_t i = 0; i < _lights.size(); ++i)
	{
		_lights[i]->addToShader(shader, i);
	}
}

void 
Scene::updateShadowMaps()
{
	std::shared_ptr<Shader> shadow = ShaderManager::getShader("Shadow");
	shadow->bind();
	Light* light;
	for (uint32_t i = 0; i < _lights.size(); ++i)
	{
		light = _lights[i];
		if (!light->castShadows)
		{
			light->lightSpace = glm::mat4(1);
			continue;
		}
		light->shadow_map->bind();
		light->shadow_map->clear();
		light->lightView = glm::lookAt(light->position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		light->lightSpace = light->lightProjection * light->lightView;

		shadow->setMat4("P", light->lightProjection);
		shadow->setMat4("V", light->lightView);
		this->render(shadow);
	}

	FrameBuffer::bindDefault();
}

std::shared_ptr<RenderObject>
Scene::getObject(std::string name)
{
	return _objects[name];
}
