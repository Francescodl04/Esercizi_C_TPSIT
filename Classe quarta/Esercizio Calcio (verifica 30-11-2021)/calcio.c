/** @file calcio.c
 * @author Francesco Di Lena, Classe 4F
 * @date 01/12/2021
 * @brief Scrittura del codice richiesto dalla verifica di TPSIT del 30/11/2021 (vedi Google Classroom).
 **/

#include <stdio.h>    //Libreria che contiene funzioni per l'input/output.
#include <stdlib.h>   //Libreria che contiene funzioni di utilità generale.
#include <string.h>   //Libreria che contiene funzioni per la gestione delle stringhe.
#include <ctype.h>    //Libreria che contiene funzioni per la gestione dei caratteri.
#include <unistd.h>   //Libreria che permette l'interfacciamento con il sistema operativo Unix, quindi permette l'uso di system call.
#include <sys/wait.h> //Libreria che permette di usare system call, in particolare quelle di attesa come wait() o waitpid().

/** \param struct Giocatore_T
 *  \param char nome[10] : Indica il nome del giocatore di calcio.
 *  \param char cognome[10] : Indica il cognome del giocatore di calcio.
 *  \param char ruolo[10] : Indica il ruolo del giocatore di calcio.
 *  \brief Struttura che definisce un tipo di variabile creato ad hoc per il programma.
**/

typedef struct
{
    char nome[10];
    char cognome[10];
    char ruolo[10];
} Giocatore_T;

/** \fn int lettura_file(char percorso_file[100], Giocatore_T giocatori[100])
 *  \param char percorso_file[] : Percorso relativo dove viene effettuata la lettura del file.
 *  \param Giocatore_T giocatori[100] : Elenco dei giocatori letti nel file.
 *  \param FILE *file : Puntatore al file.
 *  \param int i : Indice del ciclo for.
 *  \param int numero_giocatori : Numero di giocatori letti nel file.
 *  \brief Questa funzione permette di effettuare la lettura del file e l'inserimento dei calciatori all'interno di una matrice unidimensionale.
 *  \return int numero_giocatori : Restituisce il numero di giocatori letti nel file.
 **/

int lettura_file(char percorso_file[], Giocatore_T giocatori[])
{
    FILE *file;
    int i, numero_giocatori;
    file = fopen(percorso_file, "r");
    for (i = 0; !feof(file); i++)
    {
        numero_giocatori++;
        fscanf(file, "%s %s %s", giocatori[i].nome, giocatori[i].cognome, giocatori[i].ruolo);
    }
    return numero_giocatori;
}

/** \fn void mostra_attaccanti(Giocatore_T giocatori[100], int numero_giocatori)
 *  \param Giocatore_T giocatori[100] : Elenco dei giocatori letti nel file.
 *  \param int i : Indice del ciclo for.
 *  \param int j : Contatore per la visualizzazione dell'elenco numerato.
 *  \param int numero_giocatori : Numero di giocatori letti nel file.
 *  \brief Questa funzione permette di mostrare solo i giocatori che hanno ruolo di attaccante.
 *  \return La funzione è di tipo void, quindi non ritorna nulla.
 **/

void mostra_attaccanti(Giocatore_T giocatori[100], int numero_giocatori)
{
    int i, j = 0;
    for (i = 0; i < numero_giocatori; i++)
    {
        if (strcmp(giocatori[i].ruolo, "attaccante") == 0)
        {
            j++;
            printf("%d) %s %s %s", j, giocatori[i].nome, giocatori[i].cognome, giocatori[i].ruolo);
        }
    }
}

/** \fn int main(int argc, char *argv[])
 *  \param int argc
 *  \param char *argv[]
 *  \param pid_t pid_processo
 *  \param int numero_giocatori
 *  \param int status
 *  \param Giocatore_T giocatori[100]
 *  \brief La funzione permette di creare un processo padre e figlio e di affidare loro compiti distinti.
 *  \return La funzione ritorna il valore intero 0.
 **/

int main(int argc, char *argv[])
{
    printf("Benvenuto nel programma!\n");
    if (argc == 2)
    {
        int numero_giocatori = 0, status;
        Giocatore_T giocatori[100];
        pid_t pid_processo;
        pid_processo = fork();
        if (pid_processo != 0)
        {
            numero_giocatori = lettura_file(argv[1], giocatori);
            fflush(stdin);
            printf("Per uscire dal programma premi un tasto qualsiasi...\n");
            getchar();
        }
        else
        {
            wait(&status);
            mostra_attaccanti(giocatori, numero_giocatori);
            exit(1);
        }
    }
    else
    {
        printf("Non sono stati inseriti argomenti sufficienti all'invocazione del programma.\n");
    }
}