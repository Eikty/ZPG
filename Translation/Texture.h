#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <iostream>

class Texture {
private:
	GLuint textureID;
	std::string filePath;
public:
	Texture(std::string filePath);
	void bind(GLuint slot);
	void unbind();
};