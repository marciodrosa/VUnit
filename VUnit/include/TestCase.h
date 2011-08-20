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

		void fail()
		{
			failed = true;
		}

		void fail(std::string message)
		{
			if (!failed)
			{
				failed = true;
				failMessage = message;
			}
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
