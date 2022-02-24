/**
 * @file esercizio5.c
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
 * @date 2022-02-24
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

/**
 * @brief La funzione main esegue tutte le istruzioni che consentono di risolvere l'esercizio.
 * 
 * @param int argc : indica il numero di argomenti passati all'invocazione del programma. 
 * @param char *argv[] : contiene gli argomenti passati all'invocazione del programma.
 * @return La funzione ritorna il valore intero 0 nel padre e -1 nei figli nel caso, in questi ultimi, che ci sia stato un errore. 
 */

int main(int argc, char *argv[])
{
    printf("Benvenuto nel programma!\n");
    if (argc != 2)
    {
        printf("Non hai inserito un numero corretto di argomenti. Riprova...\n");
    }
    else
    {
        char stringa_ingresso[10]; //Variabile che conterrà la stringa posta in ingresso da parte dell'utente per la ricerca.
        pid_t pid; //Conterrà il pid del processo che starà eseguendo il programma.
        int p1p0[2], numero_totale_richieste = 0; //Il primo array conterrà i due file descriptor che corrisponderanno ai due estremi della pipe, mentre la seconda variabile conterrà il numero totale di richieste effettuate.
        do
        {
            printf("Inserisci il nome dell'utente che desideri ricercare:\n");
            scanf("%s", stringa_ingresso);
            int i;
            for (i = 0; i < sizeof(stringa_ingresso); i++) //Con questo ciclo for faccio diventare tutti i caratteri che compongono la stringa in ingresso maiuscoli.
            {
                stringa_ingresso[i] = toupper(stringa_ingresso[i]);
            }
            if (strcmp(stringa_ingresso, "ESCI") != 0)
            {
                pipe(p1p0); //Creo il canale pipe.
                pid = fork(); //Eseguo il fork: divido il processo in processo padre e processo figlio.
                if (pid == 0) //Se si sta eseguendo il processo figlio, allora esegue le seguenti istruzioni.
                {
                    close(1); //Chiudo il file descriptor del STDOUT.
                    dup(p1p0[1]); //Duplico il file descriptor dell'estremo di scrittura della pipe.
                    //Chiudo entrambi gli estremi della pipe.
                    close(p1p0[0]);
                    close(p1p0[1]);
                    execl("/usr/bin/grep", "grep", "-c", strcat(stringa_ingresso, " insoluto"), argv[1], (char *)0); //Eseguo il comando GREP -c.
                    return -1;
                }
                else //Se si sta eseguendo il processo padre, allora esegue le seguenti istruzioni.
                {
                    char numero_insoluti_trovati[64]; //Variabile che conterrà il numero degli insoluti trovati all'interno del file.
                    close(p1p0[1]); //Chiudo l'estremo di scrittura della pipe.
                    read(p1p0[0], numero_insoluti_trovati, sizeof(numero_insoluti_trovati)); //Leggo il contenuto della pipe e lo pongo in numero_insoluti_trovati.
                    if (atoi(numero_insoluti_trovati) == 0) //Se il cliente non ha insoluti, allora visualizza a schermo la seguente stringa.
                    {
                        printf("Non è stato trovato nessun insoluto del cliente %s.\n", stringa_ingresso);
                    }
                    else //Se il cliente ha uno o più insoluti, allora visualizza a schermo la seguente stringa.
                    {
                        printf("Il cliente %s ha %d insoluti.\n", stringa_ingresso, atoi(numero_insoluti_trovati));
                    }
                    close(p1p0[0]); //Chiudo l'estremo di lettura della pipe.
                    numero_totale_richieste++; //Incremento di uno il numero di richieste.
                }
            }
            else
            {
                printf("Il numero totale di richieste è stato %d.\n", numero_totale_richieste);
            }
        } while (strcmp(stringa_ingresso, "ESCI") != 0);
    }
    return 0;
}