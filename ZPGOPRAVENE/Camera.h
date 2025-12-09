#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "IObserver.h"

using namespace std;

class Camera {
private:
	vector<IObserver*> observers;
	glm::mat4 projectionMatrix;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	float alpha;
	float fi;

	void notify();
public:
	Camera();
	glm::vec3 getPosition();
	glm::vec3 getDirection();
	void addObserver(IObserver* observer);
	glm::mat4 getProjectionMatrix();
	void updateProjectionMatrix(int width, int height);
	glm::mat4 getCamera();
	void moveZ(float distance);
	void moveX(float distance);
	void rotate(float x, float y, float sensitivity);
};