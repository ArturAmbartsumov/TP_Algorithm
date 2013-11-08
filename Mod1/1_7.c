/*
 ============================================================================
 Name        : Task7.c
 Author      : Artur Ambartsumov
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int turn(int Number);

int main(void)   {
	int N = 0;
    scanf("%d", &N);
    printf("\n%d", turn(N));
    return EXIT_SUCCESS;
}

int turn(int Number)   {
    int buff = 0;
    int result = 0;
    while (!(Number == 0))   {
        buff = Number % (10);
        result = result * 10 + buff;
        Number = Number/10;
    }
    return result;
}
