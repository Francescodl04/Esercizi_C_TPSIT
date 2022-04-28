/**
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4F
 * @brief Il file.txt rappresenta le fatture dell’ultimo mese della ditta ProgrammatoriHero srl
            e contiene 3 campi: codice, “pagato” o “insoluto”, l’importo

            Si vuole realizzare un programma concorrente in linguaggio C che mostri a video l'importo totale delle fatture emesse.

            Si usi la seguente procedura:
            Si generi un processo figlio P1 che legge il file e lo manda al processo P2 il quale
            estrapola la terza colonna del file, e la manda al processo P0.
            Il processo P0 riceve quindi tutti gli importi, ne calcola il totale e lo mostra a video.

            Note operative
            Il processo P1 usi il comando cat per mostrare il contenuto del file e inviarlo a P2
            Il processo P2 usi il comando: awk '{print $3}' per estrapolare la terza colonna
            Il processo P2 deve inviare al processo P0 la terza colonna
            Il processo P0 deve leggere in input tutti i valori e per ogni lettura deve incrementare la variabile accumulatore “totale”

            Osservazione:
            strncat(strimporto, &buffer[0], sizeof(buffer[0]))
            Aggiunge in coda alla stringa strimporto il carattere buffer[0] la cui dimensione è sizeof(buffer[0])

            Osservazione:
            char *ptr; strtod(strimporto, &ptr);
            converte la stringa strimporto in double.

            Osservazione:
            strimporto[0] = '\0';
            Pone in posizione 0 di una stringa il carattere terminatore, in questo modo si resetta a livello logico una stringa
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
    if (argc != 2)
    {
        printf("Numero argomenti non corretto.\n");
        exit(0);
    }
    pid_t pid;
    int p1p2[2], p2p0[2];
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
    pipe(p2p0);
    pid = fork();
    if (pid == 0)
    {
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        close(p1p2[1]);
        close(1);
        dup(p2p0[1]);
        close(p2p0[0]);
        close(p2p0[1]);
        execl("/usr/bin/awk", "awk", "{print $3}", NULL);
        return -1;
    }
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[1]);
    char buffer[1];
    char stringa_valore_parziale[100];
    double totale = 0;
    int numero_bytes_letti = 0;
    while ((numero_bytes_letti = read(p2p0[0], buffer, 1)) > 0)
    {
        if (buffer[0] != '\n')
        {
            strncat(stringa_valore_parziale, &buffer[0], sizeof(buffer[0]));
        }
        else
        {
            char *puntatore;
            totale += strtod(stringa_valore_parziale, &puntatore);
            stringa_valore_parziale[0] = '\0';
        }
    }
    printf("Il totale delle fatture è di %.2f euro.\n", totale);
    return 0;
}