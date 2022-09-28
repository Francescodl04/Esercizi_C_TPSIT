/**
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4F
 * @brief  Scrivere un programma concorrente che realizzi il seguente comando:

            cat file.txt | wc

            il processo p2 deve rimandare l'output di wc al padre, il quale lo scriverà
            su un file chiamato wc.txt
            il nome del file "file.txt" deve essere passato come argomento in argv[1]

 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    printf("Benvenuto nel programma!\n");
    if (argc != 2)
    {
        printf("Non hai inserito un numero corretto di argomenti, riprova...\n");
        exit(0);
    }
    pid_t pid;
    int p1p2[2], p2p0[2];
    pipe(p1p2); //Creo il canale pipe fra il processo uno e il processo due.
    pipe(p2p0); //Creo il canale pipe fra il processo due e il processo zero (padre).
    pid = fork(); //Divido il processo in processo padre (zero) e processo figlio (uno).
    if (pid == 0)
    {
        pid = fork();
        if (pid == 0)
        {
            close(1); //Chiudo lo standard output.
            dup(p1p2[1]); //Duplico il lato di scrittura della pipe, che viene posta al posto dello standard output.
            //Chiudo gli estremi della prima pipe.
            close(p1p2[0]);
            close(p1p2[1]);
            //Chiudo anche gli estremi della seconda pipe, perché altrimenti rimarrebbe aperta in questo processo.
            close(p2p0[0]);
            close(p2p0[1]);
            execl("/usr/bin/cat", "cat", argv[1], NULL); //Eseguo il comando CAT.
            return -1;
        }
        close(0); //Chiudo lo standard input.
        dup(p1p2[0]); //Duplico il lato di lettura della pipe e lo metto al posto dello standard input.
        //Chiudo gli estremi della prima pipe.
        close(p1p2[0]); 
        close(p1p2[1]);
        close(1); //Chiudo lo standard output.
        dup(p2p0[1]); //Duplico il lato di scrittura della seconda pipe, che viene messo al posto dello standard output.
        //Chiudo entrambi gli estremi della pipe perché non mi serve più.
        close(p2p0[0]);
        close(p2p0[1]);
        execl("/usr/bin/wc", "wc", NULL); //Eseguo il comando WC.
        return -1;
    }
    //Chiudo gli estremi della prima pipe e il lato di scrittura della seconda.
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[1]);
    int nread = 0; //Variabile che conterrà il numero di byte letti dalla pipe.
    char buffer[1024]; //Stringa in cui verrà inserito il contenuto letto dalla pipe.
    int fd = open("wc.txt", O_CREAT | O_WRONLY, 0777); //Apro il file in cui dovrò scrivero il contenuto della pipe.
    while ((nread = read(p2p0[0], buffer, 1024)) > 0) //Eseguo la lettura dalla pipe e conseguentemente la scrittura sul file aperto.
    {
        write(fd, buffer, nread);
    }
    close(p2p0[0]); //Chiudo il lato di lettura della seconda pipe.
    close(fd); //Chiudo il file su cui ho scritto il contenuto letto dalla pipe.
    printf("Scrittura completata con successo.\n");
    return 0;
}