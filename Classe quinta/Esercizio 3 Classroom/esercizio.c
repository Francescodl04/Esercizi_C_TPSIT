/**
 * @name Francesco Di Lena, classe 5F
 * @date 21/09/2022
 * @brief Esercizio 3 di classroom.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int *numbers, n_numbers, software_boot = 1;

/**
 * @fn int sum()
 * @brief Esegue la somma di tutti i numeri presenti nell'array.
 * @return int sum : ritorna la somma
 **/

int sum()
{
    int sum = 0;
    for (int i = 0; i < n_numbers; i++)
    {
        sum += numbers[i];
    }
    return sum;
}

/**
 * @fn int even_odd_numbers(int number)
 * @param int number : il numero che deve essere analizzato
 * @brief Determina se un numero è pari o dispari.
 * @returns int : ritorna 1 se è dispari, mentre 0 se è pari
 **/

int even_odd_numbers(int number)
{
    if (number % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @fn int number_research(int researched_number, int *indexes)
 * @param int researched_number : numero ricercato
 * @param int *indexes : conterrà gli indici dei numeri trovati
 * @brief Esegue la ricerca del numero inserito in argomento.
 **/

int number_research(int researched_number, int *indexes)
{
    int results = 0;
    for (int i = 0; i < n_numbers; i++)
    {
        if (numbers[i] == researched_number)
        {
            indexes = realloc(indexes, (results + 1) * sizeof(int));
            indexes[results] = i;
            results++;
        }
    }
    return results;
}

/**
 * @fn int array_sort()
 * @brief Esegue l'ordinamento dell'array con l'algoritmo bubble sort.
 **/

void array_sort()
{
    int temp;
    for (int i = 0; i < n_numbers - 1; i++)
    {
        for (int j = 0; j < n_numbers - i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

/**
 * @fn void numbers_generator()
 * @brief Esegue la generazione casuale dei numeri e li inserisce nell'array.
 **/

void numbers_generator()
{
    for (int i = 0; i < n_numbers; i++)
    {
        numbers[i] = rand() % 100;
    }
}

/**
 * @fn int main()
 * @brief Mostra il menu, raccoglie gli inserimenti da parte dell'utente, richiama le altre funzioni.
 **/

int main()
{
    int choice;
    char *menu[10] = {"Stampa gli elementi dell' array", "Stampa inversa degli elementi dell’array", "Somma e media degli elementi dell'array", "Stampa tutti i numeri pari",
                      "Stampa tutti i numeri dispari", "Ricerca di un numero nell’array", "Eliminare un elemento dell’array", "Alternare a due a due le posizioni del vettore",
                      "Ordinamento del vettore", "Esci dal programma"};
    system("clear");
    if (software_boot == 1)
    {
        printf("Benvenuto nel programma! Inserisci il numero di numeri che desideri generare:\n");
        scanf("%d", &n_numbers);
        numbers = malloc(n_numbers * sizeof(int));
        numbers_generator();
    }
    system("clear");
    printf("Ora che sono stati generati i numeri, scegli un'operazione da eseguire:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d) %s.\n", i, menu[i]);
    }
    scanf("%d", &choice);
    getchar();
    system("clear");
    switch (choice)
    {
    case 0:
        printf("Ecco gli elementi che compongono il vettore con il loro rispettivo indice:\n");
        for (int i = 0; i < n_numbers; i++)
        {
            printf("%d) %d\n", i, numbers[i]);
        }
        break;
    case 1:
        printf("Ecco gli elementi che compongono il vettore con il loro rispettivo indice (all'inverso):\n");
        for (int i = n_numbers - 1; i >= 0; i--)
        {
            printf("%d) %d\n", i, numbers[i]);
        }
        break;
    case 2:
        printf("La somma è %d, mentre la media è %d.\n", sum(), sum() / n_numbers);
        break;
    case 3:
        printf("Ecco gli elementi pari che compongono il vettore con il loro rispettivo indice:\n");
        for (int i = 0; i < n_numbers; i++)
        {
            if (even_odd_numbers(numbers[i]) == 0)
            {
                printf("%d) %d\n", i, numbers[i]);
            }
        }
        break;
    case 4:
        printf("Ecco gli elementi dispari che compongono il vettore con il loro rispettivo indice:\n");
        for (int i = 0; i < n_numbers; i++)
        {
            if (even_odd_numbers(numbers[i]) == 1)
            {
                printf("%d) %d\n", i, numbers[i]);
            }
        }
        break;
    case 5:
        printf("Inserisci il numero che desideri ricercare:\n");
        int researched_number;
        scanf("%d", &researched_number);
        int results = number_research(researched_number, NULL);
        if (results == 1)
        {
            printf("Il numero ricercato è stato trovato una volta.\n");
        }
        else
        {
            printf("Il numero ricercato è stato trovato %d volte.\n", results);
        }
        getchar();
        break;
    case 6:
        printf("Inserisci il numero che desideri eliminare:\n");
        scanf("%d", &researched_number);
        int *indexes;
        indexes = malloc(sizeof(int));
        results = number_research(researched_number, indexes);
        if (results == 0)
        {
            printf("L'elemento che desideri eliminare nell'array non esiste.\n");
        }
        else
        {
            for (int i = 0; i < results; i++)
            {
                for (int j = indexes[i]; j < n_numbers; j++)
                {
                    numbers[j] = numbers[j + 1];
                }
                for (int j = i; j < results; j++)
                {
                    indexes[j]--;
                }
            }
            n_numbers -= results;
            numbers = realloc(numbers, n_numbers * sizeof(int));
            printf("Eliminazione completata con successo!\n");
        }
        getchar();
        break;
    case 7:
        for (int i = 0; i < n_numbers; i += 2)
        {
            if (n_numbers % 2 == 0 || (n_numbers % 2 != 0 && i != n_numbers - 1))
            {
                int temp;
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
            }
        }
        printf("Ecco gli elementi che compongono il vettore scambiati a due a due con il loro rispettivo indice:\n");
        for (int i = 0; i < n_numbers; i++)
        {
            printf("%d) %d\n", i, numbers[i]);
        }
        break;
    case 8:
        array_sort();
        printf("Ecco il vettore ordinato:\n");
        for (int i = 0; i < n_numbers; i++)
        {
            printf("%d) %d\n", i, numbers[i]);
        }
        break;
    case 9:
        exit(0);
    }
    software_boot = 0;
    fflush(stdin);
    printf("\nPer tornare al menu principale premere un tasto qualsiasi...");
    getchar();
    main();
}