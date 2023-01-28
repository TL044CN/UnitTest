#pragma once
#include "../src/UnitTest.h"
#include "fibonacci.h"

class UT_Fibonacci : public Test::Testable {
public:
	UT_Fibonacci() : Testable("Fibonacci Test") {};

protected:
	void run() override {
		EXPECT_EQ(fibonacci(0), 0);
		EXPECT_EQ(fibonacci(1), 1);

		EXPECT_EQ(fibonacci(10), 55);

		EXPECT_EXCEPTION(fibonacci(-1), std::invalid_argument);
	}

};

