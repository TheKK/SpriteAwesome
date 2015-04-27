#ifndef TEXTURE_CONVERTOR_H
#define TEXTURE_CONVERTOR_H
#pragma once

#include <type_traits>

#include "texture.h"

namespace TextureConvertor
{
	template<typename T>
	T fromShadeTexturetoNormalTexture(T& lightUp, T& lightDown,
					  T& lightLeft, T& lightRight)
	{
		static_assert(std::is_base_of<ITexture, T>::value,
			      "typename T is not a derived of ITexture");

		/* TODO Implement this function */
		return T(lightUp);
	}
} /* namespace TextureConvertor */

#endif /* TEXTURE_CONVERTOR_H */
