#include "../include-test/SubtractionTest.h"

void SubtractionTest::testOneMinusOneShouldBeZero()
{
	// when:
	int result = subtraction.calculate(1, 1);

	// then:
	assertEquals("The result is not the expected.", 0, result);
}

void SubtractionTest::testThreeMinusOneShouldBeTwo()
{
	// when:
	int result = subtraction.calculate(3, 1);

	// then:
	assertEquals("The result is not the expected.", 2, result);
}

void SubtractionTest::testTwoMinusThreeShouldBeNegativeOne()
{
	// when:
	int result = subtraction.calculate(2, 3);

	// then:
	assertEquals("The result is not the expected.", -1, result);
}
