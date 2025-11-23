#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "tiny_obj_loader.h"
#include "Material.h"

class Model {
private:
	GLuint VBO, VAO;
	GLsizei pointsCount;
	Material* material;
public:
	Model(const float* points, GLsizei pointsCount, Material* material, bool uv = false);
	Model(const char* name, Material* material);
	void draw();
	Material* getMaterial();
};