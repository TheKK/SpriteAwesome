#ifndef APP_H
#define APP_H
#pragma once

#include <string>

#include "appOptions.h"

class App
{
public:
	App():
		appOptions_(),
		outputFileName_() {}

	int run(int argc, char* argv[]);
private:
	AppOptions appOptions_;
	std::string outputFileName_;

	void printUsage_();
	void printHelp_();
	void printVersion_();
};

#endif /* APP_H */
