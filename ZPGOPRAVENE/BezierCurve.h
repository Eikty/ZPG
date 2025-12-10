#pragma once
#include "ITransformation.h"

class BezierCurve : public ITransformation {
protected:
	glm::mat4 bernstein, points;
	float t, delta;
public:
	BezierCurve(glm::mat4 points, float delta = 0.01f) {
		this->points = points;
		t = 0.0f;
		this->delta = delta;

		bernstein = glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0)
		);
	}

	bool isFinished() {
		return t >= 1.0f;
	}

	void reset(glm::mat4 newPoints) {
		this->points = newPoints;
		this->t = 0.0f;
		this->delta = abs(delta);
	}

	void setT(float t) {
		this->t = t;
	}

	glm::mat4 transform() override {
		glm::vec4 p = glm::vec4(t * t * t, t * t, t, 1.0f);
		glm::vec4 dp = glm::vec4(3 * t * t, 2 * t, 1.0f, 0.0f);

		glm::vec3 point = glm::vec3(p * bernstein * glm::transpose(points));
		glm::vec3 tangent = glm::vec3(dp * bernstein * glm::transpose(points));

		glm::vec3 forward = glm::normalize(-tangent);

		if (length(tangent) == 0.f)
			forward = glm::vec3(0.0f, 0.0f, -1.0f);

		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		up = glm::normalize(glm::cross(forward, right));

		t += delta;

		if (t >= 1.0f || t <= 0.0f)
			delta *= -1;

		return glm::mat4(
			glm::vec4(right, 0),
			glm::vec4(up, 0),
			glm::vec4(forward, 0),
			glm::vec4(point, 1)
		);
	}
};