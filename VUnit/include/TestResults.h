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
				std::cerr << std::endl << "> Starting tests..." << std::endl << std::endl;
			}
			if (passed)
			{
				passedCount++;
				std::cerr << " >>   Passed : ";
			}
			else
			{
				failCount++;
				std::cerr << " >> X FAILED : ";
			}

			std::cerr << className << " : " << testName;
	
			if (!passed)
			{
				std::cerr << " : " << resultMessage;
			}

			std::cerr << std::endl;
		}

		void finishTests()
		{
			std::cerr << std::endl << "> " << (passedCount + failCount) << " tests executed; " << std::endl;
			std::cerr << "> " << passedCount << " tests passed; " << std::endl;
			std::cerr << "> " << failCount << " tests failed; " << std::endl << std::endl;
		}

		unsigned int getFailCount() const
		{
			return failCount;
		}
	};
}

#endif
