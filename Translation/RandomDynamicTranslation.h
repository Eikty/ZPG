#pragma once
#include "Translation.h"

class RandomDynamicTranslation : public Translation {
private:
	int frame;
	int interval;
	glm::vec3 randomMovement;
public:
	RandomDynamicTranslation(glm::vec3 direction, int interval) : Translation(direction) {
		frame = interval;
		this->interval = interval;
	}

	glm::mat4 transform() override {
		if (frame++ >= interval) {
			float randX = (rand() % 11 - 5) / 100.0f;
			float randY = (rand() % 11 - 5) / 100.0f;
			float randZ = (rand() % 11 - 5) / 100.0f;
			randomMovement = glm::vec3(randX * vector.x, randY * vector.y, randZ * vector.z);

			frame = 0;
		}

		return glm::translate(glm::mat4(1.0f), randomMovement);
	}
};