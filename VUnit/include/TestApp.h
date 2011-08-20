#ifndef VUNIT_TESTAPP_H
#define VUNIT_TESTAPP_H

#include "VUnitNamespace.h"
#include "TestCase.h"
#include "TestResults.h"

#define VUNIT_APP_BEGIN()										\
int main(int argc, char** argv)									\
{																\
	vunit::TestResults testResults;

#define VUNIT_TEST_CLASS(className)								\
	className::suite(testResults);

#define VUNIT_APP_END()											\
	testResults.finishTests();									\
	return testResults.getFailCount() > 0 ? 1 : 0;				\
}

#endif
