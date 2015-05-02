#include <getopt.h>
#include <cstdio>

#include "appOptions.h"

#include "app.h"

App::App()
{
}

int
App::run(int argc, char* argv[])
{
	AppOptions appOptions;
	int ret;

	ret = appOptions.parse(argc, argv);
	if (ret < 0)
		return ret;

	if (appOptions.shouldPrintHelp()) {
		printHelp_();
		return 0;
	}
	if (appOptions.shouldPrintVersion()) {
		printVersion_();
		return 0;
	}

	return 0;
}

void
App::printHelp_()
{
	printf("help won't help you\n");
}

void
App::printVersion_()
{
	printf("SpriteAwesome V0.0\n");
}
