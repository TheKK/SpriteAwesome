#include <gtest/gtest.h>
#include <string>

#include "data/lightUp.h"
#include "data/lightDown.h"
#include "data/lightLeft.h"
#include "data/lightRight.h"

#include "textureConvertor.h"

using namespace TextureConvertor;

namespace
{
	const std::string kTestShadeTextureUpName = "test/data/lightUp.png";
	const std::string kTestShadeTextureDownName = "test/data/lightDown.png";
	const std::string kTestShadeTextureLeftName = "test/data/lightLeft.png";
	const std::string kTestShadeTextureRightName =
		"test/data/lightRight.png";

	const uint32_t kTestShadeTextureWidth = lightUp.width;
	const uint32_t kTestShadeTextureHeight = lightUp.height;
	const uint32_t kTestShadeTextureBpp = 3;
}

TEST(fromShadeTextureToNormalTexture, usingSDLTextureImpl)
{
	SDLTextureImpl lightUp(kTestShadeTextureUpName);
	SDLTextureImpl lightDown(kTestShadeTextureDownName);
	SDLTextureImpl lightLeft(kTestShadeTextureLeftName);
	SDLTextureImpl lightRight(kTestShadeTextureRightName);
	SDLTextureImpl result;

	result = fromShadeTextureToNormalTexture(lightUp, lightDown,
						 lightLeft, lightRight);

	bool expected = true;
	bool actual = result.used();

	ASSERT_EQ(expected, actual);
}
