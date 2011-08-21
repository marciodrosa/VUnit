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
		Asserts if the two objects or values are equal. To use with custom classes,	you must
		override the == operator of the class and the << operator of the std::ostream.
		expected: the expected value
		actual: the actual value
		message: the message to be shown if the assertion fails
		*/
		template<class T>
		void assertEquals(std::string message, const T& expected, const T& actual)
		{
			if (!(expected == actual))
			{
				std::ostringstream messageStream;
				if (message.length() > 0)
				{
					messageStream << message << " - ";
				}
				messageStream << "Expected: <" << expected << "> but was: <" << actual << ">.";
				fail(messageStream.str());
			}
		}

		/**
		Asserts if the two objects or values are equal. To use with custom classes,	you must
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
