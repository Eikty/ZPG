#include "LightsManager.h"

void LightsManager::addLight(ILight* light) {
	lights.push_back(light);
}

void LightsManager::draw() {
	for (int i = 0; i < lights.size(); i++) {
		lights[i]->draw(i, lights.size());
	}
}

LightsManager::~LightsManager() {
	for (ILight* light : lights)
		delete light;
}