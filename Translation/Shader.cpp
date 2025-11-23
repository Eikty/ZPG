#include "Shader.h"

Shader::Shader(const char* vertexCode, const char* fragmentCode) {
	createShader(GL_VERTEX_SHADER, vertexCode);
	createShader(GL_FRAGMENT_SHADER, fragmentCode);
}

void Shader::createShader(GLenum shaderType, const char* shaderCode) {
	switch (shaderType) {
	case GL_VERTEX_SHADER:
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &shaderCode, NULL);
		glCompileShader(vertexShader);
		break;
	case GL_FRAGMENT_SHADER:
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &shaderCode, NULL);
		glCompileShader(fragmentShader);
		break;
	}
}

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open()) {
		std::cout << "Unable to open file " << shaderFile << std::endl;
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	createShader(shaderType, shaderCode.c_str());
}

void Shader::attachShader(GLuint idShaderProgram) {
	glAttachShader(idShaderProgram, vertexShader);
	glAttachShader(idShaderProgram, fragmentShader);
}