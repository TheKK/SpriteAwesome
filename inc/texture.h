#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>

class Texture
{
public:
	Texture();
	Texture(const std::string& filePath);

	uint32_t width() const { return width_; };
	uint32_t height() const { return height_; };

	uint32_t bpp() const { return bpp_; };
private:
	uint32_t width_, height_;
	uint32_t bpp_;
};

#endif /* TEXTURE_H */
