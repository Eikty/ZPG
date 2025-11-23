#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string>
#include "Shader.h"
#include "ICameraObserver.h"
#include "Camera.h"
#include "Material.h"

using namespace std;

class Camera;
class ShaderProgram : public ICameraObserver {
private:
	GLuint programID;
	Shader* shader;
	Camera* camera;

	void check();
public:
	ShaderProgram(Shader*& shader);
	void setCamera(Camera* camera);
	void use(glm::mat4 modelMatrix, glm::vec3 color, Material* material = nullptr);
	void setUniform(string name, glm::mat4 M);
	void setUniform(string name, glm::vec3 v);
	void setUniform(string name, float f);
	void setUniform(string name, int i);
	void update() override;
};