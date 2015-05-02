#include <getopt.h>

#include "error.h"

#include "appOptions.h"

int
AppOptions::parse(int argc, char* argv[])
{
	int opt = 0;

	optind = 0;

	while ((opt = getopt(argc, argv, "hvndo:")) != -1) {
		switch (opt) {
		case 'h':
			shouldPrintHelp_ = true;
			break;
		case 'v':
			shouldPrintVersion_ = true;
			break;
		case 'n':
			if (operation_ != Operations::none)
				return ERROR_MULTI_OPERATION;

			operation_ = Operations::generateNormalMap;
			break;
		case 'd':
			if (operation_ != Operations::none)
				return ERROR_MULTI_OPERATION;

			operation_ = Operations::generateDepthMap;
			break;
		case 'o':
			outputFile_ = optarg;
			break;
		default:
			return ERROR_INVALID_OPTION;
		}
	}

	return 0;
}
