#include "src/UnitTest.h"
#include "utTest/FactorialUnitTest.h"
#include "utTest/FibonacciUnitTest.h"
#include "utTest/TimingUnitTest.h"

#include <iostream>
#include <fstream>

int main() {

    UT_Factorial FactorialTest;
    UT_Fibonacci FibonacciTest;
    UT_Timing TimingTest;

    Test::TestCollection::runTests();

    Test::TestCollection::report(std::cout, true);

    std::ofstream stream("./UT_report.txt");
    Test::TestCollection::report(stream);
    stream.close();

    return EXIT_SUCCESS;
}