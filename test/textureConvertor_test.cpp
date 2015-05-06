#include <gtest/gtest.h>
#include <string>

#include "fakeit.hpp"

#include "textureConvertor.h"

using namespace TextureConvertor;
using namespace fakeit;

typedef ITexture::Color Color;

namespace
{
	const uint32_t kTestWidth = 321;
	const uint32_t kTestHeight = 321;
}

/* XXX Kind of useless test */
TEST(TextureConvertors, fromShadeTextureToNormalTexture)
{
	Mock<ITexture> inputMock[5];

	for (int i = 0; i < 5; ++i) {
		When(Method(inputMock[i], width)).Return(kTestWidth);
		When(Method(inputMock[i], height)).Return(kTestHeight);
		When(Method(inputMock[i], used)).Return(true);
		When(Method(inputMock[i], load)).Return(0);
		When(ConstOverloadedMethod(inputMock[i], pixel,
					   Color(uint32_t,
						 uint32_t))).Return(Color());
	}

	ITexture& lightUp = inputMock[0].get();
	ITexture& lightDown = inputMock[1].get();
	ITexture& lightLeft = inputMock[2].get();
	ITexture& lightRight = inputMock[3].get();
	ITexture& result = inputMock[4].get();

	ASSERT_NO_THROW(
		fromShadeTextureToNormalTexture(lightUp, lightDown,
						lightLeft, lightRight,
						result)
	);
}
