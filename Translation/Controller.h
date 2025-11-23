#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include "Camera.h"
#include "Scene.h"

using namespace std;

class Controller {
private:
	static vector<Scene*> scenes;
	static int activeScene;
	static float cameraSpeed;
	static bool rightMousePressed;
	static double lastX;
	static double lastY;
	static int windowWidth;
	static int windowHeight;
public:
	static void addScene(Scene* scene);
	static Scene* getActiveScene();
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};