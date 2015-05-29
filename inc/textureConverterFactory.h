#ifndef TEXTURE_CONVERTER_FACTORY
#define TEXTURE_CONVERTER_FACTORY
#pragma once

#include "appOptions.h"
#include "textureConvertor.h"

class TextureConverterFactory
{
	TextureConverterFactory() = delete;
	TextureConverterFactory(const TextureConverterFactory& other) = delete;
	bool operator=(const TextureConverterFactory& other) = delete;
public:
	static ShadeTextureConverter* make(Operations op)
	{
		switch (op) {
		case Operations::generateNormalTexture:
			return new ShadeTextureToNormalConverter();
		case Operations::generateDepthTexture:
			return new ShadeTextureToDepthConverter();
		case Operations::generateAmbientTexture:
			return new ShadeTextureToAmbientConverter();
		case Operations::none:
		default:
			return nullptr;
		}
	}
};

#endif /* TEXTURE_CONVERTER_FACTORY */
