#include <DataStructure/EnvironmentMap.h>

EnvironmentMap::EnvironmentMap(const glm::vec3& position, const uint32_t& width, const uint32_t& height)
	:_width(width),
	 _height(height)
{
	EnvironmentMap result;
	_camera = std::make_shared<Camera>(position, 90.0f, 1.0f, 0.1f, 100.0f);
	_cube_map = Texture::createTexture(width, height, (void*)NULL, CUBEMAP);
	_environment_map = std::make_shared<FrameBuffer>(1024, 1024);
	_environment_map->attachRenderBuffer();
	_environment_map->unbind();
}

void
EnvironmentMap::setPosition(const glm::vec3& position)
{
	_camera->teleport(position);
}

void 
EnvironmentMap::render(Scene* scene, Skybox& skybox, std::shared_ptr<Shader>& shader)
{
	_environment_map->bind();
	glViewport(0, 0, _width, _height);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	for (uint32_t i = 0; i < 6; ++i)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cube_map->getID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_camera->updateDirection(angles[i].pitch, angles[i].yaw);
		skybox.render(_camera.get());
		shader->bind();
		shader->setMVP(glm::mat4(1), _camera->getView(), _camera->getProjection());
		if(shader)
			scene->render(shader);
	}
	_environment_map->unbind();
}