#pragma once
#include "ITransformation.h"

class BezierCurve : public ITransformation {
protected:
	glm::mat4 bernstein, points;
	float t, delta;
public:
	BezierCurve(glm::mat4 points, float t = 0.5f, float delta = 0.01f) {
		this->points = points;
		this->t = t;
		this->delta = delta;

		bernstein = glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0)
		);
	}

	glm::mat4 transform() override {
		glm::vec4 p = glm::vec4(t * t * t, t * t, t, 1.0f);
		glm::vec4 dp = glm::vec4(3 * t * t, 2 * t, 1.0f, 0.0f);

		glm::vec3 point = glm::vec3(p * bernstein * glm::transpose(points));
		glm::vec3 tangent = glm::vec3(dp * bernstein * glm::transpose(points));

		if (t >= 1.0f || t <= 0.0f)
			delta *= -1;

		t += delta;

		if (glm::length(tangent) < 0.001f)
			tangent = glm::vec3(0, 0, 1);

		return glm::inverse(glm::lookAt(point, point + tangent, glm::vec3(0.0f, 1.0f, 0.0f)));
	}
};