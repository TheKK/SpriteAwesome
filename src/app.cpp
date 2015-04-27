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

	if ((ret = appOptions.parse(argc, argv)))
		return ret;

	if (appOptions.shouldPrintHelp())
		printf("help won't help you\n");
	if (appOptions.shouldPrintVersion())
		printf("SpriteAwesome V0.0\n");

	return 0;
}
