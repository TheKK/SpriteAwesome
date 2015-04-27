#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H
#pragma once

class AppOptions
{
public:
	AppOptions() {};

	int parse(int argc, char* argv[]);

	bool shouldPrintHelp() const { return shouldPrintHelp_; };
	bool shouldPrintVersion() const { return shouldPrintVersion_; };
private:
	bool shouldPrintHelp_ = false;
	bool shouldPrintVersion_ = false;
};

#endif /* APP_OPTIONS_H */

