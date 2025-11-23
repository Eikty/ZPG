#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;

uniform float w;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPos;
out vec3 worldNormal;
out vec2 texCoords;

void main() {
    vec4 homPos = vec4(vp * w, w);

    worldPos = vec3(modelMatrix * homPos);
    worldPos = worldPos / homPos.w;
    worldNormal= normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * homPos;
    texCoords = uv;
}