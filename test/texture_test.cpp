#include <gtest/gtest.h>

#include "texture.h"

TEST(Texture, constructWithNoArgument)
{
	ASSERT_NO_THROW(Texture());
}

TEST(Texture, construcWithExistFilePathArgument)
{
	ASSERT_NO_THROW(Texture("imageForTest.bmp"));
}

TEST(Texture, construcWithNonexistFilePathArgument)
{
	ASSERT_ANY_THROW(Texture("you can't find me"));
}

TEST(Texture, getWidth)
{
	Texture target("imageForTest.bmp");

	uint32_t expected = 123;
	uint32_t actual = target.width();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getHeight)
{
	Texture target("imageForTest.bmp");

	uint32_t expected = 123;
	uint32_t actual = target.height();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getBytePerPixel)
{
	Texture target("imageForTest.bmp");

	uint32_t expected = 4;
	uint32_t actual = target.bpp();

	ASSERT_EQ(expected, actual);
}
