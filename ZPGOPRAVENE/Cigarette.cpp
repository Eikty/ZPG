#include "Cigarette.h"

Cigarette::Cigarette() {
	Shader* newCigaretteShader = new Shader();
	newCigaretteShader->createShaderFromFile(GL_VERTEX_SHADER, "cigarette.vert");
	newCigaretteShader->createShaderFromFile(GL_FRAGMENT_SHADER, "cigarette.frag");
	this->shaderProgram = new ShaderProgram(newCigaretteShader);
	
	model = new Model("cigarette.obj", new Material(1.0f, 0.8f, 0.1f, 8.0f));
	texture = new Texture("Textures/cigarette.png");

	transformations = new CompositeTransformation();
	transformations->addTransformation(new Translation(glm::vec3(0.6f, -0.5f, -1.2f)));
	transformations->addTransformation(new Rotation(glm::radians(-100.0f), glm::vec3(1.0f, 0.8f, 0.0f)));
	transformations->addTransformation(new Rotation(glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	transformations->addTransformation(new Scale(glm::vec3(0.1f)));
}

void Cigarette::setCamera(Camera* camera) {
	shaderProgram->setCamera(camera);
}

void Cigarette::draw(glm::mat4 cameraViewMatrix) {
	glDisable(GL_DEPTH_TEST);

    shaderProgram->use(transformations->transform(), glm::vec3(-1.0f), model->getMaterial());
    texture->bind(0);

    shaderProgram->setUniform("textureUnitID", 0);
    shaderProgram->setUniform("viewMatrix", glm::mat4(1.0f));

    model->draw();

    texture->unbind();
    glUseProgram(0);

	glEnable(GL_DEPTH_TEST);
}