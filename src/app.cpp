#include <cstdio>
#include <memory>

#include "error.h"
#include "l10n.h"
#include "texture.h"
#include "textureConverterFactory.h"

#include "app.h"

namespace
{
	const std::string kDefaultOutName = "result.bmp";
}

int
App::run(int argc, char* argv[])
{
	int ret;
	std::unique_ptr<ShadeTextureConverter> converter;

	ret = appOptions_.parse(argc, argv);
	if (ret) {
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

	converter.reset(TextureConverterFactory::make(
			appOptions_.getOperation()));
	if (!converter)
		printUsage_();
	else
		processShadeTexture_(*converter);

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

int
App::processShadeTexture_(ShadeTextureConverter& converter)
{
	int ret = 0;
	MagickTextureImpl lightUp, lightDown, lightLeft, lightRight, result;

	ret = lightUp.load(appOptions_.getInputFileName(ShadeDir::Up));
	if (ret) {
		fprintf(stderr, "%s\n", getError(ret));
		return -1;
	}

	ret = lightDown.load(appOptions_.getInputFileName(ShadeDir::Down));
	if (ret) {
		fprintf(stderr, "%s\n", getError(ret));
		return -1;
	}

	ret = lightLeft.load(appOptions_.getInputFileName(ShadeDir::Left));
	if (ret) {
		fprintf(stderr, "%s\n", getError(ret));
		return -1;
	}

	ret = lightRight.load(appOptions_.getInputFileName(ShadeDir::Right));
	if (ret) {
		fprintf(stderr, "%s\n", getError(ret));
		return -1;
	}

	/* XXX Need a method to create empty texture */
	ret = result.load(appOptions_.getInputFileName(ShadeDir::Up));
	if (ret) {
		fprintf(stderr, "%s\n", getError(ret));
		return -1;
	}

	ret = converter.convert(lightUp, lightDown, lightLeft, lightRight,
				result);
	if (ret)
		return -1;

	result.write(outputFileName_);

	return 0;
}
