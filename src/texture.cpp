#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cstring>

#include "texture.h"

#ifndef DISABLE_SDL2
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

	if (memcmp(surface_->pixels, other.surface_->pixels,
		   width() * height() * surface_->format->BytesPerPixel) != 0)
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
#endif /* DISABLE_SDL2 */

#ifndef DISABLE_MAGICK_PLUS_PLUS
MagickTextureImpl::MagickTextureImpl(const std::string& filePath)
{
	img_.read(filePath);
}

bool
MagickTextureImpl::operator==(const MagickTextureImpl& other)
{
	if (!used() && !other.used())
		return true;
	else
		return (img_ == other.img_);
}

int
MagickTextureImpl::load(const std::string& filePath)
{
	try {
		img_.read(filePath);
	} catch (const std::exception& e) {
		return -1;
	}

	return 0;
}
#endif /* DISABLE_MAGICK_PLUS_PLUS */
