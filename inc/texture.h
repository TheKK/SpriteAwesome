#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>
#include <cassert>

class ITexture
{
public:
	virtual ~ITexture() {}

	virtual bool used() const = 0;
	virtual int load(const std::string& filePath) = 0;

	virtual uint32_t width() const = 0;
	virtual uint32_t height() const = 0;
	virtual uint32_t bpp() const = 0;

	virtual void* pixels() const = 0;
};

class SDLTextureImpl : public ITexture
{
public:
	SDLTextureImpl() {}
	SDLTextureImpl(const std::string& filePath);
	SDLTextureImpl(const SDLTextureImpl& other);

	SDLTextureImpl& operator=(const SDLTextureImpl& other);
	bool operator==(const SDLTextureImpl& other);

	virtual ~SDLTextureImpl();

	virtual bool used() const { return surface_ != nullptr; }

	virtual int load(const std::string& filePath);

	virtual uint32_t width() const
	{
		assert(surface_);

		return surface_->w;
	}

	virtual uint32_t height() const
	{
		assert(surface_);

		return surface_->h;
	}

	virtual uint32_t bpp() const
	{
		assert(surface_);

		return surface_->format->BytesPerPixel;
	}

	virtual void* pixels() const
	{
		assert(surface_);

		return surface_->pixels;
	}
private:
	SDL_Surface* surface_ = nullptr;

	SDL_Surface* createSurfaceFromOther_(const SDLTextureImpl& other)
	{
		assert(other.surface_);

		SDL_Surface* newSurface;

		newSurface = SDL_CreateRGBSurfaceFrom(
			other.pixels(),
			other.width(),
			other.height(),
			other.bpp() * 8,
			other.surface_->pitch,
			other.surface_->format->Rmask,
			other.surface_->format->Gmask,
			other.surface_->format->Bmask,
			other.surface_->format->Amask);

		return newSurface;
	}
};



#endif /* TEXTURE_H */
