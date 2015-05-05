#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <string>
#include <cstdint>
#include <cassert>

class ITexture
{
public:
	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;

		Color():
			r(0), g(0), b(0) {}

		Color(uint8_t r, uint8_t g, uint8_t b):
			r(r), g(g), b(b) {}

		bool operator==(const Color& other) const
		{
			return ((r == other.r) &&
				(g == other.g) &&
				(b == other.b));
		}
	};

	virtual ~ITexture() {}

	virtual bool used() const = 0;
	virtual int load(const std::string& filePath) = 0;

	virtual uint32_t width() const = 0;
	virtual uint32_t height() const = 0;

	virtual void pixel(uint32_t x, uint32_t y, Color color) = 0;
	virtual Color pixel(uint32_t x, uint32_t y) const = 0;
};

#ifndef DISABLE_SDL2

#include <SDL2/SDL.h>

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

	virtual uint32_t height() const noexcept
	{
		assert(surface_);

		return surface_->h;
	}

	virtual void pixel(uint32_t x, uint32_t y, Color color)
	{
		assert(x < width());
		assert(y < height());

		int offset = y * width() + x;
		Color& colorRef = static_cast<Color*>(surface_->pixels)[offset];

		colorRef = color;
	}

	virtual Color pixel(uint32_t x, uint32_t y) const
	{
		assert(x < width());
		assert(y < height());

		int offset = y * width() + x;
		Color& colorRef = static_cast<Color*>(surface_->pixels)[offset];

		return colorRef;
	}
private:
	SDL_Surface* surface_ = nullptr;

	SDL_Surface* createSurfaceFromOther_(const SDLTextureImpl& other)
	{
		assert(other.surface_);

		SDL_Surface* newSurface;

		newSurface = SDL_CreateRGBSurfaceFrom(
			other.surface_->pixels,
			other.width(),
			other.height(),
			other.surface_->format->BitsPerPixel,
			other.surface_->pitch,
			other.surface_->format->Rmask,
			other.surface_->format->Gmask,
			other.surface_->format->Bmask,
			other.surface_->format->Amask);

		return newSurface;
	}
};
#endif /* DISABLE_SDL2 */

#ifndef DISABLE_MAGICK_PLUS_PLUS

#include <Magick++.h>

class MagickTextureImpl : public ITexture
{
public:
	MagickTextureImpl(): img_() {}
	MagickTextureImpl(const std::string& filePath);

	bool operator==(const MagickTextureImpl& other);

	virtual bool used() const { return img_.isValid(); }

	virtual int load(const std::string& filePath);

	virtual uint32_t width() const
	{
		assert(used());

		return img_.size().width();
	}

	virtual uint32_t height() const
	{
		assert(used());

		return img_.size().height();
	}

	virtual void pixel(uint32_t x, uint32_t y, Color color)
	{
		Magick::ColorRGB magickColor((double) color.r / 255.0,
					     (double) color.g / 255.0,
					     (double) color.b / 255.0);

		img_.pixelColor(x, y, magickColor);
	}

	virtual Color pixel(uint32_t x, uint32_t y) const
	{
		Magick::ColorRGB magickColor = img_.pixelColor(x, y);

		Color color;
		color.r = std::round(magickColor.red() * 255.0);
		color.g = std::round(magickColor.green() * 255.0);
		color.b = std::round(magickColor.blue() * 255.0);

		return color;
	}

private:
	Magick::Image img_;
};
#endif /* DISABLE_MAGICK_PLUS_PLUS */

#endif /* TEXTURE_H */
