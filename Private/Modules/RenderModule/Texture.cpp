
#include "Modules/RenderModule/Texture.h"

bool Texture::Load(const std::string& path)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(path.c_str(), &mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);

	if (!image)
	{
		SDL_Log("Texture::Load: SOIL failed to load image %s : %s", path.c_str(), SOIL_last_result());
		return false;
	}

	int format = channels == 4 ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID);
	SetActive();

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

