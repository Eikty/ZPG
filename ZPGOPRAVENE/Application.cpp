#include "Application.h"

Application::Application() {
	window = nullptr;
}

void Application::initialization() {
	glfwSetErrorCallback(Controller::error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	GLint depthBits;
	glGetIntegerv(GL_DEPTH_BITS, &depthBits);
	printf("=== DEBUG: OpenGL hlasi %d depth bitu ===\n", depthBits);

	GLint stencilBits;
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
	printf("=== DEBUG: OpenGL hlasi %d stencil bitu ===\n", stencilBits);

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION)); int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	// Sets the key callback
	glfwSetKeyCallback(window, Controller::key_callback);
	glfwSetCursorPosCallback(window, Controller::cursor_callback);
	glfwSetMouseButtonCallback(window, Controller::button_callback);
	glfwSetWindowFocusCallback(window, Controller::window_focus_callback);
	glfwSetWindowIconifyCallback(window, Controller::window_iconify_callback);
	glfwSetWindowSizeCallback(window, Controller::window_size_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::createShaders() {
	Shader* shaderNoLight = new Shader();
	Shader* shaderConstantLight = new Shader();
	shaderConstantLight->createShaderFromFile(GL_VERTEX_SHADER, "shader.vert");
	shaderConstantLight->createShaderFromFile(GL_FRAGMENT_SHADER, "constant.frag");
	Shader* shaderLambertLight = new Shader();
	shaderLambertLight->createShaderFromFile(GL_VERTEX_SHADER, "shader.vert");
	shaderLambertLight->createShaderFromFile(GL_FRAGMENT_SHADER, "lambert.frag");
	Shader* shaderPhongLight = new Shader();
	shaderPhongLight->createShaderFromFile(GL_VERTEX_SHADER, "shader.vert");
	shaderPhongLight->createShaderFromFile(GL_FRAGMENT_SHADER, "phong.frag");
	Shader* shaderBlinnLight = new Shader();
	shaderBlinnLight->createShaderFromFile(GL_VERTEX_SHADER, "shader.vert");
	shaderBlinnLight->createShaderFromFile(GL_FRAGMENT_SHADER, "blinn.frag");

	shaders.push_back(new ShaderProgram(shaderNoLight));			// 0
	shaders.push_back(new ShaderProgram(shaderConstantLight));		// 1
	shaders.push_back(new ShaderProgram(shaderLambertLight));		// 2
	shaders.push_back(new ShaderProgram(shaderPhongLight));			// 3
	shaders.push_back(new ShaderProgram(shaderBlinnLight));			// 4

	shaders.push_back(new ShaderProgram(shaderConstantLight));		// 5
	shaders.push_back(new ShaderProgram(shaderLambertLight));		// 6
	shaders.push_back(new ShaderProgram(shaderPhongLight));			// 7
	shaders.push_back(new ShaderProgram(shaderBlinnLight));			// 8
	shaders.push_back(new ShaderProgram(shaderNoLight));			// 9
}

void Application::createModels() {
	float points_triangle[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	Material* material_organic = new Material(0.1f, 0.9f, 0.1f, 16.0f);
	Material* material_neutral = new Material(0.1f, 0.7f, 0.4f, 64.0f);
	Material* material_shiny = new Material(0.1f, 0.6f, 0.9f, 128.0f);
	Material* material_flat = new Material(0.1f, 0.8f, 0.1f, 8.0f);

	models.emplace("triangle", new Model(points_triangle, 3, material_neutral));
	models.emplace("sphere", new Model(sphere, (sizeof(sphere) / sizeof(*sphere)) / 6, material_neutral));
	models.emplace("bushes", new Model(bushes, (sizeof(bushes) / sizeof(*bushes)) / 6, material_organic));
	models.emplace("gift", new Model(gift, (sizeof(gift) / sizeof(*gift)) / 6, material_organic));
	models.emplace("suziFlat", new Model(suziFlat, (sizeof(suziFlat) / sizeof(*suziFlat)) / 6, material_flat));
	models.emplace("suziSmooth", new Model(suziSmooth, (sizeof(suziSmooth) / sizeof(*suziSmooth)) / 6, material_shiny));
	models.emplace("tree", new Model(tree, (sizeof(tree) / sizeof(*tree)) / 6, material_organic));
	models.emplace("plain", new Model(plain, (sizeof(plain) / sizeof(*plain)) / 8, material_organic, true));
	models.emplace("formula", new Model("formula1.obj", material_flat));
	models.emplace("shrek", new Model("shrek.obj", material_flat));
	models.emplace("fiona", new Model("fiona.obj", material_flat));
	models.emplace("toiled", new Model("toiled.obj", material_shiny));
	models.emplace("planet", new Model("planet.obj", material_flat));
}

void Application::createScenes() {
	// Scene 1 - Night Forest
	Scene* scene1 = new Scene();
	shaders.at(3)->setCamera(scene1->getCamera());
	shaders.at(0)->setCamera(scene1->getCamera());
	vector<DrawableObject*> forest;
	vector<glm::vec3> translations;

	srand(time(NULL));

	for (int i = 0; i < 80; i++) {
		glm::vec3 translation;

		do {
			translation = { rand() % 41 - 20, -2, rand() % 41 - 20 };
		} while (
				find(translations.begin(), translations.end(), translation) != translations.end() ||
				(translation.x >= -3 && translation.x <= 3 && translation.z >= -3 && translation.z <= 3)
			);

		translations.push_back(translation);
		forest.push_back(new DrawableObject(models.at("tree"), glm::vec3(0.0f, 0.67f, 0.0f), new Translation(translation), shaders.at(3)));
	}

	for (int i = 0; i < 100; i++) {
		glm::vec3 translation;

		do {
			translation = { rand() % 41 - 20, -2, rand() % 41 - 20 };
		} while (find(translations.begin(), translations.end(), translation) != translations.end());

		translations.push_back(translation);
		forest.push_back(new DrawableObject(models.at("bushes"), glm::vec3(0.0f, 0.67f, 0.0f), new Translation(translation), shaders.at(3)));
	}

	scene1->addDrawableObjects(forest);

	DrawableObject* grass = new DrawableObject(models.at("plain"), glm::vec3(-1.0f), new Translation(glm::vec3(0.0f, -2.0f, 0.0f)), shaders.at(3), new Texture("Textures/grass.png"));
	grass->addTransformation(new Scale(glm::vec3(30.0f)));
	scene1->addDrawableObject(grass);

	DrawableObject* shrek = new DrawableObject(models.at("shrek"), glm::vec3(-1.0f), new Translation(glm::vec3(1.0f, -2.0f, 0.0f)), shaders.at(3), new Texture("Textures/shrek.png"));
	shrek->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	DrawableObject* fiona = new DrawableObject(models.at("fiona"), glm::vec3(-1.0f), new Translation(glm::vec3(-1.0f, -2.0f, 0.0f)), shaders.at(3), new Texture("Textures/fiona.png"));
	fiona->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	DrawableObject* toiled = new DrawableObject(models.at("toiled"), glm::vec3(-1.0f), new Translation(glm::vec3(-0.0f, -2.0f, 2.0f)), shaders.at(3), new Texture("Textures/toiled.jpg"));
	toiled->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	scene1->addDrawableObject(shrek);
	scene1->addDrawableObject(fiona);
	scene1->addDrawableObject(toiled);

	LightsManager* fireflies = new LightsManager();
	
	for (int i = 0; i < 30; i++) {
		glm::vec3 translation;

		translation = { rand() % 41 - 20, (rand() % 201) / 100.0f, rand() % 41 - 20 };

		translations.push_back(translation);
		PointLight* light = new PointLight(glm::vec3(1.0f), 0.3f, glm::vec3(1.0f, 3.0f, 0.3f), 5.0f, shaders.at(3), models.at("sphere"), shaders.at(0));

		light->addTransformation(new Translation(translation));

		light->addTransformation(new Scale(glm::vec3(0.1f)));

		fireflies->addLight(light);
	}

	scene1->addLights(fireflies);
	
	scene1->addFlashlight(new Flashlight(shaders.at(3), scene1->getCamera()));

	Controller::addScene(scene1);

	// Scene 2 - Daylight Forest
	std::vector<std::string> sides = {
	"Textures/Skybox/posx.jpg",
	"Textures/Skybox/negx.jpg",
	"Textures/Skybox/posy.jpg",
	"Textures/Skybox/negy.jpg",
	"Textures/Skybox/posz.jpg",
	"Textures/Skybox/negz.jpg"
	};
	Skybox* forest_sky = new Skybox(sides);

	Scene* scene2 = new Scene(forest_sky/*, new Cigarette(shaders.at(7))*/);
	shaders.at(7)->setCamera(scene2->getCamera());

	int i = 0;
	for ( ; i < 80; i++) {
		forest[i] = new DrawableObject(models.at("tree"), glm::vec3(0.0f, 0.67f, 0.0f), new Translation(translations[i]), shaders.at(7));
	}

	for ( ; i < forest.size(); i++) {
		forest[i] = new DrawableObject(models.at("bushes"), glm::vec3(0.0f, 0.67f, 0.0f), new Translation(translations[i]), shaders.at(7));
	}
	scene2->addDrawableObjects(forest);

	grass = new DrawableObject(models.at("plain"), glm::vec3(-1.0f), new Translation(glm::vec3(0.0f, -2.0f, 0.0f)), shaders.at(7), new Texture("Textures/grass.png"));
	grass->addTransformation(new Scale(glm::vec3(30.0f)));
	scene2->addDrawableObject(grass);

	shrek = new DrawableObject(models.at("shrek"), glm::vec3(-1.0f), new Translation(glm::vec3(1.0f, -2.0f, 0.0f)), shaders.at(7), new Texture("Textures/shrek.png"));
	shrek->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	fiona = new DrawableObject(models.at("fiona"), glm::vec3(-1.0f), new Translation(glm::vec3(-1.0f, -2.0f, 0.0f)), shaders.at(7), new Texture("Textures/fiona.png"));
	fiona->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	toiled = new DrawableObject(models.at("toiled"), glm::vec3(-1.0f), new Translation(glm::vec3(-0.0f, -2.0f, 2.0f)), shaders.at(7), new Texture("Textures/toiled.jpg"));
	toiled->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	scene2->addDrawableObject(shrek);
	scene2->addDrawableObject(fiona);
	scene2->addDrawableObject(toiled);

	scene2->addLight(new DirectionalLight(glm::vec3(0.0f, -1.0f, 3.0f), glm::vec3(1.0f), 1, shaders.at(7)));

	scene2->setSpawnableObject(new DrawableObject(models.at("tree"), glm::vec3(0.0f, 0.67f, 0.0f)/*, new Translation(glm::vec3(0.0f, -2.0f, 0.0f))*/, shaders.at(7)));

	DrawableObject* test = new DrawableObject(models.at("shrek"), glm::vec3(-1.0f), new Translation(glm::vec3(1.0f, -2.0f, -1.0f)), shaders.at(7), new Texture("Textures/shrek.png"));
	test->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	test->addTransformation(new CustomTransformation(glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 20.0f
	)));
	scene2->addDrawableObject(test);

	Controller::addScene(scene2);

	// Scene 3 - Solar System
	sides = {
	"Textures/space.png",
	"Textures/space.png",
	"Textures/space.png",
	"Textures/space.png",
	"Textures/space.png",
	"Textures/space.png"
	};
	Skybox* space = new Skybox(sides);

	Scene* scene3 = new Scene(space/*, new Cigarette(shaders.at(7))*/);
	shaders.at(1)->setCamera(scene3->getCamera());
	shaders.at(4)->setCamera(scene3->getCamera());

	scene3->addLight(new PointLight(glm::vec3(1.0f), 1.0f, glm::vec3(1.0f, 0.05f, 0.001f), 5000.0f, shaders.at(1)));
	scene3->addLight(new PointLight(glm::vec3(1.0f), 1.0f, glm::vec3(1.0f, 0.05f, 0.001f), 5000.0f, shaders.at(4)));

	vector<DrawableObject*> spaceObjects;

	// Sun
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(1), new Texture("Textures/sun.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f)));

	// Mercury
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/mercury.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(2.5f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.1f)));

	// Venus
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/venus.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.2f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(4.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.4f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.18f)));

	// Earth
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/earth.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(6.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.2f)));

	// Moon
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/moon.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(6.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(0.4f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.05f)));

	// Mars
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/mars.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.8f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(8.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.8f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.15f)));

	// Jupiter
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/jupiter.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(11.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.6f)));

	// Saturn
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/saturn.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.4f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(14.5f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.8f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.5f)));

	// Uranus
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/uranus.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.3f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(17.5f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.35f)));

	// Neptune
	spaceObjects.push_back(new DrawableObject(models.at("planet"), glm::vec3(-1.0f), shaders.at(4), new Texture("Textures/neptune.jpg")));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(0.2f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Translation(glm::vec3(20.0f, 0.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new DynamicRotation(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	spaceObjects.back()->addTransformation(new Scale(glm::vec3(0.35f)));

	scene3->addDrawableObjects(spaceObjects);
	
	Controller::addScene(scene3);

	Scene* scene4 = new Scene(forest_sky);
	shaders.at(8)->setCamera(scene4->getCamera());

	grass = new DrawableObject(models.at("plain"), glm::vec3(-1.0f), new Translation(glm::vec3(-20.0f, -2.0f, 0.0f)), shaders.at(8), new Texture("Textures/grass.png"));
	grass->addTransformation(new Scale(glm::vec3(10.0f, 1.0f, 40.f)));
	scene4->addDrawableObject(grass);

	DrawableObject* asphalt = new DrawableObject(models.at("plain"), glm::vec3(-1.0f), new Translation(glm::vec3(0.0f, -2.0f, 0.0f)), shaders.at(8), new Texture("Textures/asphalt.jpg"));
	asphalt->addTransformation(new Scale(glm::vec3(10.0f, 1.0f, 40.f)));
	scene4->addDrawableObject(asphalt);

	DrawableObject* grass2 = new DrawableObject(models.at("plain"), glm::vec3(-1.0f), new Translation(glm::vec3(20.0f, -2.0f, 0.0f)), shaders.at(8), new Texture("Textures/grass.png"));
	grass2->addTransformation(new Scale(glm::vec3(10.0f, 1.0f, 40.f)));
	scene4->addDrawableObject(grass2);

	BezierSpline* spline = new BezierSpline(glm::vec3(0.0f, -2.0f, 30.0f));
	scene4->setSpline(spline);

	DrawableObject* formula = new DrawableObject(models.at("formula"), glm::vec3(1.0f, 0.1f, 0.1f), shaders.at(8));
	formula->addTransformation(spline);
	formula->addTransformation(new Rotation(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	formula->addTransformation(new Scale(glm::vec3(0.1f)));
	scene4->addDrawableObject(formula);

	scene4->addLight(new DirectionalLight(glm::vec3(0.0f, -1.0f, 3.0f), glm::vec3(1.0f), 1, shaders.at(8)));
	scene4->addFlashlight(new Flashlight(shaders.at(8), scene4->getCamera()));

	Controller::addScene(scene4);
}

void Application::run() {
	glEnable(GL_DEPTH_TEST); //Do depth comparisons and update the depth buffer.
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	while (!glfwWindowShouldClose(window)) {
		// clear color, depth and stencil buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if (Controller::getActiveScene())
			Controller::getActiveScene()->show();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

Application::~Application() {
	for (ShaderProgram* shader : shaders)
		delete shader;

	for (auto& pair : models)
		delete pair.second;
}