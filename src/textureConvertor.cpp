#include <cmath>

#include "error.h"

#include "textureConvertor.h"

int
ShadeTextureToNormalConverter::convert(ITexture& lightUp,
				       ITexture& lightDown,
				       ITexture& lightLeft,
				       ITexture& lightRight,
				       ITexture& result)
{
	int width = result.width(), height = result.height();
	double reflxDegree;
	ITexture::Color lightUpColor, lightDownColor;
	ITexture::Color lightLeftColor, lightRightColor;
	arma::rowvec3 lightUpNormal, lightDownNormal;
	arma::rowvec3 lightLeftNormal, lightRightNormal;
	arma::rowvec3 resultNormal;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			lightUpColor = lightUp.pixel(x, y);
			lightDownColor = lightDown.pixel(x, y);
			lightLeftColor = lightLeft.pixel(x, y);
			lightRightColor = lightRight.pixel(x, y);

			if (lightUpColor.r == 0 &&
			    lightUpColor.g == 0 &&
			    lightUpColor.b == 255) {
				resultNormal = {-1, -1, -1};
			} else {
				reflxDegree = -1 * acos(lightUpColor.r / 255.0);
				lightUpNormal =  rotateAroundX_(reflxDegree,
							       {0, -1, 0});

				reflxDegree = acos(lightDownColor.r / 255.0);
				lightDownNormal = rotateAroundX_(reflxDegree,
								{0, 1, 0});

				reflxDegree = acos(lightLeftColor.r / 255.0);
				lightLeftNormal = rotateAroundY_(reflxDegree,
								{-1, 0, 0});

				reflxDegree = -1 * acos(lightRightColor.r / 255.0);
				lightRightNormal = rotateAroundY_(reflxDegree,
								 {1, 0, 0});

				resultNormal =
					lightUpNormal + lightDownNormal +
					lightLeftNormal + lightRightNormal;
			}

			resultNormal = arma::normalise(resultNormal);
			result.pixel(x, y,
				     ITexture::Color(
					     resultNormal.at(0) * 128.0 + 127.0,
					     resultNormal.at(1) * 128.0 + 127.0,
					     resultNormal.at(2) * 128.0 + 127.0
				     ));
		}
	}

	return ERROR_NO_ERROR;
}

arma::rowvec
ShadeTextureToNormalConverter::rotateAroundX_(double degree, arma::rowvec vec)
{
	arma::mat rotateMatrix = {
		{1, 0, 0},
		{0, cos(degree), -1 * sin(degree)},
		{0, sin(degree), cos(degree)}
	};

	return vec * rotateMatrix.t();
}

arma::rowvec
ShadeTextureToNormalConverter::rotateAroundY_(double degree, arma::rowvec vec)
{
	arma::mat33 rotateMatrix = {
		{cos(degree), 0, sin(degree)},
		{0, 1, 0},
		{-1 * sin(degree), 0, cos(degree)}
	};

	return vec * rotateMatrix.t();
}

