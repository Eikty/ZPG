#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization(); //OpenGL inicialization

	//Loading scene
	app->createShaders();
	app->createModels();
	app->createScenes();
	app->run(); //Rendering
}