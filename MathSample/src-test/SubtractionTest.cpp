#include "../include-test/SubtractionTest.h"

void SubtractionTest::testOneMinusOneShouldBeZero()
{
	// when:
	int result = subtraction.calculate(1, 1);

	// then:
	if (result != 0)
	{
		fail("The result is not the expected.");
	}
}

void SubtractionTest::testThreeMinusOneShouldBeTwo()
{
	// when:
	int result = subtraction.calculate(3, 1);

	// then:
	if (result != 2)
	{
		fail("The result is not the expected.");
	}
}

void SubtractionTest::testTwoMinusThreeShouldBeNegativeOne()
{
	// when:
	int result = subtraction.calculate(2, 3);

	// then:
	if (result != -1)
	{
		fail("The result is not the expected.");
	}
}
