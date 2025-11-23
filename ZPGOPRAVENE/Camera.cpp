#include "Camera.h"

Camera::Camera() {
	// 60° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	eye = glm::vec3(0.0f, 0.0f, -1.8f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	alpha = 90;
	fi = 90;
}

glm::vec3 Camera::getPosition() {
	return eye;
}

glm::vec3 Camera::getDirection() {
	target.x = sin(glm::radians(alpha)) * cos(glm::radians(fi));
	target.z = sin(glm::radians(alpha)) * sin(glm::radians(fi));
	target.y = cos(glm::radians(alpha));

	return target;
}

void Camera::addObserver(ICameraObserver* observer) {
	observers.push_back(observer);
}

glm::mat4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}

void Camera::updateProjectionMatrix(int width, int height) {
	if (height == 0)
		height = 1;

	this->projectionMatrix = glm::perspective(glm::radians(60.f), width / (float)height, 0.1f, 100.0f);
}

glm::mat4 Camera::getCamera() {
	target.x = sin(glm::radians(alpha)) * cos(glm::radians(fi));
	target.z = sin(glm::radians(alpha)) * sin(glm::radians(fi));
	target.y = cos(glm::radians(alpha));

	return glm::lookAt(eye, eye + target, up);
}

void Camera::notify() {
	for (ICameraObserver* observer : observers) {
		observer->update();
	}
}

void Camera::moveZ(float distance) {
	eye += glm::normalize(target) * distance;
	notify();
}

void Camera::moveX(float distance) {
	eye += glm::normalize(glm::cross(target, up)) * distance;
	notify();
}

void Camera::rotate(float x, float y, float sensitivity) {
	alpha -= y * sensitivity;
	fi -= x * sensitivity;

	if (alpha > 179.0f)
		alpha = 179.0f;
	if (alpha < 1.0f)
		alpha = 1.0f;

	notify();
}