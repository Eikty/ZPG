#pragma once
#include "ILight.h"
#include "Model.h"

class PointLight : public ILight {
private:
	ShaderProgram* modelShader;
	Model* model;
public:
	PointLight(glm::vec3 color, float intensity, glm::vec3 attenuation, float maxRange, ShaderProgram* shaderProgram, Model* model = nullptr, ShaderProgram* modelShader = nullptr);
	PointLight(glm::vec3 color, float intensity, glm::vec3 attenuation, float maxRange, ShaderProgram* shaderProgram, ITransformation* transformations, Model* model = nullptr, ShaderProgram* modelShader = nullptr);
	void draw(int index, int size) override;
};