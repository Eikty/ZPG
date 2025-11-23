#include "Flashlight.h"

Flashlight::Flashlight(ShaderProgram* shaderProgram, Camera* camera, float alpha, glm::vec3 color, float intensity) : SpotLight(camera->getDirection(), alpha, color, intensity, shaderProgram, nullptr) {
	this->position = camera->getPosition();
	this->camera = camera;
	this->camera->addObserver(this);

	enabled = true;
}

void Flashlight::toggle() {
	enabled = !enabled;
}

void Flashlight::draw(int index, int size) {
	shaderProgram->use(transformations->transform(), color);

	std::string lights = "lights[" + std::to_string(index) + "]";

	shaderProgram->setUniform(lights + ".type", 1);

	shaderProgram->setUniform(lights + ".color", color);
	shaderProgram->setUniform(lights + ".intensity", intensity);

	glm::mat4 modelMatrix = transformations ? transformations->transform() : glm::mat4(1.0f);
	shaderProgram->setUniform(lights + ".position", position);

	shaderProgram->setUniform(lights + ".constant", 1.0f);
	shaderProgram->setUniform(lights + ".linear", 0.045f);
	shaderProgram->setUniform(lights + ".quadratic", 0.0075f);

	shaderProgram->setUniform(lights + ".maxRange", enabled ? 100.0f : 0.0f);

	shaderProgram->setUniform(lights + ".direction", direction);
	shaderProgram->setUniform(lights + ".alpha", cos(glm::radians(alpha)));

	shaderProgram->setUniform("lightsCount", size);
}

void Flashlight::update() {
	position = camera->getPosition();
	direction = camera->getDirection();
}