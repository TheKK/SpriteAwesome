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

	((uint8_t*) target1.pixels())[2] = 0x96;
	((uint8_t*) target2.pixels())[2] = 0x45;

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

TEST(SDLTextureImpl, loadTextureFromFileAndSucess)
{
	SDLTextureImpl target;

	int expected = 0;
	int actual = target.load(kTestImageName);

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, loadTextureFromFileAndFailure)
{
	SDLTextureImpl target;

	int expected = -1;
	int actual = target.load("you can't find me");

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, loadTextureAndCheckIfUsed)
{
	SDLTextureImpl target(kTestImageName);

	bool expected = true;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, loadNothingAndCheckIfUsed)
{
	SDLTextureImpl target;

	bool expected = false;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, getWidth)
{
	SDLTextureImpl target(kTestImageName);

	uint32_t expected = kTestImageWidth;
	uint32_t actual = target.width();

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, getHeight)
{
	SDLTextureImpl target(kTestImageName);

	uint32_t expected = kTestImageHeight;
	uint32_t actual = target.height();

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, getBytePerPixel)
{
	SDLTextureImpl target(kTestImageName);

	uint32_t expected = kTestImageBpp;
	uint32_t actual = target.bpp();

	ASSERT_EQ(expected, actual);
}

TEST(SDLTextureImpl, checkPixelsPtrExistAfterLoaded)
{
	SDLTextureImpl target(kTestImageName);

	void* notExpected = nullptr;
	void* actual = target.pixels();

	ASSERT_NE(notExpected, actual);
}

TEST(SDLTextureImpl, checkPixelDataSotredIsCorrect)
{
	SDLTextureImpl target(kTestImageName);

	int expected = 0;
	int actual = memcmp(target.pixels(), kTestImageData,
			    kTestImageWidth * kTestImageHeight * kTestImageBpp);

	ASSERT_EQ(expected, actual);
}
