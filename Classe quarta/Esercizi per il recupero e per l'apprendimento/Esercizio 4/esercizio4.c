/** \file esercizio4.c
 * \author Francesco Di Lena, Classe 4F
 * \date 02/12/2021
 * \version 1.0
 * \brief Scrivi un programma in linguaggio C che:
          - genera due processi padre/figlio;
          - il processo padre legge il nome e cognome dell’utente e lo trasforma con l’iniziale maiuscola e le altre lettere
            minuscole (cioè per esempio inserendo “rossi MARIO” produce “Rossi Mario”);
          - il processo padre scrive il nome così trasformato in un file di testo aperto prima di eseguire la fork;
          - dopo aver completato la scrittura del nome, chiude e rimuove il file creato;
          - contemporaneamente il processo figlio attende 5 secondi e stampa il contenuto del file appena scritto dal pro-
            cesso padre convertendo le parole in maiuscolo.
**/

#include <stdio.h>    //Libreria di standard input/output.
#include <stdlib.h>   //Libreria che contiene funzioni di utilità generale.
#include <unistd.h>   //Libreria di interfaccia con il sistema operativo Unix.
#include <sys/wait.h> //Libreria apposita per le chiamate di sistema, in particolare quelle di attesa.
#include <string.h>   //Libreria che contiene funzioni per la gestione delle stringhe.
#include <ctype.h>    //Libreria che contiene funzioni per la gestione dei caratteri.

/** \fn void trasforma_stringhe(char stringa_da_trasformare[15], int controllo)
 * \param char stringa_da_trasformare[15] : Contiene la stringa che deve essere trasformata
 * \param int controllo : Stabilisce se rendere un carattere maiuscolo o minuscolo.
 * \brief La funzione trasforma_stringhe(char stringa_da_trasformare[15], int controllo) permette di trasformare ogni singolo carattere di una stringa in minuscolo o maiuscolo.
 * \return La funzione è di tipo void, quindi non ritorna nulla.
 **/

void trasforma_stringhe(char stringa_da_trasformare[15], int controllo)
{
    int i;
    for (i = 0; i < strlen(stringa_da_trasformare); i++) //Ripete il ciclo finché la stringa non è terminata. La funzione strlen(char stringa[]) restituisce la lunghezza di una stringa.
    {
        if (i == 0 || controllo == 0)
        {
            stringa_da_trasformare[i] = toupper(stringa_da_trasformare[i]); //La funzione toupper(char carattere) permette di rendere un carattere maiuscolo.
        }
        else if (controllo == -1)
        {
            stringa_da_trasformare[i] = tolower(stringa_da_trasformare[i]); //La funzione tolower(char carattere) permette di rendere un carattere maiuscolo.
        }
    }
}

/** \fn int main()
 * \param FILE *file : Puntatore al file.
 * \param char nome[15] : Contiene il nome della persona inserito da tastiera.
 * \param char cognome[15] : Contiene il cognome della persona inserito da tastiera.
 * \param char percorso_file[20] : Contiene il percorso del file in cui verrà salvato il nome e cognome della persona.
 * \param pid_t pid_processo : PID del processo in esecuzione.
 * \brief La funzione main() permette la creazione di un processo figlio attraverso la funzione fork() e mostra a schermo il PID del processo padre e del figlio.
 * \return La funzione ritorna il valore intero 0.
 **/

int main()
{
    FILE *file;
    char nome[15], cognome[15], percorso_file[20] = "output.txt";
    pid_t pid_processo;
    printf("Benvenuto nel programma!\n");
    printf("Inserisci il nome:\n");
    scanf("%s", nome);
    printf("Inserisci il cognome:\n");
    scanf("%s", cognome);
    file = fopen(percorso_file, "w+"); //La funzione fopen() permette di aprire un file (in questo caso in scrittura e creazione in caso della sua assenza), e restituire un puntatore al file.
    pid_processo = fork();             //La funzione fork() permette di eseguire il biforcamento di un processo: si crea quindi un processo padre e un figlio.
    if (pid_processo == 0)             //Se il processo in esecuzione è il figlio, quindi la fork() restituisce 0, allora esegue le seguenti istruzioni.
    {
        printf("Ora e' in esecuzione il processo figlio (PID: %d)...\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
        sleep(5);                                                                   //La funzione sleep(int secondi) permette di sospendere il processo per il tempo (in secondi) che le viene passato in argomento.
        fscanf(file, "%s %s", nome, cognome);                                       //La funzione fscanf() permette di eseguire la lettura del contenuto di un file e di effettuare il suo salvataggio all'interno delle stringhe locali.
        trasforma_stringhe(nome, 0);
        trasforma_stringhe(cognome, 0);
        printf("La persona inserita si chiama %s %s", nome, cognome);
        exit(0); //La funzione exit(int status) permette di uscire dal processo (in questo caso il figlio).
    }
    else //Nell'altro caso il processo è il padre.
    {
        trasforma_stringhe(nome, -1);
        trasforma_stringhe(cognome, -1);
        printf("Ora e' in esecuzione il processo padre (PID: %d)...\n", getpid()); //Qui viene effettuata una visualizzazione a schermo. La funzione getpid() permette di ottenere il PID del processo che la esegue.
        fprintf(file, "%s %s", nome, cognome);                                     //La funzione fprintf() permette di scrivere su un file il contenuto di variabili locali.
        fclose(file);                                                              //La funzione fclose(FILE *file) permette di chiudere un file.
        remove(percorso_file);                                                     //La funzione remove(FILE *file) permette di eliminare un file.
    }
    return 0;
}