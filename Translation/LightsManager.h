#pragma once
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "ILight.h"
#include "ShaderProgram.h"

class LightsManager {
private:
	vector<ILight*> lights;
public:
	void addLight(ILight* light);
	void draw();
	~LightsManager();
};