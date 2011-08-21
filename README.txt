=============================================================================

VUNIT is a simple unit test tool for C++.

=============================================================================

PROJECT STRUCTURE:

VUnit is a header-only library, so it doesn't need to be compiled. All files are header files (.h). Only the samples projects needs to be compiled, because those contains .cpp files.

The package contains a solution for Visual Studio, with the VUnit project (the .h files) and other sample files.

=============================================================================

USAGE:

1) Include the VUnit.h and use the namespace vunit::

2) Create a test class:
- create a class with the test methods (simple public methods without parameters)
- the class must extends the TestCase class
- inside the body of the class, call the macros VUNIT_TEST_SUITE_BEGIN, VUNIT_TEST_METHOD and VUNIT_TEST_SUITE_END, like the example:

class MyTestClass : public TestCase
{
public:
	void myTestMethod();
	void myOtherTestMethod();
	
	VUNIT_TEST_SUITE_BEGIN(MyTestClass)
		VUNIT_TEST_METHOD(myTestMethod)
		VUNIT_TEST_METHOD(myOtherTestMethod)
	VUNIT_TEST_SUITE_END()
};

3) Inside the test methods, you can call the following methods to assert:
- fail()
- assertEquals(expected, actual) (warning: to use with custom classes, you must override the == operator of the class and the << operator of the std::ostream)
(those methods can be also called with an optional std::string as first parameter to be used as failure message)

4) You can also overrides the following methods of the TestCase class: beforeClass, beforeTest, afterTest and afterClass.

5) Create the test application, calling the macros VUNIT_APP_BEGIN, VUNIT_TEST_CLASS, VUNIT_APP_END (it will automatically create the main function), like the example:

VUNIT_APP_BEGIN()
	VUNIT_TEST_CLASS(MyTestClass)
	VUNIT_TEST_CLASS(SomeOtherTestClass)
VUNIT_APP_END()

6) The results will be written in the default cout object.

