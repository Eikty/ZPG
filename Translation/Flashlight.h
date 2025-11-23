#pragma once
#include "SpotLight.h"
#include "ICameraObserver.h"

class Flashlight : public SpotLight, ICameraObserver {
private:
	glm::vec3 position;
	Camera* camera;
	bool enabled;
public:
	Flashlight(ShaderProgram* shaderProgram, Camera* camera, float alpha = 25, glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.8f), float intensity = 1.0f);
	void toggle();
	void draw(int index, int size) override;
	void update() override;
};