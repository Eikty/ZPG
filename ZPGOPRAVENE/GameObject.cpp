#include "GameObject.h"

int GameObject::score = 0;

GameObject::GameObject(int scoreAdder, Model* model, glm::vec3 color, ShaderProgram* shaderProgram, Texture* texture) : DrawableObject(model, color, shaderProgram, texture) {
	this->scoreAdder = scoreAdder;

    movement = new BezierCurve(glm::mat4(1.0f), (rand() % 5 - 5) / 1000.0f);
	transformation->addTransformation(movement);

	respawn(true);
}

GameObject::GameObject(int scoreAdder, Model* model, glm::vec3 color, ITransformation* startingTransformation, ShaderProgram* shaderProgram, Texture* texture) : DrawableObject(model, color, shaderProgram, texture) {
	this->scoreAdder = scoreAdder;

    movement = new BezierCurve(glm::mat4(1.0f), (rand() % 5 + 5) / 1000.0f);
	transformation->addTransformation(movement);

    transformation->addTransformation(startingTransformation);

	respawn(true);
}

void GameObject::respawn(bool randomStart) {
    glm::vec3 start;
    start.x = rand() % 20 - 10;
    start.y = -2.0f;
    start.z = 40.0f;

    glm::vec3 finish;
    finish.x = rand() % 20 - 10;
    finish.y = -2.0f;
    finish.z = -2.5f;

    glm::mat4 newPoints = glm::mat4(
        glm::vec4(start, 1.0f),
        glm::vec4(start, 1.0f),
        glm::vec4(finish, 1.0f),
        glm::vec4(finish, 1.0f)
    );

    movement->reset(newPoints);

    if (randomStart)
        movement->setT((rand() % 7) / 10.0f);
}

bool GameObject::isGameObject() {
    return true;
}

void GameObject::draw(bool isSelected) {
	if (isSelected) {
		score += scoreAdder;
		fprintf(stdout, "\nTotal score so far: %d\n\n", score);
		DrawableObject::draw(isSelected);
	}

    if (movement->isFinished()) {
        this->respawn();
    }

    DrawableObject::draw(isSelected);
}