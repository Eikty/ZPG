#pragma once
#include "Rotation.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DynamicRotation : public Rotation {
private:
	float currentAngle;
public:
	DynamicRotation(float angle, glm::vec3 axis) : Rotation(angle, axis) {
		currentAngle = 0;
	}

	glm::mat4 transform() override {
		currentAngle += angle;
		
		if (currentAngle > 360) {
			currentAngle -= 360;
		}
		else if (currentAngle < -360) {
			currentAngle += 360;
		}

		return glm::rotate(glm::mat4(1.0f), currentAngle, axis);
	}
};