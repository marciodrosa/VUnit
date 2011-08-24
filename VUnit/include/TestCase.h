#ifndef VUNIT_TESTCASE_H
#define VUNIT_TESTCASE_H

#include "VUnitNamespace.h"
#include "TestResults.h"

#include <string>
#include <sstream>

VUNIT_NAMESPACE
{
	/**
	Base class of the tests classes of your project.

	Extend the TestCase, create public void test methods and call the
	assertions functions, like fail or assertEquals.

	Inside the body of the declaration of the class, you must declare
	the call of the tests using the macros VUNIT_TEST_SUITE_BEGIN, VUNIT_TEST_METHOD
	and VUNIT_TEST_SUITE_END.
	*/
	class TestCase
	{
	private:
		bool failed;
		std::string failMessage;

		template<class T>
		std::string getExpectedValueMessage(std::string customMessage, T expected, T actual)
		{
			std::ostringstream messageStream;
			if (customMessage.length() > 0)
			{
				messageStream << customMessage << " - ";
			}
			messageStream << "Expected: <" << expected << "> but was: <" << actual << ">.";

			return messageStream.str();
		}

	public:
		TestCase() : failed(false) {}
		virtual ~TestCase() {}

		/**
		Called before all tests of the class.
		*/
		virtual void beforeClass() {}
		
		/**
		Called after all tests of the class.
		*/
		virtual void afterClass() {}

		/**
		Called before each test of the class.
		*/
		virtual void beforeTest() {}
		
		/**
		Called after each test of the class.
		*/
		virtual void afterTest() {}

		/**
		Causes the test to fail.
		message: the message to be shown
		*/
		void fail(std::string message = "")
		{
			if (!failed)
			{
				failed = true;
				failMessage = message;
			}
		}

		/**
		Tests if the two objects or values are equal. To use with custom classes,	you must
		override the == operator of the class and the << operator of the std::ostream.
		message: the message to be shown if the assertion fails
		expected: the expected value
		actual: the actual value
		*/
		template<class T>
		void assertEquals(std::string message, const T& expected, const T& actual)
		{
			if (!(expected == actual))
			{
				fail(getExpectedValueMessage(message, expected, actual));
			}
		}

		/**
		Tests if the two objects or values are equal. To use with custom classes,	you must
		override the == operator of the class and the << operator of the std::ostream.
		expected: the expected value
		actual: the actual value
		*/
		template<class T>
		void assertEquals(const T& expected, const T& actual)
		{
			assertEquals("", expected, actual);
		}

		/**
		Tests if the two doubles are equal.
		message: the message to be shown if the assertion fails
		expected: the expected value
		actual: the actual value
		delta: a value used to avoid the imprecision of the comparation between two doubles. The actual
		value will be considered equal to the expected if it is between (expected - delta) and (expected + delta).
		*/
		void assertEquals(std::string message, double expected, double actual, double delta)
		{
			double min = expected - delta;
			double max = expected + delta;
			if (actual < min || actual > max)
			{
				fail(getExpectedValueMessage(message, expected, actual));
			}
		}

		/**
		Tests if the two doubles are equal.
		expected: the expected value
		actual: the actual value
		delta: a value used to avoid the imprecision of the comparation between two doubles. The actual
		value will be considered equal to the expected if it is between (expected - delta) and (expected + delta).
		*/
		void assertEquals(double expected, double actual, double delta)
		{
			assertEquals("", expected, actual, delta);
		}

		/**
		Asserts if the value is true.
		*/
		void assertTrue(bool actual)
		{
			assertEquals(true, actual);
		}

		/**
		Asserts if the value is true.
		message: the message to be shown if the assertion fails
		*/
		void assertTrue(std::string message, bool actual)
		{
			assertEquals(message, true, actual);
		}

		/**
		Asserts if the value is false.
		*/
		void assertFalse(bool actual)
		{
			assertEquals(false, actual);
		}

		/**
		Asserts if the value is false.
		message: the message to be shown if the assertion fails
		*/
		void assertFalse(std::string message, bool actual)
		{
			assertEquals(message, false, actual);
		}

		/**
		Returns if some test has failed.
		*/
		bool hasFailed() const
		{
			return failed;
		}

		/**
		Returns the failure message, or an empty string if there is no failures.
		*/
		std::string getFailMessage() const
		{
			return failMessage;
		}
	};
}

#define VUNIT_TEST_SUITE_BEGIN(className)																	\
	public:																									\
		static className* createInstanceForTest()															\
		{																									\
			return new className;																			\
		}																									\
																											\
		static void suite(TestResults& testResults)															\
		{																									\
			std::string classNameStr = #className;															\
			className* test;																				\
			test = createInstanceForTest();																	\
			test->beforeClass();																			\
			testResults.addResult(classNameStr, "beforeClass", !test->hasFailed(), test->getFailMessage());	\
			delete test;

#define VUNIT_TEST_METHOD(methodName)																		\
			test = createInstanceForTest();																	\
			test->beforeTest();																				\
			test->methodName();																				\
			test->afterTest();																				\
			testResults.addResult(classNameStr, #methodName, !test->hasFailed(), test->getFailMessage());	\
			delete test;

#define VUNIT_TEST_SUITE_END()																				\
			test = createInstanceForTest();																	\
			test->afterClass();																				\
			testResults.addResult(classNameStr, "afterClass", !test->hasFailed(), test->getFailMessage());	\
			delete test;																					\
		}

#endif
