#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <ctime>
#include <string>
#include <unordered_map>
#include "Controller.h"
#include "Model.h"
#include "sphere.h"
#include "Scene.h"
#include "DynamicRotation.h"
#include "Translation.h"
#include "RandomDynamicTranslation.h"
#include "Scale.h"
#include "CustomTransformation.h"
#include "BezierCurve.h"
#include "BezierSpline.h"
#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"
#include "Shader.h"
#include "ILight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "LightsManager.h"
#include "Flashlight.h"
#include "Cigarette.h"

using namespace std;

class Application {
private:
	GLFWwindow* window;
	vector<ShaderProgram*> shaders;
	unordered_map<string, Model*> models;
public:
	Application();
	void initialization();
	void createShaders();
	void createModels();
	void createScenes();
	void run();
	~Application();
};