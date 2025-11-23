#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation() {
    modelMatrix = glm::mat4(1.0f);
}

glm::mat4 CompositeTransformation::transform() {
    modelMatrix = glm::mat4(1.0f);

    for (ITransformation* transformation : transformations) {
        modelMatrix *= transformation->transform();
    }

    return modelMatrix;
}

void CompositeTransformation::addTransformation(ITransformation* transformation) {
    transformations.push_back(transformation);
}

CompositeTransformation::~CompositeTransformation() {
    for (ITransformation* transformation : transformations)
        delete transformation;
}