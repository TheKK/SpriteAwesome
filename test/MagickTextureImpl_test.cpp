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

/* XXX Lots of duplicated code */
TEST(MagickTextureImpl, constructWithNoArgument)
{
	ASSERT_NO_THROW(MagickTextureImpl());
}

TEST(MagickTextureImpl, constructWithStringArgument)
{
	ASSERT_NO_THROW(MagickTextureImpl(kTestImageName));
}

TEST(MagickTextureImpl, construcWithNonexistFilePathArgument)
{
	ASSERT_ANY_THROW(MagickTextureImpl("you can't find me"));
}

TEST(MagickTextureImpl, checkCopyConstructorNoThrowWithNonemptyTexture)
{
	MagickTextureImpl base(kTestImageName);

	ASSERT_NO_THROW(MagickTextureImpl target(base));
}

TEST(MagickTextureImpl, checkCopyConstructorNoThrowWithEmptyTexture)
{
	MagickTextureImpl base;

	ASSERT_NO_THROW(MagickTextureImpl target(base));
}

TEST(MagickTextureImpl, makeEqOperatorTureWithNonemptyTextures)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2(kTestImageName);

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, makeEqOperatorTureWithEmptyTextures)
{
	MagickTextureImpl target1;
	MagickTextureImpl target2;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, makeEqOperatorFalseWithNonemptyTextures)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2(kTestImageName);

	target1.pixel(1, 12, {0x00, 0x11, 0x22});
	target2.pixel(1, 12, {0xcc, 0x11, 0x22});

	bool expected = false;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, makeEqOperatorTrueWithNonemptyTextureAndEmptyTexture)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2;

	bool expected = false;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, checkEqOperatorWithNonemptyTexture)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2(kTestImageName);

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, assignEmptyTextureToNonempty)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2;

	target2 = target1;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, assignEmptyTextureToEmpty)
{
	MagickTextureImpl target1;
	MagickTextureImpl target2;

	target2 = target1;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}

TEST(MagickTextureImpl, assignNonemptyTextureToEmpty)
{
	MagickTextureImpl target1(kTestImageName);
	MagickTextureImpl target2;

	target1 = target2;

	bool expected = true;
	bool actual = (target1 == target2);

	ASSERT_EQ(expected, actual);
}
