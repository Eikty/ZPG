#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Camera.h"
#include "ITransformation.h"
#include "CompositeTransformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "DynamicRotation.h"
#include "Scale.h"

class Cigarette {
private:
    ShaderProgram* shaderProgram;
    Model* model;
    Texture* texture;
    ITransformation* transformations;
public:
    Cigarette();
    void setCamera(Camera* camera);
    void draw(glm::mat4 cameraViewMatrix);
};