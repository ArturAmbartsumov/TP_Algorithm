/*
 ============================================================================
 Name        : Task14.c
 Author      : Artur Ambartsumov
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double triangleSquare(double * , double * , double *);
double sigmentLength(double * , double *);
double polygonSquare(int , double *);

int main(void)   {
    double points[100] = {0};
    int N = 0;
    scanf("%d", &N);
    for (int i = 0; i < N * 2; i++)
        scanf("%lf", &points[i]);
    printf("%0.3lf", polygonSquare(N, points));
    return EXIT_SUCCESS;
}


double sigmentLength(double *A, double *B)   {
    return sqrt(pow((*A - *B), 2) + pow((*(A + 1) - *(B + 1)), 2));
}


double triangleSquare(double *A, double *B, double *C)   {
    double AB = sigmentLength(A, B);
    double BC = sigmentLength(B, C);
    double CA = sigmentLength(C, A);
    double per = AB + BC + CA;
    return sqrt((per/2) * (per/2 - AB) * (per/2 - BC) * (per/2 - CA));
}

double polygonSquare(int number, double *points)   {
    double square = 0;
    for (size_t i = 1; i <= (number - 2); i++)
        square = square +
        triangleSquare(points, (points + i*2), (points + (i + 1)*2));
    return square;
}
