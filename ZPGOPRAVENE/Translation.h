#pragma once
#include "ITransformation.h"

class Translation : public ITransformation {
protected:
	glm::vec3 vector;
public:
	Translation(glm::vec3 vector) {
		this->vector = vector;
	}

	glm::mat4 transform() override {
		return glm::translate(glm::mat4(1.0f), vector);
	}
};