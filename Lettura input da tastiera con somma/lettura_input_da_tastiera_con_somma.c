//Alunno: Francesco Di Lena
//Classe: 4 F A.S. 2021-2022
//Consegna: Scrivere il codice sorgente di un programma che legga in input da tastiera due numeri maggiori di 0 e che ne faccia la somma.

#include <stdio.h>

int main (void){
		printf("\nBenvenuto. Questo programma calcola la somma di due numeri maggiori di zero. Inserisci il primo numero:\n");
		int numero1 = 0, numero2 = 0;
		do{
			scanf("%i", &numero1);
			if(numero1 <= 0){
				printf("\nNon puoi inserire numeri minori o uguali a zero. Inserisci di nuovo il primo numero:\n");
			}
		}
		while(numero1<=0);
		printf("\nInserisci il secondo numero:\n");
		do{
			scanf("%i", &numero2);
			if( numero2 <= 0){
				printf("\nNon puoi inserire numeri minori o uguali a zero. Inserisci di nuovo il secondo numero:\n");
			}
		}
		while(numero2<=0);
		int somma=numero1+numero2;
		printf("\nLa somma dei due numeri e' uguale a: %i\n",somma);
		printf("\nPremere un tasto qualsiasi per uscire dal programma...");
		getch();
	
}
