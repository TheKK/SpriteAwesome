#include <cstdio>
#include <Magick++.h>

#include "appOptions.h"
#include "l10n.h"
#include "error.h"

#include "app.h"

namespace
{
	const std::string kDefaultOutName = "result.bmp";
}

int
App::run(int argc, char* argv[])
{
	int ret;

	ret = appOptions_.parse(argc, argv);
	if (ret < 0) {
		if (ret == ERROR_INVALID_OPTION)
			printUsage_();

		fprintf(stderr, "%s\n", getError(ret));

		return -1;
	}

	if (appOptions_.shouldPrintHelp()) {
		printHelp_();
		return 0;
	}
	if (appOptions_.shouldPrintVersion()) {
		printVersion_();
		return 0;
	}

	if (appOptions_.shouldUseDefaultOutputName())
		outputFileName_ = kDefaultOutName;
	else
		outputFileName_ = appOptions_.getOuputFileName();

	switch (appOptions_.getOperation()) {
	case Operations::generateNormalTexture:
		printf("normal texture");
		break;
	case Operations::generateDepthTexture:
		/* TODO implement this */
		printf("depth texture");
		break;
	default:
	case Operations::none:
		printUsage_();
		break;
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
