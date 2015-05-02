#include <getopt.h>
#include <cstdio>

#include "appOptions.h"
#include "l10n.h"

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
	if (ret < 0) {
		printUsage_();
		return ret;
	}

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
App::printUsage_()
{
	printf(_("SpriteAwesome Usage: [-v version] [-h help]\n"));
}
void
App::printHelp_()
{
	printf(_("help won't help you\n"));
}

void
App::printVersion_()
{
	printf(_("SpriteAwesome V0.0\n"));
}
