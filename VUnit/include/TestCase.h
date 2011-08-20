#ifndef VUNIT_TESTCASE_H
#define VUNIT_TESTCASE_H

#include "VUnitNamespace.h"
#include "TestResults.h"

#include <string>
#include <sstream>

VUNIT_NAMESPACE
{
	class TestCase
	{
	private:
		bool failed;
		std::string failMessage;

	public:
		TestCase() : failed(false) {}
		virtual ~TestCase() {}

		virtual void beforeClass() {}
		virtual void afterClass() {}

		virtual void beforeTest() {}
		virtual void afterTest() {}

		void fail(std::string message = "")
		{
			if (!failed)
			{
				failed = true;
				failMessage = message;
			}
		}

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

		template<class T>
		void assertEquals(const T& expected, const T& actual)
		{
			assertEquals("", expected, actual);
		}

		bool hasFailed() const
		{
			return failed;
		}

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
