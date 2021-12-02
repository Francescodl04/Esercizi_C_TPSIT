/** \file esercizio2.c
 * \author Francesco Di Lena, Classe 4F
 * \date 02/12/2021
 * \version 1.0
 * \brief Scrivi un programma in linguaggio C che possa ricevere come input un numero intero immesso da tastiera.
          A tale numero, il processo figlio creato somma 15, mentre il processo padre somma 10.
          Visualizza il risultato dopo ogni operazione.
 **/

#include <stdio.h>    //Libreria di standard input/output.
#include <stdlib.h>   //Libreria che contiene funzioni di utilità generale.
#include <unistd.h>   //Libreria di interfaccia con il sistema operativo Unix.
#include <sys/wait.h> //Libreria apposita per le chiamate di sistema, in particolare quelle di attesa.

/** \fn int somma(int primo_addendo, int secondo_addendo)
 * \param int primo_addendo : Il primo addendo inserito dall'utente per eseguire l'addizione.
 * \param int secondo_addendo : Il secondo addendo che può essere 10 o 15 in base al tipo di processo che richiama la funzione.
 * \brief Esegue la somma di due numeri.
 * \return La funzione ritorna il valore dei due numeri sommati.
 **/

int somma(int primo_addendo, int secondo_addendo)
{
    return primo_addendo + secondo_addendo;
}

/** \fn int main()
 * \param pid_t pid_processo : PID del processo in esecuzione.
 * \param int primo_addendo : Il primo addendo inserito dall'utente per eseguire l'addizione.
 * \param int risultato : Il risultato dell'addizione.
 * \brief La funzione main() permette la creazione di un processo figlio attraverso la funzione fork() e mostra a schermo il PID del processo padre e del figlio.
 * \return La funzione ritorna il valore intero 0.
 **/

int main()
{
    pid_t pid_processo;
    printf("Benvenuto nel programma!\n");
    printf("Inserisci il primo addendo:\n");
    int primo_addendo, risultato;
    scanf("%d", &primo_addendo); //Effettua la lettura dell'input da tastiera e lo inserisce nella variabile primo_addendo.
    pid_processo = fork();       //La funzione fork() permette di eseguire il biforcamento di un processo: si crea quindi un processo padre e un figlio.
    if (pid_processo == 0)       //Se il processo in esecuzione è il figlio, quindi la fork() restituisce 0, allora esegue le seguenti istruzioni.
    {
        printf("Sono il processo figlio e il mio Process Identifier (PID) e': %d.\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
        risultato = somma(primo_addendo, 15);                                                    //Si esegue la somma.
        printf("Il risultato dell'operazione e' %d.\n", risultato);                              //Viene mostrato il risultato della somma.
        exit(0);                                                                                 //La funzione exit(int status) permette di uscire dal processo, in questo caso il figlio.
    }
    else //Nell'altro caso il processo è il padre.
    {
        printf("Sono il processo padre e il mio Process Identifier (PID) e': %d.\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
        risultato = somma(primo_addendo, 10);                                                   //Si esegue la somma.
        printf("Il risultato dell'operazione e' %d.\n", risultato);                             //Viene mostrato il risultato della somma.
    }
    return 0;
}