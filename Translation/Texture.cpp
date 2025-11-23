#include "Texture.h"
#include <stb_image.h>

Texture::Texture(std::string filePath) {
	int width, height, channels;
	textureID = channels = height = channels = 0;
	this->filePath = filePath;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 4);

	if (!data) {
		std::cerr << "Error loading texture: " << filePath << std::endl;
	}

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	unbind();
}

void Texture::bind(GLuint slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}