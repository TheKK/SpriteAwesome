#ifndef TEXTURE_CONVERTOR_H
#define TEXTURE_CONVERTOR_H
#pragma once

#include <armadillo>

#include "appOptions.h"
#include "texture.h"

class ShadeTextureToNormalConverter;
class ShadeTextureToDepthConverter;
class ShadeTextureToAmbientConverter;

class ShadeTextureConverter
{
public:
	virtual ~ShadeTextureConverter() {}

	virtual int convert(ITexture& lightUp, ITexture& lightDown,
			    ITexture& lightLeft, ITexture& lightRight,
			    ITexture& result) = 0;
};

class ShadeTextureToNormalConverter : public ShadeTextureConverter
{
public:
	virtual int convert(ITexture& lightUp, ITexture& lightDown,
			    ITexture& lightLeft, ITexture& lightRight,
			    ITexture& result);
private:
	arma::rowvec rotateAroundX_(double degree, arma::rowvec vec);
	arma::rowvec rotateAroundY_(double degree, arma::rowvec vec);
};

class ShadeTextureToDepthConverter : public ShadeTextureConverter
{
public:
	virtual int convert(ITexture& lightUp, ITexture& lightDown,
			    ITexture& lightLeft, ITexture& lightRight,
			    ITexture& result)
	{
		return 0;
	}
private:
};

class ShadeTextureToAmbientConverter : public ShadeTextureConverter
{
public:
	virtual int convert(ITexture& lightUp, ITexture& lightDown,
			    ITexture& lightLeft, ITexture& lightRight,
			    ITexture& result)
	{
		return 0;
	}
private:
};

#endif /* TEXTURE_CONVERTOR_H */
