/**@author Francesco Di Lena
 **@date 08/11/2021
 **@filename esercizio_scegli_piu_vecchio.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numero_persone 4

typedef struct
{
    char nome_persona[200];
    char cognome_persona[200];
    int eta_persona;
} persona_T;

persona_T inserisci()
{
}

void vecchio()
{
    int piu_vecchio = 0;
    int i;
    for (i = 0; i < numero_persone; i++)
    {
        if (i == 0)
        {
            piu_vecchio = 0;
        }
        else if (piu_vecchio < 0)
        {
            piu_vecchio = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    printf("\nBenvenuto nel programma.");
    int i, j;
    persona_T p[numero_persone];
    char testo_da_visualizzare[3][200] = {"il nome", "il cognome", "l'eta'"};
    for (i = 0; i < numero_persone; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("\nInserisci %s della %da persona:\n", testo_da_visualizzare[j], i + 1);
            switch (j)
            {
            case 0:
                scanf("%s", &p->nome_persona);
                break;
            case 1:
                scanf("%s", &p->cognome_persona);
                break;
            case 2:
                scanf("%d", &p->eta_persona);
                break;
            }
        }
    }
    fflush(stdin);
    printf("\nPer uscire dal programma premere un tasto qualsiasi...");
    getchar();
    return 0;
}