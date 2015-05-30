#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <Magick++.h>

#include "l10n.h"
#include "app.h"

int
localizationInit()
{
	char* ret;

	ret = setlocale(LC_ALL, "");
	if (!ret)
		return -1;

	ret = bindtextdomain(PROJECT_NAME, PO_DIR);
	if (!ret)
		return -1;

	ret = textdomain(PROJECT_NAME);
	if (!ret)
		return -1;

	return 0;
}

int
systemInit(int argc, char* argv[])
{
	try {
		Magick::InitializeMagick(*argv);
	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
		return -1;
	}

	return 0;
}

int
main(int argc, char* argv[])
{
	App app;

	if (localizationInit() < 0)
		printf("WARN: Failed with localization\n");

	if (systemInit(argc, argv) < 0)
		return EXIT_FAILURE;

	return app.run(argc, argv);
}
