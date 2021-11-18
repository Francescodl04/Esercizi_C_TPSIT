/** @author Francesco Di Lena
 * @file Esercizio File TPSIT.c
 * @version 1.0
 * @date 11/11/2021
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void minuscolo_maiuscolo(char parola[100]) //Funzione che permette di rendere maiuscolo ogni carattere della parola.
{
}

int main(int argc, char *argv[]) //Funzione principale richiamata dal programma ad ogni suo avvio.
{
	printf("\nBenvenuto nel programma!\n");
	if (argc == 2)
	{
		minuscolo_maiuscolo(argv[1]);
		int i;
		for (i = 0; i < strlen(argv[1]); i++)
		{
			toupper(*argv[1]);
		}
		printf("\nLa parola e' %s", argv[1]);
	}
	else
	{
		printf("\nNon hai inserito abbastanza argomenti all'invocazione del programma, riprova di nuovo...\n");
	}
	fflush(stdin); //Permette di ricevere un altro input da tastiera.
	printf("\nPer uscire dal programma, premere un tasto qualsiasi...");
	getchar();
}
