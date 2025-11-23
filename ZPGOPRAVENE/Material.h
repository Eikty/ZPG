#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Material {
private:
	float ra;
	float rd;
	float rs;
	float h;
public:
	Material(float ra, float rd, float rs, float h) {
		this->ra = ra;
		this->rd = rd;
		this->rs = rs;
		this->h = h;
	}

	glm::vec3 getMaterial() {
		return glm::vec3(ra, rd, rs);
	}

	float getShininess() {
		return h;
	}
};