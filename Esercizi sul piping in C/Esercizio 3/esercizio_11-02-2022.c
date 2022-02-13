/**
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4F
 * @brief Realizzare un programma in cui venga realizzato il piping in C.
 * @version 1.0
 * @date 2022-02-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define GRANDEZZA_STRINGA_INPUT 25
#define GRANDEZZA_STRINGA_OUTPUT 10
#define DIMENSIONE_CANALE_PIPE 2

/**
 * @fn int main(int argc, char *argv[])
 * @brief Esegue tutto il programma in quest'unica funzione.
 * @return Il padre ritorna il valore zero, mentre il figlio il valore -1.
 */
int main(int argc, char *argv[])
{
    printf("\nBenvenuto nel programma!\n");
    if (argc == 2)
    {
        int file;
        pid_t pid;
        char stringa_ingresso[GRANDEZZA_STRINGA_INPUT];
        char risultato[GRANDEZZA_STRINGA_OUTPUT];
        int canale_pipe[DIMENSIONE_CANALE_PIPE];
        int numero_stringhe_trovate = 0;
        file = open(argv[1], O_WRONLY);
        if (file == 0)
        {
            printf("Il percorso del file indicato non è corretto, riprova...\n");
        }
        else
        {
            do
            {
                pipe(canale_pipe);
                printf("Inserisci la stringa che desideri ricercare (per terminare inserisci FINE):");
                scanf("%s", stringa_ingresso);
                if (strcmp(stringa_ingresso, "FINE") != 0)
                {
                    pid = fork();
                    if (pid == 0)
                    {
                        close(1);
                        dup(canale_pipe[1]);
                        close(canale_pipe[0]);
                        close(canale_pipe[1]);
                        execl("/usr/bin/grep", "grep", "-c", stringa_ingresso, argv[1], (char *)0);
                        return -1;
                    }
                    else
                    {
                        wait(&pid);
                        read(canale_pipe[0], risultato, sizeof(risultato));
                        int i;
                        for (i = 0; i < strlen(stringa_ingresso); i++)
                        {
                            stringa_ingresso[i] = toupper(stringa_ingresso[i]);
                        }
                        if (strcmp(stringa_ingresso, "FINE") != 0)
                        {
                            printf("La stringa \"%s\" e' stata trovata %d volte.\n", stringa_ingresso, atoi(risultato));
                            numero_stringhe_trovate += atoi(risultato);
                        }
                    }
                }
            } while (strcmp(stringa_ingresso, "FINE") != 0);
            printf("\nIl numero totale di stringhe trovate e': %d.\n", numero_stringhe_trovate);
        }
    }
    else
    {
        printf("Non hai inserito un numero corretto di argomenti. Riprova...\n");
    }
    return 0;
}
