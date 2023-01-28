#include "factorial.h"

int32_t factorial(int32_t number){

    if(number < 0) throw std::invalid_argument("Negatives Argument ist unzulässig");
    if(number == 0) return 1;
    int32_t fact = 1;

    for(int32_t i = 1; i <= number; i++){
        int32_t a = fact * i;
        if (fact != 0 && a / fact != i) throw std::overflow_error(std::string("Multiplikationsueberlauf ab ") + std::to_string(i));
        fact = a;
    }

    return fact;
}
