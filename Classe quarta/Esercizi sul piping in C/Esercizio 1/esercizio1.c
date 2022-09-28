/**
 * @file esercizio1.c
 * @author Francesco Di Lena, classe 4F
 * @brief Scrivere il codice di un programma in C che esegua il comando cat file.txt | more
 * @version 0.1
 * @date 2022-02-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

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
    pid_t pid;
    int p1p0[2]; //Inizializzo l'array che conterrà i due file descriptor che rappresenteranno i due estremi del canale pipe.
    pipe(p1p0); //Creo il canale pipe.
    pid = fork(); //Eseguo la fork: creo un processo padre e un processo figlio.
    if (pid == 0) //Se si tratta del processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
    {
        close(1); //Chiudo il file descriptor di STDOUT.
        dup(p1p0[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
        //Chiudo entrambi gli estremi della pipe.
        close(p1p0[0]);
        close(p1p0[1]);
        execl("/usr/bin/cat", "cat", "file.txt", NULL); //Eseguo il comando CAT.
        return -1;
    }
    else //Se si tratta del processo padre in esecuzione, allora eseguo le seguenti istruzioni.
    {
        pid = fork(); //Eseguo la fork: creo un processo padre e un processo figlio.
        if (pid == 0) //Se si tratta del processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
        {
            close(0); //Chiudo il file descriptor di STDIN.
            dup(p1p0[0]); //Duplico il file descriptor dell'estremo di lettura della pipe.
            //Chiudo entrambi gli estremi della pipe.
            close(p1p0[0]);
            close(p1p0[1]);
            execl("/usr/bin/more", "more", "-f", NULL); //Eseguo il comando MORE, che mostrerà il suo output nella shell.
            return -1;
        }
        else //Se si tratta del processo padre in esecuzione, allora eseguo le seguenti istruzioni.
        {
            //Chiudo entrambi gli estremi della pipe.
            close(p1p0[0]);
            close(p1p0[1]);
            wait(&pid); //Attendo che il processo figlio venga eseguito.
            wait(&pid);
            printf("\n\nPer uscire dal programma premi un tasto qualsiasi...");
            fflush(stdin); //Eseguo una pulizia del buffer dello standard input.
            getchar();
            return 0;
        }
    }
}