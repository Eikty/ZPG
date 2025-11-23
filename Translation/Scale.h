#pragma once
#include "ITransformation.h"

class Scale : public ITransformation {
private:
	glm::vec3 vector;
public:
	Scale(glm::vec3 vector) {
		this->vector = vector;
	}

	glm::mat4 transform() override {
		return glm::scale(glm::mat4(1.0f), vector);
	}
};