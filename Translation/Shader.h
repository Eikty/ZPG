#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

class Shader {
private:
	GLuint vertexShader;
	GLuint fragmentShader;
public:
	Shader(const char* vertexCode =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"void main () {"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
		"}",
		const char* fragmentCode =
		"#version 330\n"
		"uniform vec3 objectColor;"
		"out vec4 fragColor;"
		"void main () {"
		"     fragColor = vec4 (objectColor, 1.0);"
		"}");
	void createShader(GLenum shaderType, const char* shaderCode);
	void createShaderFromFile(GLenum shaderType, const char* shaderFile);
	void attachShader(GLuint idShaderProgram);
};