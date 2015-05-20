#ifndef TEXTURE_CONVERTOR_H
#define TEXTURE_CONVERTOR_H
#pragma once

#include <type_traits>

#include "texture.h"

namespace TextureConvertor
{

void fromShadeTextureToNormalTexture(ITexture& lightUp,
				     ITexture& lightDown,
				     ITexture& lightLeft,
				     ITexture& lightRight,
				     ITexture& result);

} /* namespace TextureConvertor */

#endif /* TEXTURE_CONVERTOR_H */
