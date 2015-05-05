#include <cstdio>
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
	Magick::InitializeMagick(*argv);

	return 0;
}

int
main(int argc, char* argv[])
{
	if (localizationInit() < 0)
		printf("WARN: Failed with localization\n");

	if (systemInit(argc, argv) < 0)
		return 1;

	try {
		App app;

		app.run(argc, argv);

	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
		return 1;
	}

	return 0;
}
