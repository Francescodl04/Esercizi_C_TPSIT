/**
 * @file esercizio.c
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
            con il flag -o e redirezionare il suo output in wc .

 * @version 0.1
 * @date 2022-04-28
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero argomenti errato.\n");
        exit(0);
    }
    pid_t pid;
    int p1p0[2], p2p0[2], totale = 0;
    char stringa_ricerca[100];
    while (1)
    {
        printf("Inserisci la stringa che desideri ricercare:\n");
        scanf("%s", stringa_ricerca);
        if (strcmp(stringa_ricerca, "fine") != 0)
        {
            pipe(p1p0);
            pid = fork();
            if (pid == 0)
            {
                close(1);
                dup(p1p0[1]);
                close(p1p0[0]);
                close(p1p0[1]);
                execl("/usr/bin/grep", "grep", "-o", stringa_ricerca, argv[1], NULL);
                return -1;
            }
            pipe(p2p0);
            pid = fork();
            if (pid == 0)
            {
                close(0);
                dup(p1p0[0]);
                close(p1p0[0]);
                close(p1p0[1]);
                close(1);
                dup(p2p0[1]);
                close(p2p0[0]);
                close(p2p0[1]);
                execl("/usr/bin/wc", "wc", "-l", NULL); //Questo particolare tipo di WC, con il flag -l, permette di mantenere solamente le righe presenti in un file, senza considerare parole e colonne.
                return -1;
            }
            close(p1p0[0]);
            close(p1p0[1]);
            close(p2p0[1]);
            int parole_lette = 0;
            char buffer[100];
            read(p2p0[0], buffer, sizeof(buffer));
            parole_lette = atoi(buffer);
            printf("La stringa %s è stata letta per %d volte nel file.\n", stringa_ricerca, parole_lette);
            totale += parole_lette;
        }
        else
        {
            printf("Il totale di stringhe trovato è %d.\n", totale);
            exit(0);
        }
    }
    return 0;
}