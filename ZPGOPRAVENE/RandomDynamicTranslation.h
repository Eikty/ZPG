#pragma once
#include "ITransformation.h"

class RandomDynamicTranslation : public ITransformation {
protected:
	glm::vec3 currentPosition, currentDestination;
	float minMove, maxMove;
	float t, delta;
public:
	RandomDynamicTranslation(glm::vec3 startingPosition, float minMove, float maxMove, float delta = 0.01f) {
		currentPosition = currentDestination = startingPosition;
		this->minMove = minMove * 100;
		this->maxMove = maxMove * 100;
		t = 0.0f;
		this->delta = delta;
	}

	glm::mat4 transform() override {
		float movementX;
		float movementY;
		float movementZ;

		if (t >= 1) {
			movementX = (rand() % ((int)maxMove - (int)minMove + 1) + minMove) / 100;
			movementY = (rand() % 2 - 1) / 10;
			movementZ = (rand() % ((int)maxMove - (int)minMove + 1) + minMove) / 100;

			if (rand() % 2) {
				movementX *= -1;
			}
			if (rand() % 2) {
				movementZ *= -1;
			}

			currentPosition = currentDestination;
			currentDestination = glm::vec3(currentPosition.x + movementX, currentPosition.y + movementY, currentPosition.z + movementZ);
			t = 0;
		}

		t += delta;

		movementX = currentPosition.x + (currentDestination.x - currentPosition.x) * t;
		movementY = currentPosition.y + (currentDestination.y - currentPosition.y) * t;
		movementZ = currentPosition.z + (currentDestination.z - currentPosition.z) * t;

		return glm::translate(glm::mat4(1.0f), glm::vec3(movementX, movementY, movementZ));
	}
};