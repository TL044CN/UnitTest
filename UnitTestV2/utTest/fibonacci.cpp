#include "fibonacci.h"

int64_t fibonacci(int64_t zahl) {
    if(zahl < 0) throw std::invalid_argument("Negatives Argument ist unzulässig");
    if(zahl == 0) return 0;
    else if(zahl == 1) return 1;
    return fibonacci(zahl - 1) + fibonacci(zahl - 2);
}
