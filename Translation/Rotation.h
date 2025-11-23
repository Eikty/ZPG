#pragma once
#include "ITransformation.h"

class Rotation : public ITransformation {
protected:
	float angle;
	glm::vec3 axis;
public:
	Rotation(float angle, glm::vec3 axis) {
		this->angle = angle;
		this->axis = axis;
	}

	glm::mat4 transform() override {
		return glm::rotate(glm::mat4(1.0f), angle, axis);
	}
};