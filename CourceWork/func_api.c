#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func_api.h"


int PrintHelp(void)
{
    printf("Root and Integral calculate application\n\n");

    printf("Functions:\n");
    printf("f1 = 0.6*x + 3\n");
    printf("f2 = (x - 2)^3 - 1\n");
    printf("f3 = 3 / x\n\n");

    printf("Usage:\n");
    printf("  program [options]\n\n");

    printf("Options:\n");
    printf("  -h        Show this help\n");
    printf("  -f N      Select function (1, 2 or 3)\n");
    printf("  -r        Find roots\n");
    printf("  -i        Calculate integral / area\n\n");

    printf("Examples:\n");
    printf("  program -r\n");
    printf("  program -i\n");
    printf("  program -r -i\n");
    printf("  program -f 1 -r\n");
    printf("  program -f 2 -i\n");

    return 0;
}

int signF( double x, function f) { 
	return f(x)==0 ? 0 : (f(x) < 0 ? -1:+1); 
}

//метод деления отрезка пополам
double rootFindDiv(double xl, double xr, double eps, function f)  
{ 
    int stepcount=0; //число шагов    
    double xm; 
    
    
    if (signF(xl, f) == signF(xr, f))
    {
        printf("No root on this interval\n");
        return NAN;
    }
    
    while(fabs(xr-xl)>eps) { 
        //вещественный модуль разницы        
        stepcount++;        
        xm=(xl+xr)/2; // середина отрезка 
        if(f(xr)==0) 
        { 
            // нашли решение на правой границе            
            printf("Find root for %d steps\n",stepcount);            
            return xr;        
        }
        if(f(xl)==0) 
        { 
            // нашли решение на левой границе            
            printf("Find root for %d steps\n",stepcount);            
            return xl;        }        
            if(signF(xl,f) != signF(xm,f)) 
            { //если знак отличается            
            xr=xm;
            }        
            else   
            {
                xl=xm;
            }             
        }    
        printf("Find root for %d steps\n",stepcount); //статистика    
        return (xl+xr)/2;
}

//Представления функций
double f1(double x)
{
    return 0.6*x+3;
}
double f2(double x)
{
    return (x-2)*(x-2)*(x-2) - 1;
}
double f3(double x)
{
    return 3/x;
}

//Разница функций
double f31(double x)
{
    return f3(x) - f1(x);
}
double f32(double x)
{
    return f3(x) - f2(x);
}
double f21(double x)
{
    return f2(x) - f1(x);
}

//Области для вычисления интеграллов
double area1(double x)
{
    return f1(x) - f3(x);
}

double area2(double x)
{
    return f1(x) - f2(x);
}


//Вычиление интеграллов метод Симпсона
double calcIntegralSimpson(double xl, double xr, size_t n, function f) 
{    
	double sum = 0;    
	double h = (xr-xl)/n;    
	for(double x=xl+h; x<xr-h; x+=h) 
	{        
		sum += h/6.0*(f(x) + 4.0*f(0.5*(x+x+h)) + f(x+h));    
	}    
	return sum; 
}