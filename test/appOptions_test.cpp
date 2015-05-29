#include <gtest/gtest.h>
#include <string>

#include "error.h"

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

	int expected = ERROR_NO_ERROR;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseWithUnknowOptions)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-j"
	};

	int expected = ERROR_INVALID_OPTION;
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

TEST(AppOptions, parseNothingToKeepOperationAsNone)
{
	AppOptions target;
	int argc = 1;
	char* argv[] = {
		(char*) "target"
	};

	target.parse(argc, argv);

	Operations expected = Operations::none;
	Operations actual = target.getOperation();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseMultipleOperationToFailed)
{
	AppOptions target;
	int argc = 3;
	char* argv[] = {
		(char*) "target",
		(char*) "-d",
		(char*) "-n"
	};

	int expected = ERROR_MULTI_OPERATION;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSetOperationAsGenerateNormalTexture)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-n"
	};

	target.parse(argc, argv);

	Operations expected = Operations::generateNormalTexture;
	Operations actual = target.getOperation();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSetOperationAsGenerateDepthTexture)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-d"
	};

	target.parse(argc, argv);

	Operations expected = Operations::generateDepthTexture;
	Operations actual = target.getOperation();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseToSetOperationAsGenerateAmbientTexture)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "-a"
	};

	target.parse(argc, argv);

	Operations expected = Operations::generateAmbientTexture;
	Operations actual = target.getOperation();

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseWithLessThanFourInput)
{
	AppOptions target;
	int argc = 2;
	char* argv[] = {
		(char*) "target",
		(char*) "input1"
	};

	int expected = ERROR_NOT_ENOUGH_INPUT;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseWithMoreThanFourInput)
{
	AppOptions target;
	int argc = 6;
	char* argv[] = {
		(char*) "target",
		(char*) "input1",
		(char*) "input2",
		(char*) "input3",
		(char*) "input4",
		(char*) "input5"
	};

	int expected = ERROR_TOO_MUCH_INPUT;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, parseWithExactlyFourInput)
{
	AppOptions target;
	int argc = 5;
	char* argv[] = {
		(char*) "target",
		(char*) "input1",
		(char*) "input2",
		(char*) "input3",
		(char*) "input4"
	};

	int expected = ERROR_NO_ERROR;
	int actual = target.parse(argc, argv);

	ASSERT_EQ(expected, actual);
}

TEST(AppOptions, retrieveFourInputFileName)
{
	AppOptions target;
	int argc = 5;
	char* argv[] = {
		(char*) "target",
		(char*) "input1",
		(char*) "input2",
		(char*) "input3",
		(char*) "input4"
	};

	target.parse(argc, argv);

	std::vector<std::string> expected = {
		target.getInputFileName(ShadeDir::Up),
		target.getInputFileName(ShadeDir::Down),
		target.getInputFileName(ShadeDir::Left),
		target.getInputFileName(ShadeDir::Right)
	};
	std::vector<std::string> actual = {
		argv[1], argv[2], argv[3], argv[4]
	};

	ASSERT_EQ(expected, actual);
}
