#include <gtest/gtest.h>

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
