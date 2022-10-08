#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int indice_numeri = 0;

int inserisci_numero(int numero, int *numeri)
{
    numeri[indice_numeri] = numero;
    indice_numeri++;
    numeri = realloc(numeri, (indice_numeri + 1) * sizeof(int));
    return 0;
}

int verifica_numero(int numero_ricercato, int *numeri, int *indici)
{
    int risultati = 0;
    for (int i = 0; i < indice_numeri; i++)
    {
        if (numeri[i] == numero_ricercato)
        {
            if (indici != NULL)
            {
                indici[risultati] = i;
                indici = realloc(indici, (risultati + 1) * sizeof(int));
            }
            risultati++;
        }
    }
    return risultati;
}

void elimina_numero(int numero_da_eliminare, int *numeri)
{
    int *indici = calloc(1, sizeof(int));
    int risultati = verifica_numero(numero_da_eliminare, numeri, indici);
    if (risultati == 0)
    {
        return 1;
    }
    for (int i = 0; i < risultati; i++)
    {
        for (int j = indexes[i]; j < indice_numeri; j++)
        {
            numbers[j] = numbers[j + 1];
        }
        for (int j = i; j < risultati; j++)
        {
            indexes[j]--;
        }
    }
    indice_numeri -= risultati;
    numeri = realloc(numeri, indice_numeri * sizeof(int));
    return 0;
}

void ordina_vettore(int *numeri)
{
    int temp;
    for (int i = 0; i < indice_numeri - 1; i++)
    {
        for (int j = 0; j < indice_numeri - i - 1; j++)
        {
            if (numeri[j] > numeri[j + 1])
            {
                temp = numeri[j];
                numeri[j] = numeri[j + 1];
                numeri[j + 1] = temp;
            }
        }
    }
}

void main()
{
    int *numeri, scelta;
    numeri = (int *)calloc(1, sizeof(int));
    char *testo_menu[5] = {"inserisci numero", "verifica numero", "elimina numero", "ordina il vettore di numeri", "esci dal programma"};
    do
    {
        system("clear");
        printf("Benvenuto nel programma. Scegli una delle seguenti opzioni:\n");
        for (int i = 0; i < 5; i++)
        {
            printf("%d) %s\n", i + 1, testo_menu[i]);
        }
        scanf("%d", &scelta);
        system("clear");
        switch (scelta)
        {
        case 1:
            printf("Inserisci il numero che desideri aggiungere al vettore:\n");
            int numero;
            scanf("%d", &numero);
            if (inserisci_numero(numero, numeri) == 0)
            {
                printf("Aggiunta completata con successo!\n");
            }
            break;
        case 2:
            printf("Inserisci il numero che desideri verificare:\n");
            scanf("%d", &numero);
            int risultati = verifica_numero(numero, numeri, NULL);
            if (risultati == 0)
            {
                printf("Il numero da te ricercato non è presente all'interno del vettore.\n");
            }
            else
            {
                printf("Il numero è stato trovato %d volte.\n", risultati);
            }
            break;
        case 3:
            printf("Inserisci il numero che desideri eliminare:\n");
            scanf("%d", &numero);
            switch (elimina_numero(numero, numeri))
            {
            case 0:
                printf("Eliminazione completata con successo!\n");
                break;
            case 1:
                printf("Il numero da te ricercato non è presente all'interno del vettore.\n");
                break;
            }
            break;
        case 4:
            ordina_vettore(numeri);
            if (indice_numeri == 0)
            {
                printf("Non sono presenti ancora numeri all'interno del vettore, inseriscili...\n");
            }
            else
            {
                printf("Ecco il vettore con gli elementi ordinati in modo crescente:\n");
                for (int i = 0; i < indice_numeri; i++)
                {
                    printf("%d) %d\n", i + 1, numeri[i]);
                }
            }
            break;
        case 5:
            exit(0);
        }
        printf("Per tornare al menu principale, premi un tasto qualsiasi...");
        char ptr;
        getchar();
        scanf("%c", &ptr);
    } while (1);
}