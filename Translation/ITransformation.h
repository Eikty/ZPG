#pragma once
#include <glm/gtc/matrix_transform.hpp>

class ITransformation {
public:
	virtual void addTransformation(ITransformation* transformation) {};
	virtual glm::mat4 transform() = 0;
};