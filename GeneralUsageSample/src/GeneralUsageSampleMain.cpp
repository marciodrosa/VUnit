#include "../../VUnit/include/VUnit.h"

#include <string>

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

class SampleClass
{
	friend ostream& operator<<(ostream& output, const SampleClass& sampleClass);
	int id;
public:
	SampleClass(int id)
	{
		this->id = id;
	}

	bool operator==(const SampleClass& other) const
	{
		return this->id == other.id;
	}

	
};

ostream& operator<<(ostream& output, const SampleClass& sampleClass)
{
	return output << "Sample class with ID " << sampleClass.id;
}

class AssertEqualsTest : public TestCase
{
public:

	void assertEqualsShouldValidateEqualValues()
	{
		assertEquals("The expected and the actual values are equal.", 1, 1);
	}
	
	void assertEqualsShouldNotValidateNotEqualValues()
	{
		assertEquals("The expected and the actual values are NOT equal, the failure is expected.", 1, 2);
	}

	void assertEqualsShouldValidateObjects()
	{
		string someString = "abc";
		string otherString = "abc";
		assertEquals("The expected and the actual values are equal.", someString, otherString);
	}

	void assertEqualsShouldValidateInstancesOfCustomClasses()
	{
		SampleClass object(1);
		SampleClass* pointerToObject = new SampleClass(1);
		const SampleClass constObject(2);

		assertEquals("The expected and the actual objects are equal.", object, *pointerToObject);
		assertEquals("The expected and the actual objects are NOT equal, failure expected.", object, constObject);

		delete pointerToObject;
	}

	VUNIT_TEST_SUITE_BEGIN(AssertEqualsTest)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateEqualValues)
		VUNIT_TEST_METHOD(assertEqualsShouldNotValidateNotEqualValues)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateObjects)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateInstancesOfCustomClasses)
	VUNIT_TEST_SUITE_END()
};

class AssertTrueAndFalseTest : public TestCase
{
public:
	void assertTrueShouldValidateWithTrueValue()
	{
		assertTrue(true);
	}

	void assertTrueShouldNotValidateWithFalseValue()
	{
		assertTrue(false);
	}

	void assertFalseShouldValidateWithFalseValue()
	{
		assertFalse(false);
	}

	void assertFalseShouldNotValidateWithTrueValue()
	{
		assertFalse(true);
	}

	VUNIT_TEST_SUITE_BEGIN(AssertTrueAndFalseTest)
		VUNIT_TEST_METHOD(assertTrueShouldValidateWithTrueValue)
		VUNIT_TEST_METHOD(assertTrueShouldNotValidateWithFalseValue)
		VUNIT_TEST_METHOD(assertFalseShouldValidateWithFalseValue)
		VUNIT_TEST_METHOD(assertFalseShouldNotValidateWithTrueValue)
	VUNIT_TEST_SUITE_END()
};

VUNIT_APP_BEGIN()

	VUNIT_TEST_CLASS(SomeTest)
	VUNIT_TEST_CLASS(FailBeforeTest)
	VUNIT_TEST_CLASS(FailAfterTest)
	VUNIT_TEST_CLASS(ClassFailTest)
	VUNIT_TEST_CLASS(AssertEqualsTest)
	VUNIT_TEST_CLASS(AssertTrueAndFalseTest)

VUNIT_APP_END()
