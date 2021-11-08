/*Autore: Francesco Di Lena
 *Classe: 4F
 *Data: 07/10/2021
 *Consegna: si crei un programma che nel momento dell'esecuzione popoli l'array argv[] con una serie di numeri. 
	Esempio: $ ./a.out 1 5 9 6
	Il programma deve calcolare la media dei numeri inseriti da riga di comando.
	Suggerimento: si usi una funzione per calcolare la somma dei numeri.
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
	int elementi_inseriti[argc],  i;
	for(i=0; i<(argc-1); i++)
	{
		elementi_inseriti[i] = atoi(argv [i]);
	}
	printf("Benvenuto nel programma. Questa e' la media dei numeri inseriti:\n\n%d", funzione_media(argc, elementi_inseriti));
	printf("\n\nPer uscire dal programma, premere un tasto qualsiasi...");
	getch();
	
}

int funzione_media(int argc, int elementi_inseriti[])
{
	int i, media=0;
	for(i=0; i<argc; i++)
	{
		media+=elementi_inseriti[i];
	}
	return media;
}
