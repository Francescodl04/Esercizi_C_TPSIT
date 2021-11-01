/** @author Francesco Di Lena
 * @file Esercizio File TPSIT.c
 * @version 1.0
 * @date 01/11/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta_parole(char contenuto_input[100][100], char parola_cercata[100], int contatore, int numero_parole) //Funzione che permette di contare il numero di parole corrispondenti a quella inserita all'interno di più stringhe.
{
	int i;
	for (i = 0; i < numero_parole; i++)
	{
		if (strcmp(contenuto_input[i], parola_cercata) == 0) //Con strcmp si effettua il confronto tra due stringhe.
		{
			contatore++;
		}
	}
	return contatore;
}

int conta_caratteri(char contenuto_input[100][100], char *carattere_cercato, int contatore, int numero_parole) //Funzione che permette di contare il numero di caratteri corrispondenti a quello inserito all'interno di più stringhe.
{
	int i, j;
	for (i = 0; i < numero_parole; i++)
	{
		for (j = 0; j < strlen(contenuto_input[i]); j++) // strlen identifica la lunghezza di una stringa.
		{
			if (contenuto_input[i][j] == *carattere_cercato)
			{
				contatore++;
			}
		}
	}
	return contatore;
}

void stampa_output(char percorso_file [200], char contenuto_output[100][100]) //Funzione che permette di stampare su file una stringa.
{
	FILE *file_output;
	file_output=fopen(percorso_file, "w"); // fopen permette di aprire un file (in scrittura). Qui il valore che restituisce viene assegnato ad un puntatore(file_output).
	fprintf(file_output, "%s", contenuto_output); //Il metodo fprintf serve per stampare su file una o più stringhe.
	fclose(file_output); // fclose chiude un file.
}

int main(int argc, char *argv[]) //Funzione principale richiamata dal programma ad ogni suo avvio.
{
	printf("\nBenvenuto nel programma!\n");
	if (argc == 5)
	{
		FILE *file_input, *file_output;
		file_input = fopen(argv[1], "r");
		file_output = fopen(argv[2], "r");
		fclose(file_output);
		if (file_input == NULL || file_output == NULL)
		{
			printf("\nI percorsi dei file specificati non esistono.");
		}
		else if (argv[3][1] != 'c' && argv[3][1] != 'p')
		{
			printf("\nNon hai inserito dei comandi giusti per effettuare la ricerca di caratteri o parole.");
		}
		else
		{
			char contenuto_input[100][100], contenuto_output[100][100];
			int numero_parole = 0;
			int contatore = 0;
			while (!feof(file_input))
			{
				fscanf(file_input, "%s\t", contenuto_input[numero_parole]); // fscanf permette di leggere il contenuto di un file.
				numero_parole++;
			}
			switch (argv[3][1])
			{
			case 'c':
				contatore = conta_caratteri(contenuto_input, argv[4], contatore, numero_parole); 
				sprintf(*contenuto_output, "Nel file di input il carattere \"%s\" è stato contato %d volte.", argv[4], contatore); //sprintf permette di concatenare più stringhe per inserirle in una sola.
				stampa_output(argv[2], contenuto_output);
				printf("\nHai scelto la modalita' di ricerca a carattere, inserendo il carattere \"%s\".\nIl numero di caratteri ricercati verra' stampato nel file indicato nell'invocazione.", argv[4]);
				break;

			case 'p':
				contatore = conta_parole(contenuto_input, argv[4], contatore, numero_parole);
				sprintf(*contenuto_output, "Nel file di input la parola \"%s\" è stata contata %d volte.", argv[4], contatore); //sprintf permette di concatenare più stringhe per inserirle in una sola.
				stampa_output(argv[2], contenuto_output);
				printf("\nHai scelto la modalita' di ricerca a carattere, inserendo la parola \"%s\".\nIl numero di parole ricercate verra' stampato nel file indicato nell'invocazione.", argv[4]);
				break;
			}
		}
	}
	else
	{
		printf("\nNon hai inserito abbastanza argomenti all'invocazione del programma, riprova di nuovo...\n");
	}
	fflush(stdin); //Permette di ricevere un altro input da tastiera.
	printf("\nPer uscire dal programma, premere un tasto qualsiasi...");
	getchar();
}
