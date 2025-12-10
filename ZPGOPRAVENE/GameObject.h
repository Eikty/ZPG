#pragma once
#include "DrawableObject.h"
#include "BezierCurve.h"

class GameObject : public DrawableObject {
private:
	static int score;
	int scoreAdder;
	BezierCurve* movement;

	void respawn(bool randomStart = false);
public:
	GameObject(int scoreAdder, Model* model, glm::vec3 color, ShaderProgram* shaderProgram, Texture* texture = nullptr);
	GameObject(int scoreAdder, Model* model, glm::vec3 color, ITransformation* startingTransformation, ShaderProgram* shaderProgram, Texture* texture = nullptr);
	bool isGameObject() override;
	void draw(bool isSelected = false) override;
};