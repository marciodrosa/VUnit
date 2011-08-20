#ifndef MATHSAMPLE_ADDICTIONTEST_H
#define MATHSAMPLE_ADDICTIONTEST_H

#include "../../VUnit/include/VUnit.h"

#include "../include/Addiction.h"

using namespace vunit;

class AddictionTest : public TestCase
{
public:
	void testOnePlusOneShouldBeTwo();
	void testOnePlusNegativeTwoShouldBeNegativeOne();
private:
	Addiction addiction;

	VUNIT_TEST_SUITE_BEGIN(AddictionTest)
		VUNIT_TEST_METHOD(testOnePlusOneShouldBeTwo)
		VUNIT_TEST_METHOD(testOnePlusNegativeTwoShouldBeNegativeOne)
	VUNIT_TEST_SUITE_END()
};

#endif
