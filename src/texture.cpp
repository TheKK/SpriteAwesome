#include <SDL2/SDL_image.h>
#include <stdexcept>

#include "texture.h"

Texture::Texture()
{
}

Texture::Texture(const std::string& filePath)
{
	if (load(filePath))
		throw std::runtime_error(IMG_GetError());
}

Texture::~Texture()
{
	SDL_FreeSurface(surface_);
	surface_ = nullptr;
}

int
Texture::load(const std::string& filePath)
{
	surface_ = IMG_Load(filePath.c_str());
	if (!surface_)
		return -1;

	return 0;
}
