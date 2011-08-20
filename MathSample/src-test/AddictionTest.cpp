#include "../include-test/AddictionTest.h"

void AddictionTest::testOnePlusOneShouldBeTwo()
{
	// when:
	int result = addiction.calculate(1, 1);

	// then:
	assertEquals("The result is not the expected.", 2, result);
}

void AddictionTest::testOnePlusNegativeTwoShouldBeNegativeOne()
{
	// when:
	int result = addiction.calculate(1, -2);

	// then:
	assertEquals("The result is not the expected.", -1, result);
}
