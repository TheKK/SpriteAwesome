#include <getopt.h>

#include "error.h"

#include "appOptions.h"

int
AppOptions::parse(int argc, char* argv[])
{
	int opt = 0;

	optind = 0;

	while ((opt = getopt(argc, argv, "hvndao:")) != -1) {
		switch (opt) {
		case 'h':
			shouldPrintHelp_ = true;
			return 0;
		case 'v':
			shouldPrintVersion_ = true;
			return 0;
		case 'n':
			if (operation_ != Operations::none)
				return ERROR_MULTI_OPERATION;

			operation_ = Operations::generateNormalTexture;
			break;
		case 'd':
			if (operation_ != Operations::none)
				return ERROR_MULTI_OPERATION;

			operation_ = Operations::generateDepthTexture;
			break;
		case 'a':
			if (operation_ != Operations::none)
				return ERROR_MULTI_OPERATION;

			operation_ = Operations::generateAmbientTexture;
			break;
		case 'o':
			outputFile_ = optarg;
			break;
		default:
			return ERROR_INVALID_OPTION;
		}
	}

	while (optind < argc) {
		inputFiles_.push_back(argv[optind]);
		optind++;
	}

	if (inputFiles_.size() < 4)
		return ERROR_NOT_ENOUGH_INPUT;
	else if (inputFiles_.size() > 4)
		return ERROR_TOO_MUCH_INPUT;

	return 0;
}
