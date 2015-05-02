#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H
#pragma once

#include <string>

enum class Operations {
	none,
	generateNormalTexture,
	generateDepthTexture
};

class AppOptions
{
public:
	AppOptions() {}

	int parse(int argc, char* argv[]);

	bool shouldPrintHelp() const { return shouldPrintHelp_; }
	bool shouldPrintVersion() const { return shouldPrintVersion_; }

	bool shouldUseDefaultOutputName() const { return outputFile_ == ""; }
	const std::string& getOuputFileName() const { return outputFile_; }

	Operations getOperation() const { return operation_; }
private:
	bool shouldPrintHelp_ = false;
	bool shouldPrintVersion_ = false;

	std::string outputFile_ = "";

	Operations operation_ = Operations::none;
};

#endif /* APP_OPTIONS_H */

