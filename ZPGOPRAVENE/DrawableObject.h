#pragma once
#include "Model.h"
#include "CompositeTransformation.h"
#include "ShaderProgram.h"
#include "Texture.h"

class DrawableObject {
protected:
	ShaderProgram* shaderProgram;
	Model* model;
	ITransformation* transformation;
	glm::vec3 color;
	Texture* texture;
public:
	DrawableObject(DrawableObject& object);
	DrawableObject(Model* model, glm::vec3 color, ShaderProgram* shaderProgram, Texture* texture = nullptr);
	DrawableObject(Model* model, glm::vec3 color, ITransformation* startingTransformation, ShaderProgram* shaderProgram, Texture* texture = nullptr);
	void addTransformation(ITransformation* transformation);
	void setTransformation(ITransformation* transformation);
	virtual void draw(bool isSelected = false);
	~DrawableObject();
};