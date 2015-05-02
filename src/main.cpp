#include <cstdio>
#include <stdexcept>

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
main(int argc, char* argv[])
{
	if (localizationInit() < 0)
		printf("WARN: Failed with localization\n");

	App app;

	return app.run(argc, argv);
}
