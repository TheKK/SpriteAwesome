#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cstring>

#include "error.h"

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
SDLTextureImpl::create(uint32_t w, uint32_t h)
{
	if (surface_)
		SDL_FreeSurface(surface_);

	surface_ = SDL_CreateRGBSurface(0, w, h, 24, 0, 0, 0, 0);
	if (!surface_)
		return ERROR_TEX_CREATE_FAILED;

	return 0;
}

int
SDLTextureImpl::load(const std::string& filePath)
{
	surface_ = IMG_Load(filePath.c_str());
	if (!surface_)
		return ERROR_TEX_LOAD_FAILED;

	return 0;
}

/* TODO Fix nameing problem, SDL could only store bmp format */
int
SDLTextureImpl::write(const std::string& fileName)
{
	return SDL_SaveBMP(surface_, fileName.c_str());
}
#endif /* DISABLE_SDL2 */

#ifndef DISABLE_MAGICK_PLUS_PLUS
MagickTextureImpl::MagickTextureImpl(const std::string& filePath):
	img_(filePath)
{
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
MagickTextureImpl::create(uint32_t w, uint32_t h)
{
	try {
		img_.size(std::to_string(w) + "X" + std::to_string(h));
	} catch (const std::exception& e) {
		return ERROR_TEX_CREATE_FAILED;
	}

	return 0;
}

int
MagickTextureImpl::load(const std::string& filePath)
{
	try {
		img_.read(filePath);
	} catch (const std::exception& e) {
		return ERROR_TEX_LOAD_FAILED;
	}

	return 0;
}

int
MagickTextureImpl::write(const std::string& fileName)
{
	try {
		img_.write(fileName);
	} catch (const std::exception& e) {
		return -1;
	}

	return 0;
}
#endif /* DISABLE_MAGICK_PLUS_PLUS */
