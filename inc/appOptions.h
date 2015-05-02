#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H
#pragma once

#include <string>

class AppOptions
{
public:
	AppOptions() {};

	int parse(int argc, char* argv[]);

	bool shouldPrintHelp() const { return shouldPrintHelp_; };
	bool shouldPrintVersion() const { return shouldPrintVersion_; };

	bool shouldUseDefaultOutputName() const { return outputFile_ == ""; };
	const std::string& getOuputFileName() const { return outputFile_; };
private:
	bool shouldPrintHelp_ = false;
	bool shouldPrintVersion_ = false;
	std::string outputFile_ = "";
};

#endif /* APP_OPTIONS_H */

