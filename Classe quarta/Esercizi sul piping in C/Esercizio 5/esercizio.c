/**
 * @file esercizio.c
 * @author Francesco Di Lena, classe 4F
 * @brief Un’applicazione multiprocesso in C deve presentare la seguente interfaccia:

            controlloFatture nomeFileFatture
            dove nomeFileFatture è un nome assoluto di file.

            A questo fine, l’addetto dell’azienda deve verificare, sul file passato
            come parametro, se un cliente ha ancora delle fatture in sospeso oppure se
            le ha pagate tutte.

            Nel file passato come parametro sono memorizzate tutte le fatture, una per
            ogni riga. Ogni riga è composta dal nome del cliente (un codice di 5 caratteri
            alfanumerico che identifica univocamente ogni cliente), da un campo che
            contiene la stringa “pagato” per le fatture saldate oppure “insoluto”
            per quelle ancora insolute, più altri campi con altre informazioni.

            L’addetto dell’azienda inserisce a terminale il codice dei clienti (uno alla
            volta) di cui vuole controllare lo stato dei pagamenti. Per ogni cliente
            inserito, l’applicazione deve visualizzare il nome del cliente stesso e il
            numero di fatture di tale cliente che risultano ancora da pagare.

            Quando l’applicazione termina,a causa dell’inserimento della stringa “esci”,
            il programma deve visualizzare il numero totale di richieste di servizio
            eseguite fino a quel momento.
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
        printf("Numero argomenti errato.\n");
        exit(0);
    }
    while (1)
    {
        pid_t pid;
        int p1p0[2], totale;
        char stringa_inserita[100];
        printf("Inserisci il nome del cliente:\n");
        scanf("%s", stringa_inserita);
        if (strcmp(stringa_inserita, "esci") != 0)
        {
            for (int i = 0; i < strlen(stringa_inserita); i++)
            {
                stringa_inserita[i] = toupper(stringa_inserita[i]);
            }
            pipe(p1p0);
            pid = fork();
            if (pid == 0)
            {
                close(1);
                dup(p1p0[1]);
                close(p1p0[0]);
                close(p1p0[1]);
                execl("/usr/bin/grep", "grep", "-c", strcat(stringa_inserita, " insoluto"), argv[1], NULL);
                return -1;
            }
            close(p1p0[1]);
            char buffer[100];
            read(p1p0[0], buffer, sizeof(buffer));
            close(p1p0[0]);
            int insoluti_cliente=atoi(buffer);
            printf("Il cliente %s ha %d insoluti.\n", stringa_inserita, insoluti_cliente);
            totale++;
        }
        else
        {
            printf("Il numero totale di richieste di servizio è stato %d.\n", totale);
            exit(0);
        }
    }
    return 0;
}