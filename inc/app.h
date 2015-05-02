#ifndef APP_H
#define APP_H
#pragma once

#include <string>

class App
{
public:
	App();

	int run(int argc, char* argv[]);
private:
	std::string outputFileName_;

	void printUsage_();
	void printHelp_();
	void printVersion_();
};

#endif /* APP_H */
