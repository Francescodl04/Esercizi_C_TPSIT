/**
 * @file esercizio.c
 * @author your name (you@domain.com)
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
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int numero_parole_trovate_totale = 0;
    if (argc != 2)
    {
        printf("Non hai inserito un numero corretto di argomenti, riprova...\n");
        exit(0);
    }
    do
    {
        pid_t pid;
        int p1p0[2];
        char stringa_da_ricercare[100];
        printf("Inserisci la stringa che desideri ricercare:\n");
        scanf("%s", stringa_da_ricercare);
        if (strcmp(stringa_da_ricercare, "fine") != 0)
        {
            int numero_parziale_parole_trovate = 0;
            pipe(p1p0);
            pid = fork();
            if (pid == 0)
            {
                close(1);
                dup(p1p0[1]);
                close(p1p0[0]);
                close(p1p0[1]);
                execl("/usr/bin/grep", "grep", "-c", stringa_da_ricercare, argv[1], NULL); //La funzione grep -c permette di contare in quante linee è presente una stringa, quindi non conta tutte le occorrenze.
                return -1;
            }
            close(p1p0[1]);
            char buffer[100];
            read(p1p0[0], buffer, 100);
            close(p1p0[0]);
            numero_parziale_parole_trovate = atoi(buffer);
            printf("La stringa \"%s\" è stata trovata %d volte nel file.\n", stringa_da_ricercare, numero_parziale_parole_trovate);
            numero_parole_trovate_totale += numero_parziale_parole_trovate;
        }
        else
        {
            printf("Il numero totale di parole trovate è %d.\n", numero_parole_trovate_totale);
            exit(0);
        }

    } while (1);
    return 0;
}