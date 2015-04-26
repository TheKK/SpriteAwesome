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
};

#endif /* TEXTURE_H */
