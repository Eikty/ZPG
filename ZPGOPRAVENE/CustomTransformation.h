#pragma once
#include "ITransformation.h"

class CustomTransformation : public ITransformation {
protected:
	glm::mat4 matrix;
public:
	CustomTransformation(glm::mat4 matrix) {
		this->matrix = matrix;
	}

	glm::mat4 transform() override {
		return matrix;
	}
};