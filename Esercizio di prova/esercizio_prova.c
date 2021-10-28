/**
* @author Francesco Di Lena
* @date 28/10/2021
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() 
{
  	printf("Benvenuto nel programma!\n");
  	FILE *file_input, *file_output; //Viene dichiarato il file.
  	char contenuto_input; //Stringa che conterrà ogni parola del file.
  	file_input = fopen("input.txt", "r"); //Apre il file esclusivamente in lettura.
  	if( file_input == NULL ) 
  	{
    	perror("Errore in apertura del file");
    	exit(1);
  	}
  	printf("\nPer cercare un carattere inserisci -c, mentre per cercare una stringa inserisci -p:\n");
  	char scelta[1][2];
  	scanf("%s", scelta);
  	if(strcmp(scelta[0], "-c") == 0)
  	{
  		printf("\nInserisci il carattere che vuoi ricercare all'interno del file:\n");
  		char carattere_ricercato;
  		int contatore=0;
  		scanf(" %c", &carattere_ricercato);
  		printf("\n");
  		do //Legge e stampa a schermo ogni riga.
		{
    		contenuto_input = fgetc(file_input);
    		printf("%c", contenuto_input);
			if(contenuto_input==carattere_ricercato)
			{
				contatore++;
			}
  		}
  		while(contenuto_input!=EOF);
		printf("\n\n\nIl carattere \"%c\"e' stato trovato %d volte.\n", carattere_ricercato, contatore);
	}
	else if (strcmp(scelta[0], "-p") == 0)
	{
		printf("\nInserisci la stringa che vuoi ricercare all'interno del file:\n");
  		char carattere_ricercato[50];
  		int contatore = 0, i, lunghezza_parola;
  		scanf("%s", &carattere_ricercato);
  		printf("\n");
		do
		{
			contenuto_input = fgetc(file_input);
			printf("%c", contenuto_input);
			if( contenuto_input=='.' || contenuto_input==',' || contenuto_input==';' || contenuto_input==':')
			{
				i++;
			}
			else
			{
				if(contenuto_input == ' ' || contenuto_input == '\n')
				{
					if(lunghezza_parola == i)
					{
						contatore++;
					}
					i = 0;
					lunghezza_parola=0;
				}
				else if(contenuto_input == carattere_ricercato[i])
				{
					lunghezza_parola++;
					i++;
				}
				else
				{
					i++;
				}
			}
			
		}
  		while(contenuto_input!=EOF);
		printf("\n\n\nLa parola \"%s\" e' stata trovata %d volte.\n", carattere_ricercato, contatore);
	}
	printf("\nVuoi salvare i risultati all'interno di un file? (Inserisci S per Si, oppure N per No)");
  	fflush(stdin);
  	char conferma;
  	scanf("%c", &conferma);
  	if(conferma=='S')
  	{
		printf("\nSalvataggio completato.");
  		fclose(file_input); //Chiude il file.
  		fclose(file_output); //Chiude il file.
	}
	printf("\nPer uscire dal programma premi un tasto qualsiasi...");
  	fflush(stdin);
  	getchar();
  	return 0;
}

