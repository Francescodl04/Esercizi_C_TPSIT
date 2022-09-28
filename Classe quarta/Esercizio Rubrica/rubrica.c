/** @file rubrica.c
  @author Francesco Di Lena
  @version 1.0
  @date 18/11/2021
  @brief Il programma esegue la gestione di una semplice rubrica presente all'interno di un file di testo (.txt) il cui percorso viene indicato nell'invocazione del programma.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** @param struct Contatto_T Viene inizializzata la struct Contatto_T per contenere le informazioni di un contatto telefonico, ovvero nome, cognome e numero di telefono. **/
typedef struct
{
    char nome[100];
    char cognome[100];
    char numero_telefono[10];

} Contatto_T;

/** @fn int acquisci_rubrica(char percorso_file[200], Contatto_T c[100]).
 * @brief Permette di effettuare la lettura del file che contiene la rubrica, inserire le informazioni all'interno di un array e restituire il numero di contatti.
 * @param char percorso_file [200]: indica dove si trova il file di input
 * @param Contatto_T c [100]: puntatore alle variabili presenti all'interno dell'omonima struct
 * @return int numero_contatti: ritorna il numero di contatti presenti all'interno del file in input
 **/
int acquisci_rubrica(char percorso_file[200], Contatto_T c[100])
{
    FILE *file_input;
    file_input = fopen(percorso_file, "r");
    int i, numero_contatti = -1;
    for (i = 0; !feof(file_input); i++)
    {
        numero_contatti++;
        fscanf(file_input, "%s %s %s", &c[i].nome, &c[i].cognome, &c[i].numero_telefono);
    }
    fclose(file_input);
    return numero_contatti;
}

/** @fn int ricerca_contatto(Contatto_T c[100], char numero_telefono[100], int numero_contatti)
 * @brief Permette di effettuare la ricerca di un carattere in base al suo numero di telefono
 * @param Contatto_T c [100]: puntatore alle variabili presenti all'interno dell'omonima struct
 * @param int numero_telefono [100]: il numero di telefono ricercato
 * @param int numero_contatti: il numero di contatti presenti nella rubrica
 * @return int indice_ricerca: ritorna l'indice, cioè la posizione all'interno dell'array Contatto_T, dell'elemento ricercato
 **/

int ricerca_contatto(Contatto_T c[100], char numero_telefono[100], int numero_contatti)
{
    int i, indice_ricerca = -1;
    for (i = 0; i < numero_contatti + 1; i++)
    {
        if (strcmp(c[i].numero_telefono, numero_telefono) == 0)
        {
            indice_ricerca = i;
        }
    }
    return indice_ricerca;
}

/** @fn void elimina_contatto(char percorso_file[200], Contatto_T c[100], int indice_contatto_da_eliminare, int numero_contatti)
 * @brief Permette di effettuare l'eliminazione di un contatto e il successivo salvataggio della rubrica all'interno del file
 * @param char percorso_file [200]: indica dove si trova il file di input
 * @param Contatto_T c [100]: puntatore alle variabili presenti all'interno dell'omonima struct
 * @param int indice_contatto_da_eliminare: l'indice, cioè la posizione all'interno dell'array Contatto_T, del contatto da eliminare
 * @param int numero_contatti: il numero di contatti presenti nella rubrica
 * @return Non ritorna nulla, visto che la funzione è void
 **/

void elimina_contatto(char percorso_file[200], Contatto_T c[100], int indice_contatto_da_eliminare, int numero_contatti)
{
    FILE *file_output;
    file_output = fopen(percorso_file, "w+");
    char contenuto_output[200];
    int i;
    for (i = 0; i < numero_contatti + 1; i++)
    {
        if (i != indice_contatto_da_eliminare)
        {
            char temp[100];
            sprintf(temp, "%s %s %s\n", c[i].nome, c[i].cognome, c[i].numero_telefono);
            strcat(contenuto_output, temp);
        }
    }
    fprintf(file_output, "%s", contenuto_output);
    fclose(file_output);
}

/** @fn void aggiungi_contatto(char percorso_file[200], Contatto_T c[100], int numero_contatti)
 * @brief Permette di effettuare l'aggiunta di un contatto e il successivo salvataggio della rubrica all'interno del file
 * @param char percorso_file [200]: indica dove si trova il file di input
 * @param Contatto_T c [100]: puntatore alle variabili presenti all'interno dell'omonima struct
 * @param int numero_contatti: il numero di contatti presenti nella rubrica
 * @return Non ritorna nulla, visto che la funzione è void
 **/

