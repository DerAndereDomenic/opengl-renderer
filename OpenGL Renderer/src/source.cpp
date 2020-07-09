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

#define LIGHTS 1


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

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	std::vector<std::string> names;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	Mesh box = ObjLoader::loadObj("cobble.obj")[0];
	Material material_box = Material::createObject("material_map", MaterialType::LAMBERT);
	material_box.ambient = glm::vec3(0.1f, 0, 0);
	material_box.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	material_box.specular = glm::vec3(1.0f, 0.0f, 0.0f);
	material_box.useTextures = false;
	material_box.shininess = 128.0f;

	models.push_back(glm::mat4(1));

	Scene scene = Scene::createObject(names, meshes, materials, models);
	names.clear();
	meshes.clear();
	materials.clear();
	models.clear();
	

	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//
	ShaderManager::instance()->addShader("Normal");

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	unsigned int frameID = 0;

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

		window.spinOnce();

		frameID += 1;

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	ShaderManager::destroyObject(*ShaderManager::instance());
	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	KeyManager::destroy();
	Scene::destroyObject(scene);

	return 0;
}