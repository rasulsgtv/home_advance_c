#include <stdint.h>
#ifndef FUNC_API_H
#define FUNC_API_H

#define N 1000 //количество шагов интегрирования

typedef double(*function)(double);


int PrintHelp(void);
int signF( double x, function f);
double rootFindDiv(double xl, double xr, double eps, function f);


double f1(double x);
double f2(double x);
double f3(double x);


double f31(double x);
double f32(double x);
double f21(double x);

double area1(double x);
double area2(double x);


double calcIntegralSimpson(double xl, double xr, size_t n, function f); 


#endif