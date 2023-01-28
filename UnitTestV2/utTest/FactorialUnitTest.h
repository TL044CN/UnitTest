#pragma once
#include "../src/UnitTest.h"
#include "factorial.h"

class UT_Factorial : public Test::Testable {
public:
	UT_Factorial() : Testable("Factorial Test") {};

protected:
	void run() override {
		EXPECT_EQ(factorial(0), 1);
		EXPECT_EQ(factorial(1), 1);

		EXPECT_EQ(factorial(5), 120);
		EXPECT_EQ(factorial(10), 3628800);

		EXPECT_EXCEPTION(factorial(-1), std::invalid_argument);

		EXPECT_EXCEPTION(factorial(13), std::overflow_error);
	}
};

