#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "ShaderProgram.h"
#include "ITransformation.h"
#include "CompositeTransformation.h"

class ILight {
protected:
	glm::vec3 color;
	float intensity;
	glm::vec3 attenuation;
	float maxRange;
	ITransformation* transformations;
	ShaderProgram* shaderProgram;
public:
	ILight(glm::vec3 color, float intensity, glm::vec3 attenuation, float maxRange, ShaderProgram* shaderProgram, ITransformation* startingTransformation = nullptr) {
		this->color = color;
		this->intensity = intensity;
		this->attenuation = attenuation;
		this->maxRange = maxRange;
		this->shaderProgram = shaderProgram;

		transformations = new CompositeTransformation();

		if (startingTransformation)
			transformations->addTransformation(startingTransformation);
	}

	void addTransformation(ITransformation* transformation) {
		transformations->addTransformation(transformation);
	}

	virtual void draw(int index, int size) = 0;
};