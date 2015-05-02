#ifndef APP_H
#define APP_H
#pragma once

class App
{
public:
	App();

	int run(int argc, char* argv[]);
private:
	void printUsage_();
	void printHelp_();
	void printVersion_();
};

#endif /* APP_H */
