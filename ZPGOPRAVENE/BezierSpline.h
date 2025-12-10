#pragma once
#include <vector>
#include "BezierCurve.h"

using namespace std;

class BezierSpline : public BezierCurve {
protected:
	int current;
	vector<glm::mat4> allPoints;
	vector<glm::vec3> tempPoints;

public:
	BezierSpline(glm::vec3 startingPoint = glm::vec3(0.0f), float delta = 0.01f) : BezierCurve(glm::mat4(), delta) {
		current = 0;
		tempPoints.push_back(startingPoint);
	}

	void addPoint(glm::vec3 point) {
		tempPoints.push_back(point);

		if (tempPoints.size() == 4) {
			allPoints.push_back(glm::mat4(
				glm::vec4(tempPoints[0], 1.0f),
				glm::vec4(tempPoints[1], 1.0f),
				glm::vec4(tempPoints[2], 1.0f),
				glm::vec4(tempPoints[3], 1.0f)
			));

			tempPoints[0] = tempPoints[3];
			tempPoints.erase(tempPoints.begin() + 1, tempPoints.end());
		}
	}

	glm::mat4 transform() override {
		if (allPoints.empty())
			return glm::translate(glm::mat4(1.0f), tempPoints[0]);

		points = allPoints[current];
		
		glm::vec4 p = glm::vec4(t * t * t, t * t, t, 1.0f);
		glm::vec4 dp = glm::vec4(3 * t * t, 2 * t, 1.0f, 0.0f);

		glm::vec3 point = glm::vec3(p * bernstein * glm::transpose(points));
		glm::vec3 tangent = glm::vec3(dp * bernstein * glm::transpose(points));

		glm::vec3 forward = glm::normalize(-tangent);

		if (length(tangent) == 0)
			forward = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		up = glm::normalize(glm::cross(forward, right));

		if (t >= 1.0f) {
			if (current < allPoints.size() - 1) {
				current++;
				t = 0.0f;
			}
			else {
				delta *= -1;
				t = 1.0f;
			}
		}
		else if (t <= 0.0f) {
			if (current > 0) {
				current--;
				t = 1.0f;
			}
			else {
				delta *= -1;
				t = 0.0f;
			}
		}

		t += delta;

		return glm::mat4(
			glm::vec4(right, 0),
			glm::vec4(up, 0),
			glm::vec4(forward, 0),
			glm::vec4(point, 1)
		);
	}
};