void aggiungi_contatto(char percorso_file[200], Contatto_T c[100], int numero_contatti)
{
    FILE *file_output;
    file_output = fopen(percorso_file, "w+");
    char contenuto_output[200];
    int i;
    for (i = 0; i < numero_contatti + 1; i++)
    {
        char temp[100];
        sprintf(temp, "%s %s %s\n", c[i].nome, c[i].cognome, c[i].numero_telefono);
        strcat(contenuto_output, temp);
    }
    fprintf(file_output, "%s", contenuto_output);
    fclose(file_output);
}

/** @fn int main(int argc, char *argv[])
 * @brief Effettua controlli sugli argomenti inseriti all'invocazione del programma e permette le visualizzazioni a schermo
 * @param int argc: indica la quantità di argomenti con cui il programma è stato invocato
 * @param char *argv[]: contiene gli argomenti con cui il programma è stato invocato
 * @return La funzione ritorna 0
 **/

int main(int argc, char *argv[])
{
    printf("\nBenvenuto nel programma!");
    if (argc == 2 || argc == 4)
    {
        FILE *file;
        Contatto_T c[100];
        file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("\nIl percorso del primo file specificato non esiste");
        }
        else
        {
            if (argc == 4 && argv[2][1] != 'f')
            {
                printf("\nNon hai inserito una modalita' corretta all'invocazione del programma.");
            }
            else
            {
                int numero_contatti = acquisci_rubrica(argv[1], c);
                printf("\nInserisci il numero corrispondente ad una delle seguenti funzioni per accedervi:\n1) Mostra tutta la rubrica\n2) Aggiungi nuovo contatto\n3) Elimina contatto\n");
                int scelta;
                scanf("%d", &scelta);
                int i;
                switch (scelta)
                {
                case 1:
                    printf("\nVerranno di seguito visualizzati i contatti presenti all'interno della rubrica (nome, cognome e numero di telefono):\n");
                    for (i = 0; i < numero_contatti; i++)
                    {
                        printf("\n%d) %s %s %s\n", i + 1, c[i].nome, c[i].cognome, c[i].numero_telefono);
                    }
                    break;
                case 2:
                    char testo_da_visualizzare[3][50] = {"nome", "cognome", "numero di telefono"};
                    for (i = 0; i < 3; i++)
                    {
                        printf("\nInserisci il %s del contatto che vuoi inserire:\n", testo_da_visualizzare[i]);
                        char dato_inserito[100];
                        scanf("%s", dato_inserito);
                        switch (i)
                        {
                        case 0:
                            strcpy(c[numero_contatti].nome, dato_inserito);
                            break;
                        case 1:
                            strcpy(c[numero_contatti].cognome, dato_inserito);
                            break;
                        case 2:
                            strcpy(c[numero_contatti].numero_telefono, dato_inserito);
                            break;
                        }
                    }
                    if (argc == 2)
                    {
                        aggiungi_contatto(argv[1], c, numero_contatti);
                    }
                    else
                    {
                        aggiungi_contatto(argv[3], c, numero_contatti);
                    }
                    printf("\nSalvataggio completato con successo.");
                    break;
                case 3:
                    printf("\nInserisci il numero di telefono del contatto che desideri eliminare:");
                    char numero_telefono_ricercato[100];
                    scanf("%s", numero_telefono_ricercato);
                    int indice_risultato = ricerca_contatto(c, numero_telefono_ricercato, numero_contatti);
                    if (indice_risultato == -1)
                    {
                        printf("\nNon è stato trovato nessun contatto con il numero di telefono %s.", numero_telefono_ricercato);
                    }
                    else
                    {
                        printf("\nIl risultato trovato e' %s %s %s.\nVuoi eliminarlo? (inserisci \"SI\" oppure \"NO\")", c[indice_risultato].nome, c[indice_risultato].cognome, c[indice_risultato].numero_telefono);
                        char scelta[2];
                        scanf("%s", scelta);
                        toupper(*scelta);
                        if (scelta == "SI")
                        {
                            if (argc == 2)
                            {
                                elimina_contatto(argv[1], c, indice_risultato, numero_contatti);
                            }
                            else
                            {
                                elimina_contatto(argv[3], c, indice_risultato, numero_contatti);
                            }
                        }
                    }
                    break;
                }
                fclose(file);
            }
        }
    }
    else
    {
        printf("\nNon hai inserito il giusto numero di argomenti all'invocazione del programma");
    }
    fflush(stdin);
    printf("\nPer uscire dal programma premere un tasto qualsiasi...");
    getchar();
    return 0;
}