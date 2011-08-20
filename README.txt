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

3) Create the test application, calling the macros VUNIT_APP_BEGIN, VUNIT_TEST_CLASS, VUNIT_APP_END (it will automatically create the main function), like the example:

VUNIT_APP_BEGIN()
	VUNIT_TEST_CLASS(MyTestClass)
	VUNIT_TEST_CLASS(SomeOtherTestClass)
VUNIT_APP_END()


