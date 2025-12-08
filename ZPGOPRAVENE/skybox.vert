#version 330 core
layout (location = 0) in vec3 uvw;

uniform float w = 500;

uniform mat4 projection;
uniform mat4 view;

out vec3 texCoords;

void main() {
    texCoords = uvw;
    vec4 pos = projection * view * vec4(uvw * w, w);
    gl_Position = pos.xyww;
}