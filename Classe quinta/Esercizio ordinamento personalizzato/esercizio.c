/**
 * @name Francesco Di Lena, classe 5F
 * @date 08-10-2022
 * @brief Esercizio sull'ordinamento personalizzato in classroom.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_NUMERI 100
#define CRESCENTE 0
#define DECRESCENTE 1
#define PARI 0
#define DISPARI 1
#define PARTENZA_ORDINAMENTO 0
#define FINE_PRIMA_PARTE_ORDINAMENTO 20   // Viene aumentato di uno rispetto a 19 perché altrimenti l'algoritmo di ordinamento non prenderebbe in considerazione la posizione 19.
#define FINE_SECONDA_PARTE_ORDINAMENTO 40 // Viene aumentato di uno rispetto a 39 perché altrimenti l'algoritmo di ordinamento non prenderebbe in considerazione la posizione 39.
#define FINE_ORDINAMENTO 100              // Viene aumentato di uno rispetto a 99 perché altrimenti l'algoritmo di ordinamento non prenderebbe in considerazione la posizione 99.
#define MIN_RAND 1
#define MAX_RAND 233

/**
 * @fn void ordina_array(int crescente_decrescente, int *numeri, int inizio, int fine)
 * @param int crescente_decrescente
 * @param int *numeri
 * @param int inizio
 * @param int fine
 * @brief La funzione permette di ordinare l'array "numeri" in ingresso, a partire da "inizio" e fino a "fine", in ordine crescente o decrescente in base al valore della variabile "crescente_decrescente" in ingresso.
 */

void ordina_array(int crescente_decrescente, int *numeri, int inizio, int fine)
{
    int temp;
    for (int i = inizio; i < fine - 1; i++)
    {
        for (int j = inizio; j < fine - 1; j++)
        {
            if ((numeri[j] > numeri[j + 1] && crescente_decrescente == CRESCENTE) || (numeri[j] < numeri[j + 1] && crescente_decrescente == DECRESCENTE))
            {
                temp = numeri[j];
                numeri[j] = numeri[j + 1];
                numeri[j + 1] = temp;
            }
        }
    }
}

/**
 * @fn int verifica_numeri_pari_dispari(int pari_dispari, int *numeri, int inizio, int fine)
 * @param int pari_dispari
 * @param int *numeri
 * @param int inizio
 * @param int fine
 * @brief La funzione permette di contare il numero di numeri pari o dispari all'interno dell'array "numeri", a partire da "inizio" e fino a "fine", pari o dispari in base al valore della variabile "crescente_decrescente" in ingresso.
 * @return int n_pari_dispari : il contatore
 */

int verifica_numeri_pari_dispari(int pari_dispari, int *numeri, int inizio, int fine)
{
    int n_pari_dispari = 0;
    for (int i = inizio; i < fine; i++)
    {
        if ((numeri[i] % 2 == 0 && pari_dispari == PARI) || (numeri[i] % 2 != 0 && pari_dispari == DISPARI))
        {
            if (n_pari_dispari + inizio != i)
            {
                int temp = numeri[n_pari_dispari + inizio];
                numeri[n_pari_dispari + inizio] = numeri[i];
                numeri[i] = temp;
            }
            n_pari_dispari++;
        }
    }
    return n_pari_dispari;
}

/**
 * @fn int generazione_numeri_casuali(int *numeri)
 * @param int *numeri
 * @brief Permette di generare N_NUMERI numeri casuali e di inserirli all'interno dell'array "numeri".
 */

void generazione_numeri_casuali(int *numeri)
{
    for (int i = 0; i < N_NUMERI; i++)
    {
        numeri[i] = (rand() % MAX_RAND) + MIN_RAND;
        for (int j = 0; j < i; j++)
        {
            if (numeri[i] == numeri[j])
            {
                i--;
                break;
            }
        }
    }
}

/**
 * @fn void main()
 * @brief La funzione viene richiamata per prima all'avvio del programma ed esegue il richiamo delle funzioni, nonché le visualizzazioni a video.
 */

void main()
{
    srand(time(NULL));
    printf("Benvenuto nel programma!\n");
    int numeri[N_NUMERI];
    generazione_numeri_casuali(numeri);
    int posizione_arrivo_primo_ordinamento = verifica_numeri_pari_dispari(PARI, numeri, PARTENZA_ORDINAMENTO, FINE_PRIMA_PARTE_ORDINAMENTO);
    ordina_array(CRESCENTE, numeri, PARTENZA_ORDINAMENTO, posizione_arrivo_primo_ordinamento);
    int posizione_arrivo_secondo_ordinamento = FINE_PRIMA_PARTE_ORDINAMENTO + verifica_numeri_pari_dispari(DISPARI, numeri, FINE_PRIMA_PARTE_ORDINAMENTO, FINE_SECONDA_PARTE_ORDINAMENTO);
    ordina_array(DECRESCENTE, numeri, FINE_PRIMA_PARTE_ORDINAMENTO, posizione_arrivo_secondo_ordinamento);
    ordina_array(CRESCENTE, numeri, FINE_SECONDA_PARTE_ORDINAMENTO, FINE_ORDINAMENTO);
    printf("Ecco il vettore, ordinato secondo le istruzioni della consegna:\n");
    for (int i = 0; i < N_NUMERI; i++)
    {
        printf("%d) %d\n", i, numeri[i]);
    }
    exit(0);
}