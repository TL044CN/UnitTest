#pragma once
#include "../src/UnitTest.h"

class UT_Timing : public Test::Testable {
public:
	UT_Timing() : Testable("Timing Test") {};

protected:
	void run() override {
		for (uint64_t i = 0; i < 10000000000; i++)
			continue;
	}
};
