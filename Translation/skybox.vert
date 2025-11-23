#version 330 core
layout (location = 0) in vec3 uvw;

out vec3 texCoords;

uniform float w = 500;

uniform mat4 projection;
uniform mat4 view;

void main() {
    texCoords = uvw;
    vec4 pos = projection * view * vec4(uvw * w, w);
    gl_Position = pos.xyww;
}