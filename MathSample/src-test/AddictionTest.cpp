#include "../include-test/AddictionTest.h"

void AddictionTest::testOnePlusOneShouldBeTwo()
{
	// when:
	int result = addiction.calculate(1, 1);

	// then:
	if (result != 2)
	{
		fail("The result is not the expected.");
	}
}

void AddictionTest::testOnePlusNegativeTwoShouldBeNegativeOne()
{
	// when:
	int result = addiction.calculate(1, -2);

	// then:
	if (result != -1)
	{
		fail("The result is not the expected.");
	}
}
