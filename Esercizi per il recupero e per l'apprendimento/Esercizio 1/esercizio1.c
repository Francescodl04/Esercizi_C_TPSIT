/** @file esercizio1.c
 * @author Francesco Di Lena, Classe 4F
 * @date 02/12/2021
 * @version 1.0
 * @brief Scrivi un programma C che stampa a video il pid del processo che lancerà un fork e dopo la sua esecuzione sia in grado di identificare i processi genitore e figlio 
          con i relativi pid testando i valori di ritorno della fork.
 **/

#include <stdio.h>    //Libreria di standard input/output.
#include <stdlib.h>   //Libreria che contiene funzioni di utilità generale.
#include <unistd.h>   //Libreria di interfaccia con il sistema operativo Unix.
#include <sys/wait.h> //Libreria apposita per le chiamate di sistema, in particolare quelle di attesa.

/** @fn int main()
 * @param pid_t pid_processo: PID del processo in esecuzione.
 * @brief La funzione main() permette la creazione di un processo figlio attraverso la funzione fork() e mostra a schermo il PID del processo padre e del figlio.
 * @return La funzione è di tipo void, quindi non ritorna alcun valore.
 **/

int main()
{
    pid_t pid_processo;
    printf("Benvenuto nel programma!\n");
    pid_processo = fork(); //La funzione fork() permette di eseguire il biforcamento di un processo: si crea quindi un processo padre e un figlio.
    if (pid_processo == 0) //Se il processo in esecuzione è il figlio, quindi la fork() restituisce 0, allora esegue le seguenti istruzioni.
    {
        printf("Sono il processo figlio e il mio Process Identifier (PID) e': %d\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
        exit(0);                                                                                //La funzione exit(int status) permette di uscire dal processo, in questo caso il figlio.
    }
    else //Nell'altro caso il processo è il padre.
    {
        printf("Sono il processo padre e il mio Process Identifier (PID) e': %d\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
    }
    return 0;
}