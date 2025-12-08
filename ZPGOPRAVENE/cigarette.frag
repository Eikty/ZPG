#version 330

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D textureUnitID;

void main() {
    fragColor = texture(textureUnitID, texCoords);
}