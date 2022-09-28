/**
 * @file esercizio3.c
 * @author Francesco Di Lena, classe 4F
 * @brief Si scriva un’applicazione concorrente che presenti la seguente interfaccia:
    cercaStringhe FileIn
    dove FileIn è un nome assoluto di file.
    L’applicazione deve contare il numero di volte in cui un insieme di stringhe
    che l’utente inserisce da terminale (una alla volta) compaiono all’interno
    del file passato come parametro in argv[1].
    Se in una riga del file una parola compare più volte, al fine del conteggio,
    considerare solamente la prima occorrenza.
    L’applicazione termina quando l’utente inserisce la stringa “fine”.
    L’applicazione deve visualizzare il numero di volte in cui ogni stringa
    compare nel file e anche, al termine dell’esecuzione, il numero totale di
    stringhe trovate nel file.

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
    if (argc != 2) //Controlla che il numero di argomenti inseriti sia corretto.
    {
        printf("Non hai inserito il numero corretto di argomenti. Riprova...\n");
    }
    else
    {
        pid_t pid;
        int p1p0[2]; //Viene inizializzato l'array che conterrà i file descriptor della pipe.
        char stringa[100], numero_stringhe_trovate[100]; //Variabili che serviranno successivamente per memorizzare la stringa inserita dall'utente e il numero di stringhe trovate da una singola ricerca.
        int numero_totale = 0; //Numero totale di stringhe trovate in tutte le ricerche.
        do
        {
            pipe(p1p0); //Viene creato il canale pipe.
            printf("Inserisci la stringa che desideri ricercare:\n");
            scanf("%s", stringa);
            if (strcmp(stringa, "fine") != 0) //Se la stringa è diversa da "fine", allora esegue le seguenti istruzioni.
            {
                pid = fork(); //Eseguo la fork: creo un processo padre e un processo figlio.
                if (pid == 0) //Se si tratta del processo figlio in esecuzione, allora eseguo le seguenti istruzioni.
                {
                    close(1); //Chiudo il file descriptor di STDOUT.
                    dup(p1p0[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
                    //Chiudo entrambi gli estremi della pipe.
                    close(p1p0[0]);
                    close(p1p0[1]);
                    execl("/usr/bin/grep", "grep", "-c", stringa, argv[1], NULL); //Eseguo il comando GREP.
                    return -1;
                }
                else //Se si tratta del processo padre in esecuzione, allora eseguo le seguenti istruzioni.
                {
                    read(p1p0[0], numero_stringhe_trovate, sizeof(numero_stringhe_trovate)); //Leggo il contenuto della pipe e lo pongono nella variabile numero_stringhe_trovate.
                    printf("La stringa %s è stata trovata %d volte.\n", stringa, atoi(numero_stringhe_trovate)); //Mostro a schermo i risultati, trasformando il contenuto letto dalla pipe in un integer.
                    numero_totale += atoi(numero_stringhe_trovate); //Sommo il numero di stringhe trovate al totale.
                }
            }
            //Chiude in ogni caso gli estremi della pipe.
            close(p1p0[0]);
            close(p1p0[1]);
        } while (strcmp(stringa, "fine") != 0);
        printf("Il numero totale di stringhe trovate è %d.\n", numero_totale);
    }
    return 0;
}