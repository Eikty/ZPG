#include "Scene.h"

Scene::Scene(Skybox* skybox, Cigarette* cigarette) {
	this->skybox = skybox;
	this->cigarette = cigarette;
	camera = new Camera();
	lights = new LightsManager();
	selectedObjectID = 0;
	spawnable = nullptr;
	flashlight = nullptr;
	spline = nullptr;

	if (this->skybox)
		this->skybox->setCamera(camera);

	if (this->cigarette)
		this->cigarette->setCamera(camera);
}

Camera* Scene::getCamera() {
	return camera;
}

void Scene::addDrawableObject(DrawableObject* object) {
	objects.push_back(object);
}

void Scene::addDrawableObjects(vector<DrawableObject*> objects) {
	this->objects.insert(this->objects.end(), objects.begin(), objects.end());
}

GLuint Scene::getSelect() {
	return selectedObjectID;
}

void Scene::setSelect(GLuint index) {
	selectedObjectID = index;
}

void Scene::setSpawnableObject(DrawableObject* object) {
	spawnable = object;
}

void Scene::spawnObjectAt(glm::vec3 position) {
	if (spawnable) {
		DrawableObject* toSpawn = new DrawableObject(*spawnable);
		toSpawn->addTransformation(new Translation(position));
		addDrawableObject(toSpawn);
		setSelect(objects.size());
	}

	if (spline) {
		spline->addPoint(position);
		setSelect(0);
	}
}

void Scene::addLights(LightsManager* lights) {
	this->lights = lights;
}

void Scene::addLight(ILight* light) {
	lights->addLight(light);
}

void Scene::addFlashlight(Flashlight* flashlight) {
	this->flashlight = flashlight;
	lights->addLight(flashlight);
}

void Scene::toggleFlashlight() {
	if (flashlight)
		flashlight->toggle();
}

void Scene::setSpline(BezierSpline* spline) {
	this->spline = spline;
}

void Scene::show() {
	lights->draw();

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (int i = 0; i < objects.size(); i++) {
		glStencilFunc(GL_ALWAYS, i + 1, 0xFF);

		bool isSelected = i + 1 == selectedObjectID;

		objects[i]->draw(isSelected);

		if (objects[i]->isGameObject() && isSelected)
			selectedObjectID = 0;
	}

	glDisable(GL_STENCIL_TEST);

	if (skybox)
		skybox->draw(camera->getCamera(), camera->getProjectionMatrix());

	if (cigarette)
		cigarette->draw(camera->getCamera());
}

Scene::~Scene() {
	for (DrawableObject* object : objects)
		delete object;

	if (camera)
		delete camera;

	if (lights)
		delete lights;

	if (skybox)
		delete skybox;

	if (cigarette)
		delete cigarette;
}