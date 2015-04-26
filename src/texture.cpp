#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cstring>

#include "texture.h"

SDLTextureImpl::SDLTextureImpl(const std::string& filePath)
{
	if (load(filePath))
		throw std::runtime_error(IMG_GetError());
}

SDLTextureImpl::SDLTextureImpl(const SDLTextureImpl& other)
{
	if (!other.surface_)
		return;

	surface_ = createSurfaceFromOther_(other);
	if (!surface_)
		throw std::runtime_error(SDL_GetError());
}

SDLTextureImpl&
SDLTextureImpl::operator=(const SDLTextureImpl& other)
{
	if (surface_)
		SDL_FreeSurface(surface_);

	if (other.surface_) {
		surface_ = createSurfaceFromOther_(other);
		if (!surface_)
			throw std::runtime_error(SDL_GetError());
	} else {
		surface_ = nullptr;
	}

	return *this;
}

bool
SDLTextureImpl::operator==(const SDLTextureImpl& other)
{
	if (surface_ == nullptr && other.surface_ == nullptr)
		return true;
	else if (surface_ == nullptr || other.surface_ == nullptr)
		return false;

	if (width() != other.width())
		return false;

	if (height() != other.height())
		return false;

	if (bpp() != other.bpp())
		return false;

	if (memcmp(pixels(), other.pixels(),
		   width() * height() * bpp()) != 0)
		return false;

	return true;
}

SDLTextureImpl::~SDLTextureImpl()
{
	SDL_FreeSurface(surface_);
	surface_ = nullptr;
}

int
SDLTextureImpl::load(const std::string& filePath)
{
	surface_ = IMG_Load(filePath.c_str());
	if (!surface_)
		return -1;

	return 0;
}
