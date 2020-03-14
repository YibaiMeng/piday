#include<cmath>
#include<functional>
#include<iostream>
#include<vector>

#include "calc.h"

double sum(double a, double b) {
    return a + b;
}	

double subtract(double a, double b) {
    return a - b;
}	
double multiply(double a, double b) {
    return a * b;
}	
double divide(double a, double b) {
    return a / b;
}

double power(double a, double b) {
    return std::pow(a, b);
}

double myLog(double a, double b) {
    return std::log(b) / std::log(a);
}

// Generated with 
//     import math
//     print([str(math.factorial(i))+".0" for i in range(0,170)])
// because double is in the range of 0 to 170
#include "factorial_lookup.in"
double factorial(double a) {
    if (std::isnan(a)) return NAN;
    if (std::abs(a - std::round(a)) > 1e-6 ) return NAN;
    if (a < 0 or a >= 170) return NAN;
    return lookup[(int)std::round(a)];
}
