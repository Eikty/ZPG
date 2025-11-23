#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, glm::vec3 color, ShaderProgram* shaderProgram, Texture* texture) {
	this->shaderProgram = shaderProgram;
	this->model = model;
	this->color = color;
	this->texture = texture;
	transformation = new CompositeTransformation();
}

DrawableObject::DrawableObject(Model* model, glm::vec3 color, ITransformation* startingTransformation, ShaderProgram* shaderProgram, Texture* texture) : DrawableObject(model, color, shaderProgram, texture) {
	transformation->addTransformation(startingTransformation);
}

void DrawableObject::addTransformation(ITransformation* transformation) {
	this->transformation->addTransformation(transformation);
}

void DrawableObject::draw(bool isSelected) {
	shaderProgram->use(transformation->transform(), color, model->getMaterial());
	if (texture)
		texture->bind(0);
	shaderProgram->setUniform("textureUnitID", 0);
	if (isSelected)
		shaderProgram->setUniform("isSelected", 1);
	model->draw();
	texture->unbind();
	glUseProgram(0); 
}

void DrawableObject::setTransformation(ITransformation* transformation) {
	this->transformation = transformation;
}

DrawableObject::~DrawableObject() {
	if (shaderProgram)
		delete shaderProgram;

	if (model)
		delete model;

	if (transformation)
		delete transformation;
}