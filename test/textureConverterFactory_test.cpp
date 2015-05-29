#include <gtest/gtest.h>
#include <typeinfo>
#include <typeindex>
#include <memory>

#include "textureConverterFactory.h"

TEST(TextureConverterFactory, requestNoneOfExistConverter)
{
	std::unique_ptr<ShadeTextureConverter> target(
		TextureConverterFactory::make(Operations::none));

	ShadeTextureConverter* expected = nullptr;
	ShadeTextureConverter* actual = target.get();

	ASSERT_EQ(expected, actual);
}

TEST(TextureConverterFactory, requestNormalTextureConverter)
{
	std::unique_ptr<ShadeTextureConverter> target(
		TextureConverterFactory::make(Operations::generateNormalTexture));

	std::type_index expected = typeid(ShadeTextureToNormalConverter);
	std::type_index actual = typeid(*target);

	ASSERT_EQ(expected, actual);
}

TEST(TextureConverterFactory, requestDepthTextureConverter)
{
	std::unique_ptr<ShadeTextureConverter> target(
		TextureConverterFactory::make(Operations::generateDepthTexture));

	std::type_index expected = typeid(ShadeTextureToDepthConverter);
	std::type_index actual = typeid(*target);

	ASSERT_EQ(expected, actual);
}

TEST(TextureConverterFactory, requestAmbientTextureConverter)
{
	std::unique_ptr<ShadeTextureConverter> target(
		TextureConverterFactory::make(Operations::generateAmbientTexture));

	std::type_index expected = typeid(ShadeTextureToAmbientConverter);
	std::type_index actual = typeid(*target);

	ASSERT_EQ(expected, actual);
}
