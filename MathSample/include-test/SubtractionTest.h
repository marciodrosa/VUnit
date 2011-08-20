#ifndef MATHSAMPLE_SUBTRACTIONTEST_H
#define MATHSAMPLE_SUBTRACTIONTEST_H

#include "../../VUnit/include/VUnit.h"

#include "../include/Subtraction.h"

using namespace vunit;

class SubtractionTest : public TestCase
{
public:
	void testOneMinusOneShouldBeZero();
	void testThreeMinusOneShouldBeTwo();
	void testTwoMinusThreeShouldBeNegativeOne();
private:
	Subtraction subtraction;

	VUNIT_TEST_SUITE_BEGIN(SubtractionTest)
		VUNIT_TEST_METHOD(testOneMinusOneShouldBeZero)
		VUNIT_TEST_METHOD(testThreeMinusOneShouldBeTwo)
		VUNIT_TEST_METHOD(testTwoMinusThreeShouldBeNegativeOne)
	VUNIT_TEST_SUITE_END()
};

#endif
