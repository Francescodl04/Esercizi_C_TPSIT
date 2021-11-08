/**
* @author Francesco Di Lena
* @date 28/10/2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int conta_caratteri(char contenuto_input[100][100], int numero_parole, int caratteri_parole_trovati, char carattere_ricercato)
{
	int num = 0;
	int i, j;
	for (i = 0; i < numero_parole; i++)
	{
		for (j = 0; j < strlen(contenuto_input[i]); j++)
		{
			if (contenuto_input[i][j] == carattere_ricercato)
			{
				caratteri_parole_trovati++;
			}
		}
	}
	return caratteri_parole_trovati;
}

int conta_parole(char contenuto_input[100][100], int numero_parole, int caratteri_parole_trovati, char parola_ricercata[100])
{
	int num = 0;
	int i;
	for (i = 0; i < numero_parole; i++)
	{
		if (strcmp(contenuto_input[i], parola_ricercata) == 0)
		{
			caratteri_parole_trovati++;
		}
	}
	return caratteri_parole_trovati;
}

void scrivi_output(char contenuto_output[100][100])
{
	FILE *file_output;
	file_output = fopen("output.txt", "w");
	fprintf(file_output, "%s", contenuto_output);
}

int main(int argc, char *argv[])
{
	FILE *file_input;
	char scelta[3];
	char contenuto_input[100][100], contenuto_output[100][100];
	int caratteri_parole_trovati = 0;
	printf("\nBenvenuto nel programma!\n");
	file_input = fopen("input.txt", "r");
	if (file_input == NULL)
	{
		printf("\nIl file di input non esiste, pertanto non è possibile eseguire operazioni.\n");
		exit(1);
	}
	int numero_parole = 0;
	while (!feof(file_input))
	{
		fscanf(file_input, "%s\t", contenuto_input[numero_parole]);
		numero_parole++;
	}
	printf("\nVuoi ricercare una parola oppure un carattere?\n");
	scanf("%s", scelta);
	fflush(stdin);
	if (scelta[1] == 'p')
	{
		printf("\nInserisci la parola che desideri ricercare:\n");
		char parola_ricercata[100];
		scanf("%s", &parola_ricercata);
		caratteri_parole_trovati = conta_parole(contenuto_input, numero_parole, caratteri_parole_trovati, parola_ricercata);
		sprintf(*contenuto_output, "La parola \"%s\" compare %d volte.", parola_ricercata, caratteri_parole_trovati);
		scrivi_output(contenuto_output);
	}
	else if (scelta[1] == 'c')
	{
		printf("\nInserisci il carattere che desideri ricercare:\n");
		char carattere_ricercato;
		scanf("%s", &carattere_ricercato);
		caratteri_parole_trovati = conta_caratteri(contenuto_input, numero_parole, caratteri_parole_trovati, carattere_ricercato);
		sprintf(*contenuto_output, "Il carattere \"%c\" compare %d volte.", carattere_ricercato, caratteri_parole_trovati);
		scrivi_output(contenuto_output);
	}
	fclose(file_input);
	fflush(stdin);
	printf("\nIl risultato e' stato scritto in output.txt. Per uscire dal programma premi un tasto qualsiasi...");
	getchar();
	exit(0);
	return 0;
}
