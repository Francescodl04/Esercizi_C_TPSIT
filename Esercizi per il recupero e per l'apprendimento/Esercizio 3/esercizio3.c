/** \file esercizio3.c
 * \author Francesco Di Lena, Classe 4F
 * \date 02/12/2021
 * \version 1.0
 * \brief Scrivi un programma dove vengono generati tre processi e fai scrivere a ciascuno di essi sullo schermo rispettiva-
          mente “Ciao, io sono Qui”, “Ciao, io sono Quo” e “Ciao, io sono Qua”.
 **/

#include <stdio.h>    //Libreria di standard input/output.
#include <stdlib.h>   //Libreria che contiene funzioni di utilità generale.
#include <unistd.h>   //Libreria di interfaccia con il sistema operativo Unix.
#include <sys/wait.h> //Libreria apposita per le chiamate di sistema, in particolare quelle di attesa.

/** \fn int main()
 * \param pid_t pid_processo1 : PID restituito dalla prima chiamata della funzione fork().
 * \param pid_t pid_processo2 : PID restituito dalla seconda chiamata della funzione fork().
 * \brief La funzione main() permette la creazione di due processi figlio attraverso la chiamata doppia della funzione fork() e mostra a schermo il PID dei tre processi totali.
 * \return La funzione ritorna il valore di tipo intero 0.
**/

int main()
{
    pid_t pid_processo1, pid_processo2;
    printf("Benvenuto nel programma!\n");
    pid_processo1 = fork(); //La funzione fork() permette di eseguire il biforcamento di un processo: si crea quindi un processo padre e un figlio.
    if (pid_processo1 == 0) //Se il processo in esecuzione è il figlio, quindi la fork() restituisce 0, allora esegue le seguenti istruzioni.
    {
        pid_processo2 = fork(); //La funzione fork() permette di eseguire un ulteriore biforcamento del processo figlio.
        if (pid_processo2 == 0) //Se il processo in esecuzione è il figlio, quindi la fork() restituisce 0, allora esegue le seguenti istruzioni.
        {
            printf("Ciao, io sono Qua!\n");
            exit(0); //La funzione exit(int status) permette di uscire dal processo, in questo caso il figlio.
        }
        else //Nell'altro caso il processo è il padre.
        {
            printf("Ciao, io sono Quo!\n");
        }
    }
    else //Nell'altro caso il processo è il padre.
    {
        printf("Ciao, io sono Qui!\n");
    }
    return 0;
}
