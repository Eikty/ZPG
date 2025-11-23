#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity, ShaderProgram* shaderProgram) : ILight(color, intensity, glm::vec3(), 0.0f, shaderProgram, nullptr) {
	this->direction = direction;
}

void DirectionalLight::draw(int index, int size) {
	shaderProgram->use(glm::mat4(1.0f), color);

	std::string lights = "lights[" + std::to_string(index) + "]";

	shaderProgram->setUniform(lights + ".type", 2);

	shaderProgram->setUniform(lights + ".color", color);
	shaderProgram->setUniform(lights + ".intensity", intensity);

	shaderProgram->setUniform(lights + ".position", glm::vec3(glm::mat4(1.0f) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

	shaderProgram->setUniform(lights + ".direction", direction);

	shaderProgram->setUniform("lightsCount", size);

	glUseProgram(0);
}