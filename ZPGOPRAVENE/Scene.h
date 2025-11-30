#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "ILight.h"
#include "LightsManager.h"
#include "Flashlight.h"
#include "Skybox.h"
#include "Cigarette.h"
#include "BezierSpline.h"

using namespace std;

class Scene {
private:
	vector<DrawableObject*> objects;
	Camera* camera;
	GLuint selectedObjectID;
	DrawableObject* spawnable;
	LightsManager* lights;
	Flashlight* flashlight;
	Skybox* skybox;
	Cigarette* cigarette;
	BezierSpline* spline;
public:
	Scene(Skybox* skybox = nullptr, Cigarette* cigarette = nullptr);
	Camera* getCamera();
	void addDrawableObject(DrawableObject* object);
	void addDrawableObjects(vector<DrawableObject*> objects);
	void setSelect(GLuint index);
	DrawableObject* getObjectByIndex(GLuint index);
	void setSpawnableObject(DrawableObject* object);
	void spawnObjectAt(glm::vec3 position);
	void addLights(LightsManager* lights);
	void addLight(ILight* light);
	void addFlashlight(Flashlight* flashlight);
	void toggleFlashlight();
	void setSpline(BezierSpline* spline);
	void show();
	~Scene();
};