#pragma once
#include "ITransformation.h"

class RandomDynamicTranslation : public ITransformation {
protected:
	glm::vec3 currentPosition, currentDestination;
	glm::vec3 boundsMin, boundsMax;
	float minMove, maxMove;
	float t, delta;
public:
	RandomDynamicTranslation(glm::vec3 startingPosition, glm::vec3 boundsMin, glm::vec3 boundsMax, float minMove, float maxMove, float delta = 0.01f) {
		currentPosition = currentDestination = startingPosition;
		this->boundsMin = boundsMin;
		this->boundsMax = boundsMax;
		this->minMove = minMove * 100;
		this->maxMove = maxMove * 100;
		t = 1.0f;
		this->delta = delta;
	}

	glm::mat4 transform() override {
		if (t >= 1) {
			float movementX = (rand() % ((int)maxMove - (int)minMove + 1) + minMove) / 100;
			float movementY = (rand() % ((int)maxMove - (int)minMove + 1) + minMove) / 100;
			float movementZ = (rand() % ((int)maxMove - (int)minMove + 1) + minMove) / 100;

			if (rand() % 2) {
				movementX *= -1;
			}
			if (rand() % 2) {
				movementZ *= -1;
			}

			currentPosition = currentDestination;

			currentDestination.x = glm::clamp(currentPosition.x + movementX, boundsMin.x, boundsMax.x);
			currentDestination.y = glm::clamp(currentPosition.y + movementY, boundsMin.y, boundsMax.y);
			currentDestination.z = glm::clamp(currentPosition.z + movementZ, boundsMin.z, boundsMax.z);

			t = 0;
		}

		t += delta;

		return glm::translate(glm::mat4(1.0f), glm::vec3(
				currentPosition.x + (currentDestination.x - currentPosition.x) * t,
				currentPosition.y + (currentDestination.y - currentPosition.y) * t,
				currentPosition.z + (currentDestination.z - currentPosition.z) * t
			));
	}
};