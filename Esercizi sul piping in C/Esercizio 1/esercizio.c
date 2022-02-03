/** 
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4 F
 * @date 03/02/2022
 * @version 1.0
 * @brief Si realizzi un programma C in cui vengono creati tre processi: un padre e due figli. Attraverso il piping in C e la funzione execlp(), con il programma
 * \n si deve ottenere un risultato simile al comando cat file.txt | wc.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/** 
 * @fn int main(int argc, char *argv[])
 * @param int argc : indica il numero di argomenti con cui è stato invocato il programma.
 * @param char *argv[]: array degli argomenti con cui è stato invocato il programma.
 * @param int file_descriptor[2]: array usato per il contenimento dei file descriptor durante l'uso di un canale PIPE.
 * @param pid_t pid : variabile usata per contenere il PID del processo in esecuzione in caso di fork().
 * @brief La funzione main(), l'unica locale che compone il programma, svolge tutti i compiti prefissati e descritti dalla consegna.
 * @return La funzione ritorna il valore intero 0 (zero).
**/

int main(int argc, char *argv[])
{
    int file_descriptor[2];
    pid_t pid;
    printf("\nBenvenuto nel programma!\n");
    pipe(file_descriptor);
    pid = fork(); //Crea il primo processo figlio.
    if (pid == 0)
    {
        printf("Adesso eseguirò il comando CAT:\n");
        close(1);                //Chiude STDOUT.
        dup(file_descriptor[1]); //Inserisce al posto di STDOUT il file descriptor.
        //Chiude entrambi gli estremi del canale PIPE.
        close(file_descriptor[0]);
        close(file_descriptor[1]);
        execlp("/bin/cat", "cat", "file.txt", (char *)0); //Esegue il comando CAT.
    }
    else
    {
        pid = fork(); //Crea il secondo progetto figlio.
        if (pid == 0)
        {
            printf("Adesso eseguirò il comando WC:\n");
            close(0);                //Chiude STDIN.
            dup(file_descriptor[0]); //Inserisce al posto di STDIN il file descriptor.
            //Chiude entrambi gli estremi del canale PIPE.
            close(file_descriptor[0]);
            close(file_descriptor[1]);
            execlp("/bin/wc", "wc", (char *)0); //Esegue il comando WC.
        }
        else
        {
            printf("Per uscire dal programma premi un tasto qualsiasi...\n");
            getchar();
        }
    }
    //Chiude entrambi gli estremi del canale PIPE.
    close(file_descriptor[0]);
    close(file_descriptor[1]);
    return 0;
}