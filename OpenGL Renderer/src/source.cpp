#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <opencv2/opencv.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Skybox.h>
#include <DataStructure/Scene.h>
#include <Shader/ShaderManager.h>

#include <IO/KeyManager.h>
#include <IO/ObjLoader.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>
#include <DataStructure/EnvironmentMap.h>

#include <chrono>
#include <thread>

#include <fstream>

#define LIGHTS 1

Scene loadScene()
{
	std::vector<std::string> names;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;
	std::vector<Mesh> meshes = ObjLoader::loadObj("res/testroom.obj");
	Material material_box = Material::createObject("materialmap", MaterialType::LAMBERT);
	material_box.ambient = glm::vec3(0.1f, 0, 0);
	material_box.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	material_box.specular = glm::vec3(1.0f, 0.0f, 0.0f);
	material_box.useTextures = false;
	material_box.shininess = 128.0f;

	for (unsigned int i = 0; i < meshes.size(); ++i)
	{
		names.push_back("Scene_" + std::to_string(i));
		materials.push_back(material_box);
		models.push_back(glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5)));
	}


	Scene scene = Scene::createObject(names, meshes, materials, models);
	names.clear();
	meshes.clear();
	materials.clear();
	models.clear();
	return scene;
}

int main(void)
{
	unsigned int width = 640;
	unsigned int height = 480;

	unsigned int shadow_width = 2000;
	unsigned int shadow_height = 2000;

	float near = 0.1f;
	float far = 13.0f;

	RenderWindow window = RenderWindow::createObject(width, height, "Render Window");
	KeyManager::instance()->setup(window);
	Camera camera = Camera::createObject(window, 45.0f, near, far);

	std::string dataset = "C:/Users/Domenic/Desktop/Test Dataset";

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	Scene scene = loadScene();
	
	Light light;
	light.ambient = glm::vec3(1.0f, 1.0f, 1.0f)*10.0f;
	light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f)*10.0f;
	light.specular = glm::vec3(1.0f, 1.0f, 1.0f)*10.0f;
	light.position = glm::vec3(0.0f, 5.0f, -5.0f)*10.0f;

	Mesh quad = Mesh::createObject();

	unsigned int id1, id2, id3, id4;

	id1 = quad.addVertex(glm::vec3(-1, -1, 0), glm::vec4(1), glm::vec2(0), glm::vec3(0, 0, 1));
	id2 = quad.addVertex(glm::vec3(1, -1, 0), glm::vec4(1), glm::vec2(1, 0), glm::vec3(0, 0, 1));
	id3 = quad.addVertex(glm::vec3(1, 1, 0), glm::vec4(1), glm::vec2(1, 1), glm::vec3(0, 0, 1));
	id4 = quad.addVertex(glm::vec3(-1, 1, 0), glm::vec4(1), glm::vec2(0, 1), glm::vec3(0, 0, 1));

	quad.addTriangle(id1, id2, id3);
	quad.addTriangle(id1, id3, id4);

	quad.create();


	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//
	ShaderManager::instance()->addShader("Normal");
	ShaderManager::instance()->addShader("Post");

	FrameBuffer frame_buffer = FrameBuffer::createObject(width, height);
	Texture depth_map = Texture::createObject(width, height, TEXTURE, GL_R16UI, GL_UNSIGNED_SHORT);
	frame_buffer.attachColor();
	frame_buffer.attachColor(depth_map);
	frame_buffer.attachDepthMap();
	frame_buffer.verify();
	frame_buffer.unbind();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	unsigned int frameID = 0;
	unsigned char* color_buffer = new unsigned char[width * height * 3];
	unsigned short* depth_buffer = new unsigned short[width * height];

	std::ofstream depth;
	std::ofstream rgb;
	rgb.open(dataset + "/rgb.txt");
	depth.open(dataset + "/depth.txt");
	bool capture = false;
	/* Loop until the user closes the window */
	while (window.isOpen())
	{

		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f fps\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		camera.processInput(0.005f);

		frame_buffer.bind();
		window.clear();
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setMat4("P", camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setMat4("V", camera.getView());
		ShaderManager::instance()->getShader("Normal").setLight("lights_frag[0]", light);
		scene.render(ShaderManager::instance()->getShader("Normal"));

		frame_buffer.unbind();

		//attachments[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, attachments);
		window.clear();
		ShaderManager::instance()->getShader("Post").bind();
		ShaderManager::instance()->getShader("Post").setInt("screenTexture", 0);
		frame_buffer.getTexture(0).bind(0);
		quad.render();

		window.spinOnce();

		frameID += 1;

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_M))
		{
			capture = true;
		}

		if (capture)
		{
			frame_buffer.getTexture(0).bind(0);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, color_buffer);

			cv::Mat cv_color(height, width, CV_8UC3, color_buffer);
			flip(cv_color, cv_color, 0);
			imwrite(dataset + "/rgb/" + std::to_string(frameID) + ".png", cv_color);

			frame_buffer.getTexture(1).bind();
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, depth_buffer);

			cv::Mat cv_depth(height, width, CV_16UC1, depth_buffer);
			flip(cv_depth, cv_depth, 0);
			imwrite(dataset + "/depth/" + std::to_string(frameID) + ".png", cv_depth);

			rgb << std::to_string(frameID) << " rgb/" << std::to_string(frameID) << ".png\n";
			depth << std::to_string(frameID) << " depth/" << std::to_string(frameID) << ".png\n";
		}
	}

	ShaderManager::destroyObject(*ShaderManager::instance());
	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	KeyManager::destroy();
	Scene::destroyObject(scene);

	delete[] color_buffer;
	delete[] depth_buffer;

	rgb.close();
	depth.close();

	return 0;
}