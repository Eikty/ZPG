#pragma once
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "ITransformation.h"

using namespace std;

class CompositeTransformation : public ITransformation {
private:
    vector<ITransformation*> transformations;
    glm::mat4 modelMatrix;
public:
    CompositeTransformation();
    glm::mat4 transform() override;
    void addTransformation(ITransformation* transformation);
    ~CompositeTransformation();
};