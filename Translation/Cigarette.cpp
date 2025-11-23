#include "Cigarette.h"

Cigarette::Cigarette(ShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
	model = new Model(cigarette, (sizeof(cigarette) / sizeof(*cigarette)) / 8, new Material(0.1f, 0.8f, 0.1f, 8.0f), true);
	texture = new Texture("Textures/cigarette.png");

	transformations = new CompositeTransformation();
	transformations->addTransformation(new Translation(glm::vec3(0.2f, -0.3f, -0.44f)));
	transformations->addTransformation(new Rotation(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	transformations->addTransformation(new Rotation(glm::radians(210.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	transformations->addTransformation(new Rotation(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	transformations->addTransformation(new Scale(glm::vec3(0.1f)));
}

void Cigarette::draw(glm::mat4 cameraViewMatrix) {
	glDisable(GL_DEPTH_TEST);

    shaderProgram->use(transformations->transform(), glm::vec3(-1.0f), model->getMaterial());
    texture->bind(0);

    shaderProgram->setUniform("textureUnitID", 0);
    shaderProgram->setUniform("viewMatrix", glm::mat4(1.0f));

    glm::mat4 overlayViewMatrix = cameraViewMatrix;

    overlayViewMatrix[3][0] = 0.0f;
    overlayViewMatrix[3][1] = 0.0f;
    overlayViewMatrix[3][2] = 0.0f;

    shaderProgram->setUniform("viewMatrix", overlayViewMatrix);

    model->draw();

    texture->unbind();
    glUseProgram(0);

	glEnable(GL_DEPTH_TEST);
}