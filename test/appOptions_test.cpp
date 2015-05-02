#include <gtest/gtest.h>
#include <string>

#include "appOptions.h"

TEST(AppOptions, defaultConstructorWithNoArgument)
{
	ASSERT_NO_THROW(AppOptions());
}

TEST(AppOptions, parseWithKnownOptions)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-h"
	};

	int expected = 0;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
	ASSERT_TRUE(target.shouldPrintHelp());
}

TEST(AppOptions, parseWithUnknowOptions)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-j"
	};

	int expected = -1;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSet_ShouldPrintHelp_True)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-h"
	};

	target.parse(argc, argv);

	bool expected = true;
	bool actual = target.shouldPrintHelp();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSet_ShouldPrintVersion_True)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-v"
	};

	target.parse(argc, argv);

	bool expected = true;
	bool actual = target.shouldPrintVersion();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSet_shouldUseDefaultOutputName_True)
{
	AppOptions target;
	int argc = 1;
	char* argv[] = {
		(char*) "target"
	};

	target.parse(argc, argv);

	bool expected = true;
	bool actual = target.shouldUseDefaultOutputName();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSet_shouldUseDefaultOutputName_False)
{
	AppOptions target;
	int argc = 3;
	char* argv[] = {
		(char*) "target",
		(char*) "-o",
		(char*) "haha.bmp"
	};

	target.parse(argc, argv);

	bool expected = false;
	bool actual = target.shouldUseDefaultOutputName();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSet_outputFileName)
{
	AppOptions target;
	int argc = 3;
	char* argv[] = {
		(char*) "target",
		(char*) "-o",
		(char*) "haha.bmp"
	};

	target.parse(argc, argv);

	std::string expected = argv[2];
	std::string actual = target.getOuputFileName();

	ASSERT_EQ(expected, actual);
}
