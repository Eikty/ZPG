#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader* shader) : IObserver() {
	programID = glCreateProgram();

	this->shader = shader;
	this->shader->attachShader(programID);

	glLinkProgram(programID);

	check();

	this->camera = nullptr;
}

void ShaderProgram::setCamera(Camera* camera) {
	this->camera = camera;
	this->camera->addObserver(this);
}

void ShaderProgram::check() {
	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void ShaderProgram::use(glm::mat4 modelMatrix, glm::vec3 color, Material* material) {
	glUseProgram(programID);
	setUniform("modelMatrix", modelMatrix);
	setUniform("w", modelMatrix[3][3]);
	setUniform("projectionMatrix", camera->getProjectionMatrix());

	setUniform("viewMatrix", camera->getCamera());
	setUniform("viewPosition", glm::vec3(camera->getPosition()));

	setUniform("objectColor", color);
	setUniform("isSelected", 0);

	if (material != nullptr) {
		glm::vec3 coefficients = material->getMaterial();
		setUniform("ra", coefficients.x);
		setUniform("rd", coefficients.y);
		setUniform("rs", coefficients.z);
		setUniform("h", material->getShininess());
	}
}

void ShaderProgram::setUniform(string name, glm::mat4 M) {
	GLint idModelTransform = glGetUniformLocation(programID, name.c_str());
	if (idModelTransform  != -1) {
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
	}
}

void ShaderProgram::setUniform(string name, glm::vec3 v) {
	GLint idModelTransform = glGetUniformLocation(programID, name.c_str());
	if (idModelTransform != -1) {
		glUniform3fv(idModelTransform, 1, &v[0]);
	}
}

void ShaderProgram::setUniform(string name, float f) {
	GLint idModelTransform = glGetUniformLocation(programID, name.c_str());
	if (idModelTransform != -1) {
		glUniform1f(idModelTransform, f);
	}
}

void ShaderProgram::setUniform(string name, int i) {
	GLint idModelTransform = glGetUniformLocation(programID, name.c_str());
	if (idModelTransform != -1) {
		glUniform1i(idModelTransform, i);
	}
}

void ShaderProgram::update() {
	setUniform("viewMatrix", camera->getCamera());
	setUniform("projectionMatrix", camera->getProjectionMatrix());
}