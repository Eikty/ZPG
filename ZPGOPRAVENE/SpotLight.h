#pragma once
#include "ILight.h"

class SpotLight : public ILight {
protected:
	glm::vec3 direction;
	float alpha;
public:
	SpotLight(glm::vec3 direction, float alpha, glm::vec3 color, float intensity, ShaderProgram* shaderProgram, ITransformation* transformations = nullptr);
	void draw(int index, int size) override;
};