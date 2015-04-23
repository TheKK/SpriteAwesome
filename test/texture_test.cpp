#include <gtest/gtest.h>
#include <string>

#include "texture.h"

namespace
{
	const std::string kTestImageName = "test/data/imageForTest.png";
}

TEST(Texture, constructWithNoArgument)
{
	ASSERT_NO_THROW(Texture());
}

TEST(Texture, constructWithStringArgument)
{
	ASSERT_NO_THROW(Texture(kTestImageName));
}

TEST(Texture, construcWithNonexistFilePathArgument)
{
	ASSERT_ANY_THROW(Texture("you can't find me"));
}

TEST(Texture, loadTextureFromFileAndSucess)
{
	Texture target;

	int expected = 0;
	int actual = target.load(kTestImageName);

	ASSERT_EQ(expected, actual);
}

TEST(Texture, loadTextureFromFileAndFailure)
{
	Texture target;

	int expected = -1;
	int actual = target.load("you can't find me");

	ASSERT_EQ(expected, actual);
}

TEST(Texture, loadTextureAndCheckIfUsed)
{
	Texture target(kTestImageName);

	bool expected = true;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, loadNothingAndCheckIfUsed)
{
	Texture target;

	bool expected = false;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getWidth)
{
	Texture target(kTestImageName);

	uint32_t expected = 123;
	uint32_t actual = target.width();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getHeight)
{
	Texture target(kTestImageName);

	uint32_t expected = 123;
	uint32_t actual = target.height();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getBytePerPixel)
{
	Texture target(kTestImageName);

	uint32_t expected = 3;
	uint32_t actual = target.bpp();

	ASSERT_EQ(expected, actual);
}

TEST(Texture, getPixelsPtr)
{
	Texture target(kTestImageName);

	void* notExpected = nullptr;
	void* actual = target.pixels();

	ASSERT_NE(notExpected, actual);
}
