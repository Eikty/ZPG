#include "Controller.h"

vector<Scene*> Controller::scenes;
int Controller::activeScene = -1;
float Controller::cameraSpeed = 1.001;
bool Controller::rightMousePressed = false;
double Controller::lastX = 0.0;
double Controller::lastY = 0.0;
int Controller::windowHeight = 640;
int Controller::windowWidth = 480;


void Controller::addScene(Scene* scene) {
	scenes.push_back(scene);
}

Scene* Controller::getActiveScene() {
	if (activeScene < 0 || activeScene >= scenes.size())
		return nullptr;
	
	return scenes.at(activeScene);
}

void Controller::error_callback(int error, const char* description) { fputs(description, stderr); }

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action) {
	case GLFW_PRESS:
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_1:
			fprintf(stdout, "Changed active scene to 1.\n");
			activeScene = 0;
			break;
		case GLFW_KEY_2:
			fprintf(stdout, "Changed active scene to 2.\n");
			activeScene = 1;
			break;
		case GLFW_KEY_3:
			fprintf(stdout, "Changed active scene to 3.\n");
			activeScene = 2;
			break;
		case GLFW_KEY_4:
			fprintf(stdout, "Changed active scene to 4.\n");
			activeScene = 3;
			break;
		case GLFW_KEY_5:
			fprintf(stdout, "Changed active scene to 5.\n");
			activeScene = 4;
			break;
		case GLFW_KEY_6:
			fprintf(stdout, "Changed active scene to 6.\n");
			activeScene = 5;
			break;
		case GLFW_KEY_7:
			fprintf(stdout, "Changed active scene to 7.\n");
			activeScene = 6;
			break;
		case GLFW_KEY_8:
			fprintf(stdout, "Changed active scene to 8.\n");
			activeScene = 7;
			break;
		case GLFW_KEY_9:
			fprintf(stdout, "Changed active scene to 9.\n");
			activeScene = 8;
			break;
		case GLFW_KEY_W:
			if (getActiveScene()) {
				fprintf(stdout, "Camera moved forward.\n");
				getActiveScene()->getCamera()->moveZ(cameraSpeed);
			}
			break;
		case GLFW_KEY_S:
			if (getActiveScene()) {
				fprintf(stdout, "Camera moved backwards.\n");
				getActiveScene()->getCamera()->moveZ(-cameraSpeed);
			}
			break;
		case GLFW_KEY_D:
			if (getActiveScene()) {
				fprintf(stdout, "Camera moved right.\n");
				getActiveScene()->getCamera()->moveX(cameraSpeed);
			}
			break;
		case GLFW_KEY_A:
			if (getActiveScene()) {
				fprintf(stdout, "Camera moved left.\n");
				getActiveScene()->getCamera()->moveX(-cameraSpeed);
			}
			break;
		case GLFW_KEY_F:
			if (getActiveScene()) {
				fprintf(stdout, "Flashlight toggled.\n");
				getActiveScene()->toggleFlashlight();
			}
			break;
		}
	}

	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	Controller::windowWidth = width;
	Controller::windowHeight = height;

	for (Scene* scene : scenes) {
		if (scene && scene->getCamera()) {
			scene->getCamera()->updateProjectionMatrix(width, height);
		}
	}
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y) {
	//printf("cursor_callback \n");

	if (rightMousePressed && getActiveScene()) {
		getActiveScene()->getCamera()->rotate(x - lastX, y - lastY, 0.1f);

		lastX = x;
		lastY = y;
	}
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) {
		//printf("button_callback [%d,%d,%d]\n", button, action, mode);

		if (button == GLFW_MOUSE_BUTTON_RIGHT && getActiveScene()) {
			rightMousePressed = true;
			glfwGetCursorPos(window, &lastX, &lastY);
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && getActiveScene()) {
			double cursorX, cursorY;
			glfwGetCursorPos(window, &cursorX, &cursorY);

			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			GLint x = (GLint)cursorX;
			GLint y = (GLint)cursorY;

			int newy = Controller::windowHeight - y;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

			scenes[activeScene]->setSelect(index);

			if (index > 0) {
				glm::vec3 screenX = glm::vec3(x, newy, depth);
				glm::mat4 view = scenes[activeScene]->getCamera()->getCamera();
				glm::mat4 projection = scenes[activeScene]->getCamera()->getProjectionMatrix();
				glm::vec4 viewPort = glm::vec4(0, 0, Controller::windowWidth, Controller::windowHeight);
				glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

				printf("pox.x: %f\tpos.y: %f\tpos.z: %f\n", pos.x, pos.y, pos.z);

				if (scenes[activeScene]->getObjectByIndex(index) == scenes[activeScene]->getGround())
					scenes[activeScene]->spawnObjectAt(pos);
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		rightMousePressed = false;
	}
}