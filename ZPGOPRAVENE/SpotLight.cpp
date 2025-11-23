#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 direction, float alpha, glm::vec3 color, float intensity, ShaderProgram* shaderProgram, ITransformation* transformations) : ILight(color, intensity, glm::vec3(), 0.0f, shaderProgram, transformations) {
	this->direction = direction;
	this->alpha = alpha;
}

void SpotLight::draw(int index, int size) {
	shaderProgram->use(transformations->transform(), color);

	std::string lights = "lights[" + std::to_string(index) + "]";

	shaderProgram->setUniform(lights + ".type", 1);

	shaderProgram->setUniform(lights + ".color", color);
	shaderProgram->setUniform(lights + ".intensity", intensity);

	glm::mat4 modelMatrix = transformations ? transformations->transform() : glm::mat4(1.0f);
	shaderProgram->setUniform(lights + ".position", glm::vec3(modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

	shaderProgram->setUniform(lights + ".constant", 1.0f);
	shaderProgram->setUniform(lights + ".linear", 0.3f);
	shaderProgram->setUniform(lights + ".quadratic", 0.3f);

	shaderProgram->setUniform(lights + ".maxRange", 100.0f);

	shaderProgram->setUniform(lights + ".direction", direction);
	shaderProgram->setUniform(lights + ".alpha", cos(glm::radians(alpha)));

	shaderProgram->setUniform("lightsCount", size);

	glUseProgram(0);
}