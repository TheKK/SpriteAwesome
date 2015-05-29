#include <gtest/gtest.h>
#include <string>

#include "fakeit.hpp"

#include "textureConvertor.h"

using namespace fakeit;

typedef ITexture::Color Color;

namespace
{
	const uint32_t kTestWidth = 321;
	const uint32_t kTestHeight = 321;
}

typedef testing::Types<ShadeTextureToNormalConverter,
	ShadeTextureToDepthConverter,
	ShadeTextureToAmbientConverter> Impelementations;

TYPED_TEST_CASE(ShadeTextureConverterInterface, Impelementations);

template <typename T>
class ShadeTextureConverterInterface : public testing::Test
{
protected:
	ShadeTextureConverterInterface() : converter_(new T()) {}
	virtual ~ShadeTextureConverterInterface() { delete converter_; }

	ShadeTextureConverter* converter_;
};

/* XXX Kind of useless test */
TYPED_TEST(ShadeTextureConverterInterface, inputLegleShadeTextureThenPass)
{
	ShadeTextureConverter& target = *this->converter_;
	Mock<ITexture> inputMock[5];

	for (int i = 0; i < 5; ++i) {
		When(Method(inputMock[i], used)).AlwaysReturn(true);
		When(Method(inputMock[i], load)).AlwaysReturn(0);
		When(Method(inputMock[i], write)).AlwaysReturn(0);
		When(Method(inputMock[i], width)).AlwaysReturn(kTestWidth);
		When(Method(inputMock[i], height)).AlwaysReturn(kTestHeight);

		When(ConstOverloadedMethod(inputMock[i], pixel,
					   Color(uint32_t, uint32_t))
		).AlwaysReturn(Color(0, 0, 0));

		When(OverloadedMethod(inputMock[i], pixel,
				      void(uint32_t, uint32_t, Color))
		).AlwaysReturn();
	}

	ITexture& lightUp = inputMock[0].get();
	ITexture& lightDown = inputMock[1].get();
	ITexture& lightLeft = inputMock[2].get();
	ITexture& lightRight = inputMock[3].get();
	ITexture& result = inputMock[4].get();

	int expected = 0;
	int actual = target.convert(lightUp, lightDown, lightLeft, lightRight,
				    result);

	ASSERT_EQ(expected, actual);
}
