#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 attenuation, float maxRange, ShaderProgram* shaderProgram, Model* model, ShaderProgram* modelShader) : ILight(color, intensity, attenuation, maxRange, shaderProgram) {
	this->modelShader = modelShader;
	this->model = model;
}

PointLight::PointLight(glm::vec3 color, float intensity, glm::vec3 attenuation, float maxRange, ShaderProgram* shaderProgram, ITransformation* transformations, Model* model, ShaderProgram* modelShader): ILight(color, intensity, attenuation, maxRange, shaderProgram, transformations) {
	this->modelShader = modelShader;
	this->model = model;
}

void PointLight::draw(int index, int size) {
	shaderProgram->use(transformations->transform(), color);

	std::string lights = "lights[" + std::to_string(index) + "]";

	shaderProgram->setUniform(lights + ".type", 0);

	shaderProgram->setUniform(lights + ".color", color);
	shaderProgram->setUniform(lights + ".intensity", intensity);

	glm::mat4 modelMatrix = transformations ? transformations->transform() : glm::mat4(1.0f);
	shaderProgram->setUniform(lights + ".position", glm::vec3(modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

	shaderProgram->setUniform(lights + ".constant", attenuation.x);
	shaderProgram->setUniform(lights + ".linear", attenuation.y);
	shaderProgram->setUniform(lights + ".quadratic", attenuation.z);

	shaderProgram->setUniform(lights + ".maxRange", maxRange);

	shaderProgram->setUniform("lightsCount", size);

	if (modelShader && model) {
		modelShader->use(transformations->transform(), color);
		model->draw();
	}

	glUseProgram(0);
}