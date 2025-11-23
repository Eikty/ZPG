#pragma once
#include "ILight.h"

class DirectionalLight : public ILight {
private:
	glm::vec3 direction;
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity, ShaderProgram* shaderProgram);
	void draw(int index, int size) override;
};