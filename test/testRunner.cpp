#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

class MyEnvironment : public ::testing::Environment
{
public:
	virtual ~MyEnvironment() {}

	virtual void SetUp()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			throw std::runtime_error(SDL_GetError());

		if (IMG_Init(IMG_INIT_PNG) < 0)
			throw std::runtime_error(IMG_GetError());
	}

	virtual void TearDown()
	{
		SDL_Quit();
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
