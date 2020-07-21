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

Scene loadScene1()
{
	std::vector<std::string> names;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;
	std::vector<Mesh> meshes = ObjLoader::loadObj("res/testroom.obj",true);
	Material material_floor = Material::createObject("materialmap", MaterialType::PHONG);
	/*material_floor.ambient = glm::vec3(0.087f, 0.072f, 0.053f);
	material_floor.diffuse = glm::vec3(0.87f, 0.72f, 0.53f);
	material_floor.specular = glm::vec3(0.87f, 0.72f, 0.53f);
	material_floor.useTextures = false;
	material_floor.shininess = 0.4f*128.0f;*/

	material_floor.texture_diffuse = Texture::createObject("res/wood_color.jpg");
	material_floor.texture_normal = Texture::createObject("res/wood_normal.jpg");
	material_floor.texture_specular = Texture::createObject("res/wood_color.jpg");
	material_floor.shininess = 0.04f * 128.0f;
	material_floor.useTextures = true;
	
	Material material_table = Material::createObject("materialmap", MaterialType::PHONG);
	material_table.texture_diffuse = Texture::createObject("res/table/table_diffuse.png");
	material_table.texture_normal = Texture::createObject("res/table/table_normal.png");
	material_table.texture_specular = Texture::createObject("res/table/table_specular.png");
	material_table.shininess = 0.04f * 128.0f;
	material_table.useTextures = true;

	Material material_suzanne = Material::createObject("materialmap", MaterialType::GGX);
	material_suzanne.ambient = glm::vec3(0.10f, 0.098f, 0.094f);
	material_suzanne.diffuse = glm::vec3(1.0f, 0.98f, 0.94f);
	material_suzanne.specular = glm::vec3(1.0f, 0.98f, 0.94f);
	material_suzanne.useTextures = false;
	material_suzanne.shininess = 0.4f*128.0f;

	Material material_wall = Material::createObject("materialmap", MaterialType::PHONG);
	material_wall.texture_diffuse = Texture::createObject("res/brickwall.png");
	material_wall.texture_normal = Texture::createObject("res/brickwall_normal.png");
	material_wall.texture_specular = Texture::createObject("res/brickwall.png");
	material_wall.shininess = 0.04f * 128.0f;
	material_wall.useTextures = true;


	materials.push_back(material_floor);
	for (unsigned int i = 0; i < 4; ++i)
	{
		materials.push_back(material_table);
	}
	materials.push_back(material_suzanne);
	materials.push_back(material_suzanne);

	for (unsigned int i = 0; i < 4; ++i)
	{
		materials.push_back(material_wall);
	}

	materials.push_back(material_wall);

	for (unsigned int i = 0; i < meshes.size();++i)
	{
		names.push_back("Scene_" + std::to_string(i));
		
		models.push_back(glm::scale(glm::mat4(1), glm::vec3(0.7f)));
	}


	Scene scene = Scene::createObject(names, meshes, materials, models);
	names.clear();
	meshes.clear();
	materials.clear();
	models.clear();
	return scene;
}

