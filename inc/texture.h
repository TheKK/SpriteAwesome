#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>
#include <cassert>

class Texture
{
public:
	Texture();
	Texture(const std::string& filePath);

	~Texture();

	bool used() const { return surface_ != nullptr; }

	int load(const std::string& filePath);

	uint32_t width() const
	{
		assert(surface_);

		return surface_->w;
	}

	uint32_t height() const
	{
		assert(surface_);

		return surface_->h;
	}

	uint32_t bpp() const
	{
		assert(surface_);

		return surface_->format->BytesPerPixel;
	}

	void* pixels()
	{
		assert(surface_);

		return surface_->pixels;
	}
private:
	SDL_Surface* surface_ = nullptr;
};

#endif /* TEXTURE_H */
