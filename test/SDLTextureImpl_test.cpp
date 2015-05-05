#include <gtest/gtest.h>
#include <string>
#include <cstring>

#include "data/imageForTest.h"

#include "texture.h"

namespace
{
	const std::string kTestImageName = "test/data/imageForTest.png";

	const uint32_t kTestImageWidth = imageForTest.width;
	const uint32_t kTestImageHeight = imageForTest.height;
	const uint32_t kTestImageBpp = imageForTest.bytes_per_pixel;

	const void* kTestImageData = imageForTest.pixel_data;
}

TEST(SDLTextureImpl, constructWithNoArgument)
{
	ASSERT_NO_THROW(SDLTextureImpl());
}

TEST(SDLTextureImpl, constructWithStringArgument)
{
	ASSERT_NO_THROW(SDLTextureImpl(kTestImageName));
}

TEST(SDLTextureImpl, construcWithNonexistFilePathArgument)
{
	ASSERT_ANY_THROW(SDLTextureImpl("you can't find me"));
}

TEST(SDLTextureImpl, checkCopyConstructorNoThrowWithNonemptyTexture)
{
	SDLTextureImpl base(kTestImageName);

	ASSERT_NO_THROW(SDLTextureImpl target(base));
}

TEST(SDLTextureImpl, checkCopyConstructorNoThrowWithEmptyTexture)
{
	SDLTextureImpl base;

	ASSERT_NO_THROW(SDLTextureImpl target(base));
}

TEST(SDLTextureImpl, makeEqOperatorTureWithNonemptyTextures)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2(kTestImageName);

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, makeEqOperatorTureWithEmptyTextures)
{
	SDLTextureImpl target1;
	SDLTextureImpl target2;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, makeEqOperatorFalseWithNonemptyTextures)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2(kTestImageName);

	target1.pixel(1, 12, {0x00, 0x11, 0x22});
	target2.pixel(1, 12, {0xcc, 0x11, 0x22});

	bool expected = false;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, makeEqOperatorTrueWithNonemptyTextureAndEmptyTexture)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2;

	bool expected = false;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, checkEqOperatorWithNonemptyTexture)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2(kTestImageName);

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, assignEmptyTextureToNonempty)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2;

	target2 = target1;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, assignEmptyTextureToEmpty)
{
	SDLTextureImpl target1;
	SDLTextureImpl target2;

	target2 = target1;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, assignNonemptyTextureToEmpty)
{
	SDLTextureImpl target1(kTestImageName);
	SDLTextureImpl target2;

	target1 = target2;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}
