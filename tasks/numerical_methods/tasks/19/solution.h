#pragma once

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    double start_segment;
    double end_segment;
    double x0;
} Segment;

double CalculatingDerivatie(double x) {
    return 0.2 * x - log(x) - 1;
}

double FirstFunc(double x) {
    return 1 / (3 + sin(3.6 * x));
}

double SecondFunc(double x) {
    return 0.1 * pow(x, 2) - x * log(x);
}

double MethodSimpleIteartions(double x0, double (*first_func)(double x)) {
    // x0 это x(n-1)
    // xn просто x
    // xn1 это x(n+1)
    double xn = first_func(x0);
    double xn1 = first_func(xn);
    while (fabs((xn1 - xn) / (1 - ((xn1 - xn) / (xn - x0)))) > DBL_EPSILON) {
        x0 = xn;
        xn = xn1;
        xn1 = first_func(xn);
    }
    return xn;
}

double NewtonMethod(double x0, double (*second_func)(double x), double (*calculating_derivatie)(double x)) {
    double xn = x0 - (second_func(x0) / calculating_derivatie(x0));
    double xn1 = xn - (second_func(xn) / calculating_derivatie(xn));
    while (fabs((xn1 - xn) / (1 - ((xn1 - xn) / (xn - x0)))) >= DBL_EPSILON) {
        x0 = xn;
        xn = xn1;
        xn1 = xn - second_func(xn) / calculating_derivatie(xn);
    }
    return xn;
}

int Task() {
    Segment first_function = {0.0, 0.85, (0.85 - 0.0) / 2};
    Segment second_function = {1.0, 2.0, (2.0 - 1.0) / 2};
    double root_first_function = MethodSimpleIteartions(first_function.x0, FirstFunc);
    printf("Method: iterations | segment [%lf, %lf] | approximate root: %lf\n", first_function.start_segment,
           first_function.end_segment, root_first_function);
    double root_second_function = NewtonMethod(second_function.x0, SecondFunc, CalculatingDerivatie);
    printf("Method: Newton | segment [%lf, %lf] | approximate root: %lf\n", second_function.start_segment,
           second_function.end_segment, root_second_function);
    return 0;
}