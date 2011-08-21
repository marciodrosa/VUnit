#ifndef VUNIT_TESTRESULTS_H
#define VUNIT_TESTRESULTS_H

#include "VUnitNamespace.h"

#include <string>
#include <iostream>

VUNIT_NAMESPACE
{
	class TestResults
	{
	private:
		unsigned int passedCount, failCount;

	public:
		TestResults() : passedCount(0), failCount(0) {}
		virtual ~TestResults() {}

		void addResult(std::string className, std::string testName, bool passed, std::string resultMessage)
		{
			if (passedCount + failCount == 0)
			{
				std::cout << std::endl << "> Starting tests..." << std::endl << std::endl;
			}
			if (passed)
			{
				passedCount++;
				std::cout << " >>   Passed : ";
			}
			else
			{
				failCount++;
				std::cout << " >> X FAILED : ";
			}

			std::cout << className << " : " << testName;
	
			if (!passed)
			{
				std::cout << " : " << resultMessage;
			}

			std::cout << std::endl;
		}

		void finishTests()
		{
			std::cout << std::endl << "> " << (passedCount + failCount) << " tests executed; " << std::endl;
			std::cout << "> " << passedCount << " tests passed; " << std::endl;
			std::cout << "> " << failCount << " tests failed; " << std::endl << std::endl;
		}

		unsigned int getFailCount() const
		{
			return failCount;
		}
	};
}

#endif
