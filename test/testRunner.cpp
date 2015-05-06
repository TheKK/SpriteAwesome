#include <gtest/gtest.h>
#include <SDL2/SDL_image.h>
#include <Magick++.h>
#include <stdexcept>
#include <cstdlib>

class MyEnvironment : public ::testing::Environment
{
public:
	virtual ~MyEnvironment() {}

	virtual void SetUp()
	{
		srand(time(nullptr));

		if (IMG_Init(IMG_INIT_PNG) < 0)
			throw std::runtime_error(IMG_GetError());

		Magick::InitializeMagick(nullptr);
	}

	virtual void TearDown()
	{
		IMG_Quit();
	}
};

int
main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new MyEnvironment());

	return RUN_ALL_TESTS();
}
