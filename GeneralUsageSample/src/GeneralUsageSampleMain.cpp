#include "../../VUnit/include/VUnit.h"

using namespace std;
using namespace vunit;

class SomeTest : public TestCase
{
public:
	void failWithMessage()
	{
		fail("This is the fail message.");
		fail("The second fail is ignored.");
	}

	void success()
	{
	}

	void failWithoutMessage()
	{
		fail();
	}

	VUNIT_TEST_SUITE_BEGIN(SomeTest)
		VUNIT_TEST_METHOD(failWithMessage)
		VUNIT_TEST_METHOD(success)
		VUNIT_TEST_METHOD(failWithoutMessage)
	VUNIT_TEST_SUITE_END()
};

class FailBeforeTest : public TestCase
{
public:
	void beforeTest()
	{
		fail("This test class fail before test.");
	}

	void someTestMethod()
	{
		fail("This fail is ignored because the beforeTest has failed.");
	}

	void afterTest()
	{
		fail("This test class fail after test, but it is ignored because the beforeTest has failed.");
	}

	VUNIT_TEST_SUITE_BEGIN(FailBeforeTest)
		VUNIT_TEST_METHOD(someTestMethod)
	VUNIT_TEST_SUITE_END()
};

class FailAfterTest : public TestCase
{
public:

	void someTestMethod()
	{
	}

	void afterTest()
	{
		fail("This test class fail after test.");
	}

	VUNIT_TEST_SUITE_BEGIN(FailAfterTest)
		VUNIT_TEST_METHOD(someTestMethod)
	VUNIT_TEST_SUITE_END()
};

class ClassFailTest : public TestCase
{
public:

	void beforeClass()
	{
		fail("Fail before class.");
	}

	void someTestMethod()
	{
	}

	void afterClass()
	{
		fail("Fail after class.");
	}

	VUNIT_TEST_SUITE_BEGIN(ClassFailTest)
		VUNIT_TEST_METHOD(someTestMethod)
	VUNIT_TEST_SUITE_END()
};

VUNIT_APP_BEGIN()

	VUNIT_TEST_CLASS(SomeTest)
	VUNIT_TEST_CLASS(FailBeforeTest)
	VUNIT_TEST_CLASS(FailAfterTest)
	VUNIT_TEST_CLASS(ClassFailTest)

VUNIT_APP_END()
