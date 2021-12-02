/*Autore: Francesco Di Lena
 *Classe: 4F
 *Data: 07/10/2021
 *Consegna: si crei un programma che nel momento dell'esecuzione popoli l'array
	argv[] con una serie di numeri. Esempio: $ ./a.out 1 5 9 6
	Il programma deve quindi chiedere in input un numero e deve cercarlo
	all'interno dell'array argv.
	Se il numero � presente il programma deve dare un messaggio positivo
	e deve mostrare la posizione dell'elemento, altrimenti deve stampare a
	video: "numero non presente"
	Suggerimento: si usi una funzione per ricercare la posizione dell'
	elemento. Tale funzione deve tornare la posizione oppure -1.
 */

#include <stdio.h>
#include <stdlib.h>

int funzione_ricerca(int argc, int elemento_ricercato, int elementi_inseriti[])
{
	int i;
	int posizione_ricercato = -1;
	for (i = 0; i < argc; i++)
	{
		if (elementi_inseriti[i] == elemento_ricercato)
		{
			posizione_ricercato = i;
		}
	}
	return posizione_ricercato;
}

int main(int argc, char *argv[])
{
	int elementi_inseriti[argc], elemento_ricercato = 0, i;
	for (i = 0; i < (argc - 1); i++)
	{
		elementi_inseriti[i] = atoi(argv[i]);
	}
	printf("Benvenuto nel programma. Inserisci il valore che vuoi cercare fra quelli che hai inserito:\n");
	scanf("%d", &elemento_ricercato);
	if (funzione_ricerca(argc, elemento_ricercato, elementi_inseriti) == -1)
	{
		printf("\nIl numero inserito non e' stato trovato nell'elenco degli elementi inseriti. Riavvia il programma e riprova...");
	}
	else
	{
		printf("\nLa posizione del numero ricercato � %d.", funzione_ricerca(argc, elemento_ricercato, elementi_inseriti) == -1);
	}
	char c;
	printf("\n\nPer uscire dal programma, premere un tasto qualsiasi...");
	getchar();
}
