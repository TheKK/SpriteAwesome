#include <getopt.h>

#include "appOptions.h"

int
AppOptions::parse(int argc, char* argv[])
{
	int opt = 0;

	optind = 0;

	while ((opt = getopt(argc, argv, "hvo:")) != -1) {
		switch (opt) {
		case 'h':
			shouldPrintHelp_ = true;
			break;
		case 'v':
			shouldPrintVersion_ = true;
			break;
		case 'o':
			outputFile_ = optarg;
			break;
		default:
			return -1;
		}
	}

	return 0;
}
