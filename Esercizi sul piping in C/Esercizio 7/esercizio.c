/**
 * @file esercizio.c
 * @author your name (you@domain.com)
 * @brief Sfruttando la programmazione concorrente si vuole realizzare un programma che legga il file, prelevi la prima delle tre colonne che mostra il tempo di risposta in nano secondi
            e calcoli quindi il tempo totale di richiesta.

            Note operative:
            p0 crea il processo p1 che chiama il comando cat e inoltra il suo output a p2
            p2 estrapola la quarta colonna e la inoltra a p3
            p3 chiama il comando tail -n +2 per escludere la prima riga, fatto cio inoltra l'output a p0
            p0 somma tutti i tempi di accesso e al termine mostra il tempo totale che un pacchetto ha impiegato lungo il percorso

            Osservazione importante:
            Al fine di rendere l'esercizio facilmente testabile si è deciso di utilizzare il file f.txt in modo da avere un risultato riproducibile. Dopo aver testato il software si consiglia di sostituire al comando cat il comando traceroute in modo da realizzare un software il cui funzionamento è reale.
            Esempio di utilizzo reale: $./a.out google.com
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero degli argomenti errato.\n");
        exit(0);
    }
    int p1p2[2], p2p3[2], p3p0[2];
    pipe(p1p2);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(1);
        dup(p1p2[1]);
        close(p1p2[0]);
        close(p1p2[1]);
        execl("/usr/sbin/traceroute", "traceroute", argv[1], NULL);
        return -1;
    }
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
        execl("/usr/bin/awk", "awk", "{print $ + 4}", NULL);
    }
    pipe(p3p0);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);
        close(p1p2[1]);
        close(0);
        dup(p2p3[0]);
        close(p2p3[0]);
        close(p2p3[1]);
        close(1);
        dup(p3p0[1]);
        close(p3p0[0]);
        close(p3p0[1]);
        execl("/usr/bin/tail", "tail", "-n", "+2", NULL);
    }
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p3[0]);
    close(p2p3[1]);
    close(p3p0[1]);
    char buffer[1];
    char numero[100];
    double somma = 0;
    while (read(p3p0[0], buffer, sizeof(buffer)) > 0)
    {
        if (buffer[0] != '\n')
        {
            strncat(numero, &buffer[0], sizeof(buffer[0]));
        }
        else
        {
            char *puntatore;
            somma += strtod(numero, &puntatore);
        }
    }
    printf("Il risultato della somma dei tempi è %.3f ms.\n", somma);
    return 0;
}