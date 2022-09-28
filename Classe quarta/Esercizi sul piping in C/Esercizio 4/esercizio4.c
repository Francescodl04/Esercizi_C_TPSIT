/**
 * @file esercizio4.c
 * @author Francesco Di Lena, classe 4F
 * @brief Si scriva un’applicazione concorrente che presenti la seguente interfaccia:

          cercaStringhe FileIn

        dove FileIn è un nome assoluto di file.
        L’applicazione deve contare il numero di volte in cui un insieme di stringhe
        che l’utente inserisce da terminale (una alla volta) compaiono all’interno
        del file passato come parametro in argv[1].
        L’applicazione termina quando l’utente inserisce la stringa “fine”.

        L’applicazione deve visualizzare il numero di volte in cui ogni stringa
        compare nel file e anche, al termine dell’esecuzione, il numero totale di
        stringhe trovate nel file.

        L'applicazione dovrà tenere conto dell'eventuale molteplicità di una parola
        dentro alla stessa stringa, per fare questo si consiglia di invocare grep
        con il flag -o e redirezionare il suo output in wc.

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
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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
    if (argc != 2) // Controlla che il numero di argomenti inseriti sia corretto.
    {
        printf("Non hai inserito il numero corretto di argomenti. Riprova...\n");
    }
    else
    {
        char stringa_inserita[100]; //Questa variabile conterrà la stringa che verrà inserita dall'utente.
        int p1p2[2], p2p0[2], numero_totale_stringhe_trovate = 0; //I primi due array serviranno per contenere i file descriptor delle due pipe che successivamente saranno create, mentre la terza variabile servirà per tenere il conto del totale di stringhe trovate e visualizzate alla fine del programma.
        pid_t pid; //Variabile che conterrà il pid del processo che sta eseguendo il codice.
        do
        {
            printf("Inserisci la stringa che desideri ricercare nel file:\n");
            scanf("%s", stringa_inserita);
            if (strcmp(stringa_inserita, "fine") != 0)
            {
                //Creo i due canali pipe.
                pipe(p1p2);
                pipe(p2p0);
                pid = fork(); //Eseguo la fork: il processo si suddivide in processo padre e processo figlio.
                if (pid == 0) //Se è il processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
                {
                    close(1); //Chiudo il file descriptor di STDOUT.
                    dup(p1p2[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
                    //Chiudo entrambi gli estremi della pipe.
                    close(p1p2[0]);
                    close(p1p2[1]);
                    execl("/usr/bin/grep", "grep", "-o", stringa_inserita, argv[1], NULL); //Eseguo il comando grep -o.
                    return -1;
                }
                else //Se è il processo padre in esecuzione, allora eseguo le seguenti istruzioni.
                {
                    pid = fork(); //Eseguo la fork: il processo si suddivide in processo padre e processo figlio.
                    if (pid == 0) //Se è il processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
                    {
                        close(0); //Chiudo il file descriptor di STDIN.
                        dup(p1p2[0]); //Duplico il file descriptor dell'estremo di lettura della prima pipe.
                        //Chiudo entrambi gli estremi della prima pipe.
                        close(p1p2[0]);
                        close(p1p2[1]);
                        close(1); //Chiudo il file descriptor di STDOUT.
                        dup(p2p0[1]); //Duplico il file descriptor dell'estremo di scrittura della seconda pipe.
                        //Chiudo entrambi gli estremi della seconda pipe.
                        close(p2p0[0]);
                        close(p2p0[1]);
                        execl("/usr/bin/wc", "wc", "-l", NULL); //Eseguo il comando WC -l.
                        return -1;
                    }
                    else //Se è il processo padre in esecuzione, allora eseguo le seguenti istruzioni.
                    {
                        //Chiudo entrambi gli estremi della prima pipe.
                        close(p1p2[0]);
                        close(p1p2[1]);
                        char numero_stringhe_file[100]; //Variabile che conterrà il numero di stringhe trovate all'interno di un file.
                        close(p2p0[1]); //Chiudo l'estremo di scrittura della seconda pipe.
                        read(p2p0[0], numero_stringhe_file, sizeof(numero_stringhe_file)); //Leggo il contenuto della seconda pipe.
                        printf("La stringa \"%s\" è stata trovata nel file %d volte.\n", stringa_inserita, atoi(numero_stringhe_file));
                        numero_totale_stringhe_trovate += atoi(numero_stringhe_file);
                        close(p2p0[0]); //Chiudo l'estremo di lettura della seconda pipe.
                    }
                }
            }
        } while (strcmp(stringa_inserita, "fine") != 0);
    }
    return 0;
}