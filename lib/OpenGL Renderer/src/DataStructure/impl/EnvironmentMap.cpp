#include <DataStructure/EnvironmentMap.h>
#include <Core/GLFunctions.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/MeshHelper.h>

EnvironmentMap::EnvironmentMap(const glm::vec3& position, const uint32_t& width, const uint32_t& height)
	:_width(width),
	 _height(height)
{
	_camera = std::make_shared<Camera>(position, 90.0f, 1.0f, 0.1f, 100.0f);
	_cube_map = Texture::createTexture(width, height, (void*)NULL, CUBEMAP);
	_environment_map = std::make_shared<FrameBuffer>(width, height);
	_environment_map->attachRenderBuffer();
	_environment_map->unbind();

	_cube = MeshHelper::cubeMesh(glm::vec4(1));
	_cube->create();
}

void EnvironmentMap::setSkybox(const std::shared_ptr<EnvironmentMap>& skybox)
{
	_skybox = skybox;
}

void
EnvironmentMap::setPosition(const glm::vec3& position)
{
	_camera->teleport(position);
}

void 
EnvironmentMap::setCubeMap(const std::shared_ptr<Texture>& cube_map)
{
	_cube_map = cube_map;
	_width = cube_map->getWidth();
	_height = cube_map->getHeight();
}

void 
EnvironmentMap::renderTo(Scene* scene, const std::shared_ptr<Shader>& scene_shader, const std::shared_ptr<Shader>& skybox_shader)
{
	_environment_map->bind();
	glViewport(0, 0, _width, _height);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	for (uint32_t i = 0; i < 6; ++i)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cube_map->getID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_camera->updateDirection(angles[i].pitch, angles[i].yaw);
		if(_skybox)
			_skybox->renderAsSkybox(_camera.get(), skybox_shader);
		scene_shader->bind();
		scene_shader->setMVP(glm::mat4(1), _camera->getView(), _camera->getProjection());
		if(scene != nullptr)
			scene->render(scene_shader);
	}
	_environment_map->unbind();
}

void 
EnvironmentMap::prefilter(const std::shared_ptr<Shader>& prefilter_shader)
{
	_environment_map->bind();
	uint32_t max_mip_levels = 5;
	prefilter_shader->bind();

	for(uint32_t mip = 0; mip < max_mip_levels; ++mip)
	{
		uint32_t width = 128 * std::pow(0.5, mip);
		uint32_t height = 128 * std::pow(0.5, mip);

		_environment_map->getRenderBuffer()->setResolution(width, height);
		GL::setViewport(width, height);

		float roughness = (float)mip / (float)(max_mip_levels - 1);
		prefilter_shader->setFloat("roughness", roughness);

		for(uint32_t i = 0; i < 6; ++i)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cube_map->getID(), mip);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			_camera->updateDirection(angles[i].pitch, angles[i].yaw);
			if (_skybox)
				_skybox->renderAsSkybox(_camera.get(), prefilter_shader);
		}
	}
	_environment_map->unbind();
}

void
EnvironmentMap::renderAsSkybox(Camera* camera, const std::shared_ptr<Shader>& skybox_shader) 
{
	renderAsSkybox(camera->getView(), camera->getProjection(), skybox_shader);
}

void 
EnvironmentMap::renderAsSkybox(const glm::mat4& view, const glm::mat4& projection, const std::shared_ptr<Shader>& skybox_shader)
{
	GL::disableDepthWriting();
	skybox_shader->bind();
	_cube_map->bind(0);
	skybox_shader->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(view)),
		projection);
	_cube->render();
	GL::enableDepthWriting();
	_cube_map->unbind(0);
}