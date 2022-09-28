/** 
 *  \file esercizio1.c
 *  \author Francesco Di Lena, Classe 4F
 *  \date 16/12/2021
 *  \version 1.0
 *  \brief Si realizzi un programma C in cui due processi, uno padre e l'altro figlio, interagiscono. Il processo padre genera casualmente (funzione rand()) 10 numeri interi e li passa al figlio. 
 *  \n Il processo figlio esegue la somma dei numeri passati dal padre e gli restituisce il risultato. Il processo padre stampa a video il risultato.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/// \brief Indica il numero di numeri che devono essere generati casualmente.
#define NUMERI_GENERATI 10
/// \brief Indica la lunghezza della stringa che rappresentetà il contenuto letto da una pipe.
#define LUNGHEZZA_CONTENUTO_LETTO_PIPE 100
/// \brief Indica il numero massimo che può essere generato casualmente.
#define MAX_RANDOM 100
/// \brief Indica il numero minimo che può essere generato casualmente.
#define MIN_RANDOM 1

/** 
 *  \fn void genera_numeri_casuali(char numeri_generati_casualmente[])
 *  \param int numeri_generati_casualmente[NUMERI_GENERATI] : Array che verrà popolato dai numeri generati casualmente.
 *  \param int i : Indice usato nel ciclo for.
 *  \brief Permette di generare numeri casuali sempre diversi fra loro e di inserirli all'interno di un array.
 *  \return La funzione è di tipo void, pertanto non restituisce nulla.
 **/

void genera_numeri_casuali(char numeri_generati_casualmente[])
{
    int i;
    srand(time(NULL)); //Questa funzione fa sì che non vengano generati di seguito gli stessi numeri casuali.
    for (i = 0; i < NUMERI_GENERATI; i++)
    {
        numeri_generati_casualmente[i] = rand() % MAX_RANDOM + MIN_RANDOM; //Viene generato il numero casuale e lo inserisce all'interno della posizione dell'array.
    }
}

/** 
 *  \fn void somma_numeri(char numeri_da_sommare[], char risultato_somma[])
 *  \param int numeri_da_sommare [NUMERI_GENERATI] : array popolato dai numeri che dovranno essere sommati.
 *  \param char risultato_somma[] : array che contiene il risultato della somma espresso in caratteri.
 *  \param int i : indice usato nel ciclo for.
 *  \param int somma : contiene la somma dei numeri presenti all'interno dell'array.
 *  \brief Svolge la somma di tutti i numeri presenti all'interno di un array.
 *  \return La funzione è di tipo void, pertanto non restituisce nulla.
 **/

void somma_numeri(char numeri_da_sommare[], char risultato_somma[])
{
    int i, somma = 0;
    for (i = 0; i < NUMERI_GENERATI; i++)
    {
        somma += numeri_da_sommare[i];
    }
    sprintf(risultato_somma, "%d", somma); //Inserisce il risultato della somma, espresso come intero, in una stringa.
}

/** 
 *  \fn int main()
 *  \param int file_descriptor1[2] : array che contiene il file-descriptor del primo canale pipe.
 *  \param int file_descriptor2[2] : array che contiene il file-descriptor del secondo canale pipe.
 *  \param int status_wait : contiene il puntatore al PID del processo che si deve attendere.
 *  \param char contenuto_letto[LUNGHEZZA_CONTENUTO_LETTO_PIPE] : array che contiene il contenuto letto dai due canali pipe.
 *  \param pid_t pid : contiene il valore del PID del processo che viene eseguito dopo la fork.
 *  \param char numeri_generati_casualmente[NUMERI_GENERATI] : array che contiene i numeri generati casualmente.
 *  \param int i : indice usato nel ciclo for.
 *  \param char risultato_somma[LUNGHEZZA_CONTENUTO_LETTO_PIPE]: array che contiene il risultato della somma .
 *  \brief Questa funzione permette la creazione di un processo figlio attraverso la funzione fork(), di due canali di tipo pipe e visualizzare a schermo i risultati delle altre due funzioni.
 *  \return La funzione restituisce il valore intero 0.
 **/

int main()
{
    int file_descriptor1[2], file_descriptor2[2], status_wait;
    char contenuto_letto[LUNGHEZZA_CONTENUTO_LETTO_PIPE];
    pid_t pid;
    printf("Benvenuto nel programma!\n\n");
    pipe(file_descriptor1); //Viene creato il primo canale pipe.
    pipe(file_descriptor2); //Viene creato il secondo canale pipe.
    pid = fork();           //Qui avviene un biforcamento: si crea processo padre e figlio.
    if (pid != 0)           //Operazioni eseguite dal processo padre.
    {
        close(file_descriptor1[0]); //Viene chiusa la lettura per questo processo nella prima pipe.
        char numeri_generati_casualmente[NUMERI_GENERATI];
        genera_numeri_casuali(numeri_generati_casualmente);                                               //Richiama la funzione per ottenere i numeri generati casualmente.
        write(file_descriptor1[1], numeri_generati_casualmente, strlen(numeri_generati_casualmente) + 1); //Esegue la scrittura dei numeri generati casualmente nella prima pipe.
        //Visualizzazioni a schermo dei numeri generati casualmente.
        int i;
        printf("Questi sono i %d numeri generati casualmente:\n", NUMERI_GENERATI);
        for (i = 0; i < NUMERI_GENERATI; i++)
        {
            if (i != NUMERI_GENERATI - 1)
            {
                printf("%d, ", numeri_generati_casualmente[i]);
            }
            else
            {
                printf("%d.\n\n", numeri_generati_casualmente[i]);
            }
        }
        wait(&status_wait);                                                                //Permette di attendere che venga eseguito il processo figlio.
        close(file_descriptor2[1]);                                                        //Viene chiusa la scrittura per questo processo nella seconda pipe.
        read(file_descriptor2[0], contenuto_letto, sizeof(contenuto_letto));               //Esegue la lettura del contenuto scritto dal processo figlio nella seconda pipe.
        printf("La somma tra i numeri generati casualmente e': %s.\n\n", contenuto_letto); //Visualizzazione a schermo del risultato della somma.
        printf("Per uscire dal programma premere un tasto qualsiasi...");
        getchar(); //Attende l'inserimento di un carattere qualsiasi.
    }
    else //Operazioni eseguite dal processo figlio.
    {
        close(file_descriptor1[1]);                                          //Viene chiusa la scrittura per questo processo nella prima pipe.
        read(file_descriptor1[0], contenuto_letto, sizeof(contenuto_letto)); //Esegue la lettura del contenuto scritto dal processo padre nella prima pipe.
        char risultato_somma[LUNGHEZZA_CONTENUTO_LETTO_PIPE];
        somma_numeri(contenuto_letto, risultato_somma);
        close(file_descriptor2[0]);                                               //Viene chiusa la lettura per questo processo nella seconda pipe.
        write(file_descriptor2[1], risultato_somma, strlen(risultato_somma) + 1); //Esegue la scrittura del risultato della somma nella seconda pipe.
        exit(1);                                                                  //Termina il processo.
    }
    return 0;
}
