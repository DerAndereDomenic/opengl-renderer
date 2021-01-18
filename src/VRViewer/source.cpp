#include <iostream>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <IO/KeyManager.h>
#include <Core/GLFunctions.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/MeshHelper.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

int main()
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();

	RenderWindow dummy_window = RenderWindow::createObject(2*822, 980, "VR Renderer");//Hard coded for Rift
	VRRenderer renderer = VRRenderer::createObject();

	KeyManager::instance()->setup(dummy_window);
	GL::enableDebugOutput();

	ShaderManager::instance()->addShader("BasicVR");
	ShaderManager::instance()->addShader("VRScreen");

	Mesh screen_quad = MeshHelper::quadMesh(2);
	screen_quad.create();

	Mesh cube = MeshHelper::cubeMesh(glm::vec4(1,0,0,1));
	cube.create();

	Mesh floor = MeshHelper::cuboidMesh(glm::vec4(0, 1, 0, 1), 10, 0.1, 10);
	floor.create();

	glm::mat4 model = glm::translate(glm::vec3(0, 1.5, 0)) * glm::scale(glm::vec3(0.1, 0.1, 0.1));

	bool running = true;

	while (running && dummy_window.isOpen())
	{
		model = glm::rotate(0.01f, glm::vec3(0, 1, 0)) * model;

		renderer.getRenderTargetLeft().bind();
		GL::clear();
		ShaderManager::instance()->getShader("BasicVR").bind();
		ShaderManager::instance()->getShader("BasicVR").setMVP(model, renderer.view(Eye::LEFT), renderer.leftProjection());
		cube.render();
		ShaderManager::instance()->getShader("BasicVR").setMVP(glm::mat4(1), renderer.view(Eye::LEFT), renderer.leftProjection());
		floor.render();

		renderer.getRenderTargetRight().bind();
		GL::clear();
		ShaderManager::instance()->getShader("BasicVR").bind();
		ShaderManager::instance()->getShader("BasicVR").setMVP(model, renderer.view(Eye::RIGHT), renderer.rightProjection());
		cube.render();
		ShaderManager::instance()->getShader("BasicVR").setMVP(glm::mat4(1), renderer.view(Eye::RIGHT), renderer.rightProjection());
		floor.render();

		renderer.uploadToHMD();

		FrameBuffer::bindDefault();

		GL::clear();
		ShaderManager::instance()->getShader("VRScreen").bind();
		ShaderManager::instance()->getShader("VRScreen").setInt("leftEye", 0);
		ShaderManager::instance()->getShader("VRScreen").setInt("rightEye", 1);
		renderer.getRenderTargetLeft().getTexture().bind(0);
		renderer.getRenderTargetRight().getTexture().bind(1);
		screen_quad.render();

		renderer.spinOnce();
		dummy_window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			running = false;
			dummy_window.close();
		}
	}

	RenderWindow::destroyObject(dummy_window);
	VRRenderer::destroyObject(renderer);
	KeyManager::instance()->destroy();
	Mesh::destroyObject(cube);
	Mesh::destroyObject(floor);
	Mesh::destroyObject(screen_quad);
	ShaderManager::destroyObject(*ShaderManager::instance());

	LOGGER::end();
	return 0;
}