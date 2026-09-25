#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "func_api.h"





int main(int argc, char *argv[])
{
	 int rez;

    int doRoot = 0;
    int doIntegral = 0;
    int selectedFunction = 0;   // 0 = все функции

    if (argc == 1)
    {
        PrintHelp();
        return 0;
    }

    while ((rez = getopt(argc, argv, "hri")) != -1)
    {
        switch (rez)
        {
            case 'h':
                PrintHelp();
                return 0;

            case 'r':
                doRoot = 1;
                break;

            case 'i':
                doIntegral = 1;
                break;

            default:
                PrintHelp();
                return 1;
        }
    }

     // Если пользователь не указал -r или -i,
     // ничего вычислять не будем.
    if (!doRoot && !doIntegral)
    {
        printf("Error: specify -r or -i\n\n");
        PrintHelp();
        return 1;
    }


     // Вычисление корней
    if (doRoot)
    {
        double x1 = rootFindDiv(-7, -5, 0.000001, f31);
        double x2 = rootFindDiv(-0.5, -0.1, 0.000001, f32);
        double x3 = rootFindDiv(3, 4, 0.000001, f21);

        printf("\nRoots:\n");

        printf("x1 = %.10f\n", x1);
        printf("x2 = %.10f\n", x2);
        printf("x3 = %.10f\n", x3);
    }


    /*
     * =========================
     *       INTEGRAL
     * =========================
     */

    if (doIntegral)
    {
        double x1 = rootFindDiv(-7, -5, 0.000001, f31);
        double x2 = rootFindDiv(-0.5, -0.1, 0.000001, f32);
        double x3 = rootFindDiv(3, 4, 0.000001, f21);

    

        double S1 = calcIntegralSimpson(x1, x2, N, area1);
        double S2 = calcIntegralSimpson(x2, x3, N, area2);

        double S = S1 + S2;

        printf("\nIntegral / area:\n");

        printf("S1 = %.10f\n", S1);
        printf("S2 = %.10f\n", S2);
        printf("S  = %.10f\n", S);
    }

		
	
	/*
	double x1 = rootFindDiv(-7, -5, 0.000001, f31);
	printf("x1 = %.10f\n", x1);
	
    double x2 = rootFindDiv(-0.5, -0.1, 0.000001, f32);
    printf("x2 = %.10f\n", x2);
    
    double x3 = rootFindDiv(3, 4, 0.000001, f21);
	printf("x3 = %.10f\n", x3);
    
 
    size_t n = 1000; // количество шагов при интегрировании

    double S1 = calcIntegralSimpson(x1, x2, n, area1);
    double S2 = calcIntegralSimpson(x2, x3, n, area2);

    double S = S1 + S2;

    printf("S1 = %.10f\n", S1);
    printf("S2 = %.10f\n", S2);
    printf("S  = %.10f\n", S);
	*/
	
	return 0;
}
