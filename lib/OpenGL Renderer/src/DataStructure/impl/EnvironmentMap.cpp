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

void EnvironmentMap::setSkybox(std::shared_ptr<EnvironmentMap>& skybox)
{
	_skybox = skybox;
}

void
EnvironmentMap::setPosition(const glm::vec3& position)
{
	_camera->teleport(position);
}

void 
EnvironmentMap::setCubeMap(std::shared_ptr<Texture>& cube_map)
{
	_cube_map = cube_map;
	_width = cube_map->getWidth();
	_height = cube_map->getHeight();
}

void 
EnvironmentMap::renderTo(Scene* scene, std::shared_ptr<Shader>& scene_shader, std::shared_ptr<Shader>& skybox_shader)
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
EnvironmentMap::renderAsSkybox(Camera* camera, std::shared_ptr<Shader>& skybox_shader) 
{
	GL::disableDepthWriting();
	skybox_shader->bind();
	_cube_map->bind(0);
	skybox_shader->setMVP(glm::mat4(1),
		glm::mat4(glm::mat3(camera->getView())),
		camera->getProjection());
	_cube->render();
	GL::enableDepthWriting();
}