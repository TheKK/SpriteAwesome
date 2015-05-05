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

	const uint8_t* kTestImageData = imageForTest.pixel_data;
}

typedef testing::Types<SDLTextureImpl, MagickTextureImpl> Impelementations;

TYPED_TEST_CASE(ITextureInterface, Impelementations);

template <typename T>
class ITextureInterface : public testing::Test
{
protected:
	ITextureInterface() : texture_(new T()) {}
	virtual ~ITextureInterface() { delete texture_; }

	ITexture* texture_;
};

TYPED_TEST(ITextureInterface, loadTextureFromFileAndSucess)
{
	ITexture& target = *this->texture_;

	int expected = 0;
	int actual = target.load(kTestImageName);

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, loadTextureFromFileAndFailure)
{
	ITexture& target = *this->texture_;

	int expected = -1;
	int actual = target.load("you can't find me");

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, loadTextureAndCheckIfUsed)
{
	ITexture& target = *this->texture_;

	target.load(kTestImageName);

	bool expected = true;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, loadNothingAndCheckIfUsed)
{
	ITexture& target = *this->texture_;

	bool expected = false;
	bool actual = target.used();

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, getWidth)
{
	ITexture& target = *this->texture_;

	target.load(kTestImageName);

	uint32_t expected = kTestImageWidth;
	uint32_t actual = target.width();

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, getHeight)
{
	ITexture& target = *this->texture_;

	target.load(kTestImageName);

	uint32_t expected = kTestImageHeight;
	uint32_t actual = target.height();

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, getPixelColor)
{
	ITexture& target = *this->texture_;

	target.load(kTestImageName);

	int x = 1, y = 23;
	int offset = (y * kTestImageWidth + x);

	ITexture::Color expected = ((ITexture::Color*) kTestImageData)[offset];
	ITexture::Color actual = target.pixel(x, y);

	ASSERT_EQ(expected, actual);
}

TYPED_TEST(ITextureInterface, setPixelColor)
{
	ITexture& target = *this->texture_;

	target.load(kTestImageName);

	int x = 1, y = 23;
	ITexture::Color colorChangeTo(0x00, 0x33, 0x77);
	target.pixel(x, y, colorChangeTo);

	ITexture::Color& expected = colorChangeTo;
	ITexture::Color actual = target.pixel(x, y);

	ASSERT_EQ(expected, actual);
}
