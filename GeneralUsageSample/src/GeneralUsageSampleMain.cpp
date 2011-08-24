#include "../../VUnit/include/VUnit.h"

#include <string>

using namespace std;
using namespace vunit;

/**
This is just a class used in this sample to demonstrate the tests involving the assertEquals method.
*/
class SampleClass
{
	friend ostream& operator<<(ostream& output, const SampleClass& sampleClass);
	int id;
public:
	/**
	Constructor.
	*/
	SampleClass(int id)
	{
		this->id = id;
	}

	/**
	Returns true if the id of this object and the other object are the same value.
	*/
	bool operator==(const SampleClass& other) const
	{
		return this->id == other.id;
	}
};

/**
Overloads the << operator of the ostream class to write the SampleClass description into the stream.
*/
ostream& operator<<(ostream& output, const SampleClass& sampleClass)
{
	return output << "Sample class with ID " << sampleClass.id;
}

class GeneralUsageTest : public TestCase
{
public:

	void noAssertion()
	{
	}

	void failWithMessage()
	{
		fail("This test fails and show this message.");
		fail("The second fail message is ignored.");
	}

	void failWithoutMessage()
	{
		fail();
	}

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
	
	void assertEqualsShouldValidateEqualValues()
	{
		assertEquals("The expected and the actual values are equal, this message will not be shown.", 1, 1);
	}
	
	void assertEqualsShouldNotValidateNotEqualValues()
	{
		assertEquals("The expected and the actual values are NOT equal, the failure is expected.", 1, 2);
	}

	void assertEqualsShouldValidateObjects()
	{
		string someString = "abc";
		string otherString = "abc";
		assertEquals("The expected and the actual values are equal, this message will not be shown.", someString, otherString);
	}

	void assertEqualsShouldNotValidateDifferentInstancesOfCustomClasses()
	{
		SampleClass object(1);
		SampleClass* pointerToObject = new SampleClass(1);
		const SampleClass constObject(2);

		assertEquals("The expected and the actual objects are equal, this message will not be shown.", object, *pointerToObject);
		assertEquals("The expected and the actual objects are NOT equal, failure expected.", object, constObject);

		delete pointerToObject;
	}

	void assertEqualsShouldValidateDoublesPrecisely()
	{
		double value = 1.5;
		double equalValue = 1.5001;
		assertEquals("The expected and the actual values are precisaly equal, this message will not be shown.", value, equalValue, 0.001);
	}

	void assertEqualsShouldNotValidateDifferentDoublesPrecisely()
	{
		double value = 1.5;
		double equalValue = 1.51;
		assertEquals("The expected and the actual values are NOT equal, failure expected.", value, equalValue, 0.001);
	}

	VUNIT_TEST_SUITE_BEGIN(GeneralUsageTest)
		VUNIT_TEST_METHOD(noAssertion)
		VUNIT_TEST_METHOD(failWithMessage)
		VUNIT_TEST_METHOD(failWithoutMessage)
		VUNIT_TEST_METHOD(assertTrueShouldValidateWithTrueValue)
		VUNIT_TEST_METHOD(assertTrueShouldNotValidateWithFalseValue)
		VUNIT_TEST_METHOD(assertFalseShouldValidateWithFalseValue)
		VUNIT_TEST_METHOD(assertFalseShouldNotValidateWithTrueValue)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateEqualValues)
		VUNIT_TEST_METHOD(assertEqualsShouldNotValidateNotEqualValues)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateObjects)
		VUNIT_TEST_METHOD(assertEqualsShouldNotValidateDifferentInstancesOfCustomClasses)
		VUNIT_TEST_METHOD(assertEqualsShouldValidateDoublesPrecisely)
		VUNIT_TEST_METHOD(assertEqualsShouldNotValidateDifferentDoublesPrecisely)
	VUNIT_TEST_SUITE_END()
};

class FailBeforeTest : public TestCase
{
public:
	void beforeTest()
	{
		fail("This test class fails before each test.");
	}

	void someTestMethod()
	{
		fail("This fail is ignored because the beforeTest has failed.");
	}

	void otherTestMethod()
	{
	}

	void afterTest()
	{
		fail("This test class fails after each test, but it is ignored because the beforeTest has failed.");
	}

	VUNIT_TEST_SUITE_BEGIN(FailBeforeTest)
		VUNIT_TEST_METHOD(someTestMethod)
		VUNIT_TEST_METHOD(otherTestMethod)
	VUNIT_TEST_SUITE_END()
};

class FailAfterTest : public TestCase
{
public:

	void someTestMethod()
	{
	}

	void otherTestMethod()
	{
	}

	void afterTest()
	{
		fail("This test class fails after each test.");
	}

	VUNIT_TEST_SUITE_BEGIN(FailAfterTest)
		VUNIT_TEST_METHOD(someTestMethod)
		VUNIT_TEST_METHOD(otherTestMethod)
	VUNIT_TEST_SUITE_END()
};

class ClassFailTest : public TestCase
{
public:

	void beforeClass()
	{
		fail("This class fails before the first test.");
	}

	void someTestMethod()
	{
	}

	void otherTestMethod()
	{
	}

	void afterClass()
	{
		fail("This class fails after the last test.");
	}

	VUNIT_TEST_SUITE_BEGIN(ClassFailTest)
		VUNIT_TEST_METHOD(someTestMethod)
		VUNIT_TEST_METHOD(otherTestMethod)
	VUNIT_TEST_SUITE_END()
};

VUNIT_APP_BEGIN()

	VUNIT_TEST_CLASS(GeneralUsageTest)
	VUNIT_TEST_CLASS(FailBeforeTest)
	VUNIT_TEST_CLASS(FailAfterTest)
	VUNIT_TEST_CLASS(ClassFailTest)

VUNIT_APP_END()
