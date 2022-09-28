/**
 * @file esercizio2.c
 * @author Francesco Di Lena, classe 4F
 * @brief Scrivere un programma concorrente che realizzi il seguente comando:
   \n cat file.txt | wc
   \n il processo p2 deve rimandare l'output di wc al padre, il quale lo scriverà
   \n su un file chiamato wc.txt. Il nome del file "file.txt" deve essere passato come argomento in argv[1].
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief La funzione main esegue tutte le istruzioni richieste dalla consegna dell'esercizio.
 * 
 * @param int argc : numero di argomenti inseriti.
 * @param char *argv[] : puntatore agli argomenti inseriti.
 * @return La funzione ritorna il valore 0 nel padre e -1 nei figli nel caso, in questi ultimi, che ci sia stato un errore.
*/

int main(int argc, char *argv[])
{
    printf("Benvenuto nel programma!\n");
    if (argc == 2) //Esegue un controllo sul numero di argomenti passati.
    {
        pid_t pid;
        int p1p0[2], p2p0[2]; //Vengono inizializzati gli array che conterranno i file descriptor delle pipe.
        //Vengono creati i due canali pipe necessari.
        pipe(p1p0); 
        pipe(p2p0);
        pid = fork(); //Eseguo la fork: creo un processo padre e un processo figlio.
        if (pid == 0) //Se si tratta del processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
        {
            close(1); //Chiudo il file descriptor di STDOUT.
            dup(p1p0[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
            //Chiudo entrambe le estremità della pipe.
            close(p1p0[0]);
            close(p1p0[1]);
            execl("/usr/bin/cat", "cat", argv[1], NULL); //Eseguo il comando CAT.
            return -1;
        }
        else //Se si tratta del processo padre in esecuzione, allora eseguo le seguenti istruzioni.
        {
            pid = fork(); //Eseguo la fork: creo un processo padre e un processo figlio.
            if (pid == 0) //Se si tratta del processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
            {
                close(0); //Chiudo il file descriptor di STDIN.
                dup(p1p0[0]); //Duplico il file descriptor dell'estremo di lettura della pipe.
                //Chiudo entrambi gli estremi della pipe p1p0.
                close(p1p0[0]); 
                close(p1p0[1]);
                close(1); //Chiudo il file descriptor di STDOUT.
                dup(p2p0[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
                //Chiudo entrambi gli estremi della pipe p2p0.
                close(p2p0[0]);
                close(p2p0[1]);
                execl("/usr/bin/wc", "wc", NULL); //Eseguo il comando WC.
                return -1;
            }
            else //Se si tratta del processo padre in esecuzione, allora eseguo le seguenti istruzioni.
            {
                //Chiudo p1p0 e l'estremità di scrittura di p2p0.
                close(p1p0[0]);
                close(p1p0[1]);
                close(p2p0[1]);
                //Inizializzo le variabili necessarie per le operazioni seguenti.
                char contenuto_letto[1024]; //Svolgerà la funzione di BUFFER.
                int numero_bytes; 
                int file_descriptor = open("wc.txt", O_WRONLY | O_CREAT, 0777); //Si apre il file in modalità di creazione e scrittura con i permessi totali e si assegna il suo file descriptor in una variabile.
                numero_bytes = read(p2p0[0], contenuto_letto, 1024); //Leggo il contenuto della pipe p2p0.
                write(file_descriptor, contenuto_letto, numero_bytes); //Scrivo nel file wc.txt.
                printf("Ho eseguito la scrittura su file\n");
                //Chiudo sia l'estremità di lettura della pipe, sia il file wc.txt.
                close(p2p0[0]);
                close(file_descriptor);
            }
        }
    }
    else
    {
        printf("Non hai inserito un numero corretto di argomenti. Riprova...\n");
    }
    printf("Per uscire dal programma premere un tasto qualsiasi...");
    fflush(stdin); //Eseguo una pulizia del buffer dello standard input.
    getchar();
    return 0;
}