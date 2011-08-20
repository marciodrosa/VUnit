#include "../../VUnit/include/VUnit.h"

#include "../include-test/AddictionTest.h"
#include "../include-test/SubtractionTest.h"

using namespace vunit;

VUNIT_APP_BEGIN()

	VUNIT_TEST_CLASS(AddictionTest)
	VUNIT_TEST_CLASS(SubtractionTest)

VUNIT_APP_END()
