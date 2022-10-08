/**
 * @name Francesco Di Lena, classe 5F
 * @date 16/09/2022
 * @brief Il programma individua il massimo e il minimo da una serie di numeri.
 * @file esercizio.c
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

int individua_massimo(int index, int numeri[])
{
    int i, massimo = numeri[0];
    for (i = 1; i < index; i++)
    {
        if (numeri[i] > massimo)
        {
            massimo = numeri[i];
        }
    }
    return massimo;
}

int individua_minimo(int index, int numeri[])
{
    int i, minimo = numeri[0];
    for (i = 1; i < index; i++)
    {
        if (numeri[i] < minimo)
        {
            minimo = numeri[i];
        }
    }
    return minimo;
}

void main(int argc, char *argv[])
{
    int i, index = 0;
    printf("Inserisci il numero di numeri che vuoi inserire:\n");
    scanf("%d", &index);
    int numeri[index];
    for (i = 0; i < index; i++)
    {
        printf("Inserisci il %d numero:\n", i + 1);
        scanf("%d", &numeri[i]);
    }
    printf("Il massimo è %d, mentre il minimo è %d.\n", individua_massimo(index, numeri), individua_minimo(index, numeri));
    exit(0);
}