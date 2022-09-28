/**
 * @file esercizio7.c
 * @author Francesco Di Lena, classe 4F
 * @brief Esercizio 7 sulla programmazione di sistema (vedi testo esercizio su repository GitHub).
 * @version 0.1 (lettura da file)
 * @date 2022-03-04
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

// traceroute google.com | awk '{print $4}' | tail -n +2

int main(int argc, char *argv[])
{
    printf("Benvenuto nel programma!\n");
    if (argc != 2)
    {
        printf("Non hai inserito un numero corretto di argomenti. Riprova...\n");
    }
    else
    {
        pid_t pid;
        int p1p2[2], p2p3[2], p3p0[2];
        double totale = 0;
        char contenuto_letto[1], *puntatore, stringa_importo[100];
        pipe(p1p2);
        pid = fork();
        if (pid == 0)
        {
            close(1);
            dup(p1p2[1]);
            close(p1p2[0]);
            close(p1p2[1]);
            execl("/usr/bin/cat", "cat", argv[1], NULL);
            return -1;
        }
        else
        {
            pipe(p2p3);
            pid = fork();
            if (pid == 0)
            {
                close(0);
                dup(p1p2[0]);
                close(p1p2[0]);
                close(p1p2[1]);
                close(1);
                dup(p2p3[1]);
                close(p2p3[0]);
                close(p2p3[1]);
                execl("/usr/bin/awk", "awk", "{print $4}", NULL);
                return -1;
            }
            else
            {
                pipe(p3p0);
                close(p1p2[0]);
                close(p1p2[1]);
                pid = fork();
                if (pid == 0)
                {
                    close(0);
                    dup(p2p3[0]);
                    close(p2p3[0]);
                    close(p2p3[1]);
                    close(1);
                    dup(p3p0[1]);
                    close(p3p0[0]);
                    close(p3p0[1]);
                    execl("/usr/bin/tail", "tail", "-n", "+2", NULL);
                    return -1;
                }
                else
                {
                    close(p2p3[0]);
                    close(p2p3[1]);
                    close(p3p0[1]);
                    while ((read(p3p0[0], contenuto_letto, 1)) > 0)
                    {
                        if (contenuto_letto[0] != '\n')
                        {
                            strncat(stringa_importo, &contenuto_letto[0], sizeof(contenuto_letto[0]));
                        }
                        else if (strcmp(stringa_importo, "*") != 0)
                        {
                            totale += strtod(stringa_importo, &puntatore);
                            stringa_importo[0] = '\0';
                        }
                    }
                    close(p3p0[0]);
                    printf("Il totale del tempo impiegato per raggiungere la destinazione è di %.2lf ms.\n", totale);
                    return 0;
                }
            }
        }
    }
}