Scene loadScene2()
{
	std::vector<std::string> names;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;
	std::vector<Mesh> meshes = ObjLoader::loadObj("res/testroom2/testroom2.obj", true);
	std::cout << "Scene contains: " << meshes.size() << " Meshes" << std::endl;
	Material material_test = Material::createObject("materialmap", MaterialType::PHONG);
	material_test.ambient = glm::vec3(0.087f, 0.072f, 0.053f);
	material_test.diffuse = glm::vec3(0.87f, 0.72f, 0.53f);
	material_test.specular = glm::vec3(0.87f, 0.72f, 0.53f);
	material_test.useTextures = false;
	material_test.shininess = 0.4f*128.0f;

	Material material_floor = Material::createObject("materialmap", MaterialType::GGX);
	material_floor.useTextures = true;
	material_floor.texture_diffuse = Texture::createObject("res/testroom2/woodplanks_albedo.png");
	material_floor.texture_specular = material_floor.texture_diffuse;
	material_floor.texture_normal = Texture::createObject("res/testroom2/woodplanks_normal.png");
	material_floor.texture_height = Texture::createObject("res/testroom2/woodplanks_height.png");
	material_floor.shininess = 0.4 * 128.0f;

	Material material_table = Material::createObject("materialmap", MaterialType::GGX);
	material_table.texture_diffuse = Texture::createObject("res/table/table_diffuse.png");
	material_table.texture_normal = Texture::createObject("res/table/table_normal.png");
	material_table.texture_specular = Texture::createObject("res/table/table_specular.png");
	material_table.shininess = 0.04f * 128.0f;
	material_table.useTextures = true;

	Material material_dresser = Material::createObject("materialmap", MaterialType::GGX);
	material_dresser.texture_diffuse = Texture::createObject("res/testroom2/wood.jpg");
	material_dresser.texture_normal = Texture::createObject("res/testroom2/woodnormal.jpg");
	material_dresser.texture_specular = material_dresser.texture_diffuse;
	material_dresser.shininess = 0.04f * 128.0f;
	material_dresser.useTextures = true;

	Material material_couch = Material::createObject("materialmap", MaterialType::GGX);
	material_couch.ambient = glm::vec3(0.8f, 0.8f, 0.8f);
	material_couch.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	material_couch.specular = glm::vec3(0.3f, 0.3f, 0.3f);
	material_couch.useTextures = false;
	material_couch.shininess = 0.4f * 128.0f;

	Material material_pillow1 = Material::createObject("materialmap", MaterialType::GGX);
	material_pillow1.texture_diffuse = Texture::createObject("res/testroom2/flame-bl.jpg");
	material_pillow1.texture_specular = material_pillow1.texture_diffuse;
	material_pillow1.shininess = 0.04f * 128.0f;
	material_pillow1.useTextures = true;

	Material material_pillow2 = Material::createObject("materialmap", MaterialType::GGX);
	material_pillow2.texture_diffuse = Texture::createObject("res/testroom2/flame-br.jpg");
	material_pillow2.texture_specular = material_pillow2.texture_diffuse;
	material_pillow2.shininess = 0.04f * 128.0f;
	material_pillow2.useTextures = true;

	Material material_wall = Material::createObject("materialmap", MaterialType::GGX);
	material_wall.texture_diffuse = Texture::createObject("res/brickwall.png");
	material_wall.texture_normal = Texture::createObject("res/brickwall_normal.png");
	material_wall.texture_specular = Texture::createObject("res/brickwall.png");
	material_wall.shininess = 0.04f * 128.0f;
	material_wall.useTextures = true;

	//wall
	materials.push_back(material_wall);
	//floor
	materials.push_back(material_floor);
	//Ceiling
	materials.push_back(material_test);
	//wall
	materials.push_back(material_wall);
	//wall
	materials.push_back(material_wall);
	//wall
	materials.push_back(material_wall);
	//dresser
	materials.push_back(material_dresser);
	//dresser
	materials.push_back(material_dresser);
	//table
	materials.push_back(material_table);
	//table
	materials.push_back(material_table);
	//Pillow1
	materials.push_back(material_pillow1);
	//Pillow2
	materials.push_back(material_pillow2);
	//Couch
	materials.push_back(material_couch);
	//Foot
	materials.push_back(material_test);
	//Pillow1
	materials.push_back(material_pillow1);
	//Pillow2
	materials.push_back(material_pillow2);
	//Couch
	materials.push_back(material_couch);
	//Foot
	materials.push_back(material_test);
	for (unsigned int i = 0; i < meshes.size(); ++i)
	{
		names.push_back("Scene_" + std::to_string(i));
		
		models.push_back(glm::scale(glm::mat4(1), glm::vec3(0.7f)));
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
	float far = 6.0f;

	RenderWindow window = RenderWindow::createObject(width, height, "Render Window");
	KeyManager::instance()->setup(window);
	Camera camera = Camera::createObject(window, 45.0f, near, far);

	std::string dataset = "C:/Users/Domenic/Desktop/Testroom2";

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	Scene scene = loadScene2();
	
	Light light;
	light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light.position = glm::vec3(0.0f, 2.1f, 0.0f);

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
	ShaderManager::instance()->addShader("Shadow");

	FrameBuffer frame_buffer = FrameBuffer::createObject(width, height);
	Texture depth_map = Texture::createObject(width, height, TEXTURE, GL_R16UI, GL_UNSIGNED_SHORT);
	frame_buffer.attachColor();
	frame_buffer.attachColor(depth_map);
	frame_buffer.attachDepthMap();
	frame_buffer.verify();
	frame_buffer.unbind();

	glm::mat4 lightProjection = glm::perspective(90.0f, window.getAspectRatio(), near, far);

	light.shadow_map = FrameBuffer::createObject(shadow_width, shadow_height);
	light.shadow_map.attachDepthMap();
	light.shadow_map.disableColor();
	light.shadow_map.verify();
	light.shadow_map.unbind();

	light.lightView = glm::lookAt(light.position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	light.lightSpace = lightProjection * light.lightView;

	window.setViewport(shadow_width, shadow_height);

	light.shadow_map.bind();
	window.clear();
	ShaderManager::instance()->getShader("Shadow").bind();
	ShaderManager::instance()->getShader("Shadow").setMat4("P", lightProjection);
	ShaderManager::instance()->getShader("Shadow").setMat4("V", light.lightView);
	scene.render(ShaderManager::instance()->getShader("Shadow"));
	window.resetViewport();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	unsigned int frameID = 0;

	std::vector<cv::Mat> color_buffers;
	std::vector<cv::Mat> depth_buffers;
	std::vector<unsigned int> time_stamps;

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
		ShaderManager::instance()->getShader("Normal").setLight("lights_frag[0]", light);
		ShaderManager::instance()->getShader("Normal").setMat4("lights_vert[0].lightSpaceMatrix", light.lightSpace);
		ShaderManager::instance()->getShader("Normal").setInt("lights_frag[0].shadow_map", 4);
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setMat4("P", camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setMat4("V", camera.getView());
		light.shadow_map.getTexture().bind(4);

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
			unsigned char* color_buffer = new unsigned char[width * height * 3];
			unsigned short* depth_buffer = new unsigned short[width * height];

			frame_buffer.getTexture(0).bind(0);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, color_buffer);

			cv::Mat cv_color(height, width, CV_8UC3, color_buffer);
			color_buffers.push_back(cv_color);

			frame_buffer.getTexture(1).bind();
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, depth_buffer);

			cv::Mat cv_depth(height, width, CV_16UC1, depth_buffer);
			depth_buffers.push_back(cv_depth);

			time_stamps.push_back(frameID);
		}
	}

	std::cout << "Started writing..." << std::endl;
	for (unsigned int i = 0; i < time_stamps.size(); ++i)
	{
		cv::Mat cv_color = color_buffers[i];
		cv::Mat cv_depth = depth_buffers[i];
		frameID = time_stamps[i];
		flip(cv_color, cv_color, 0);
		imwrite(dataset + "/rgb/" + std::to_string(frameID) + ".png", cv_color);

		flip(cv_depth, cv_depth, 0);
		imwrite(dataset + "/depth/" + std::to_string(frameID) + ".png", cv_depth);

		rgb << std::to_string(frameID) << " rgb/" << std::to_string(frameID) << ".png\n";
		depth << std::to_string(frameID) << " depth/" << std::to_string(frameID) << ".png\n";

		delete[] cv_color.ptr();
		delete[] cv_depth.ptr();

		std::cout << 100.0f * static_cast<float>(i) / static_cast<float>(time_stamps.size()) << "%" << std::endl;
	}

	ShaderManager::destroyObject(*ShaderManager::instance());
	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	KeyManager::destroy();
	Scene::destroyObject(scene);
	FrameBuffer::destroyObject(frame_buffer);

	rgb.close();
	depth.close();

	return 0;
}