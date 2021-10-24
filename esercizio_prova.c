
/*
  Lettura di un file riga per riga.
*/

#include<stdlib.h>
#include<stdio.h>

int main() {
  FILE *file_input;
  char contenuto_input[200];
  char *controllo_righe;
  file_input=fopen("FileLetto.txt", "r"); //Apre il file con il permesso di lettura.
  if( file_input==NULL ) 
  {
    perror("Errore in apertura del file");
    exit(1);
  }
  while(1) //Legge e stampa a schermo ogni riga.
  {
    controllo_righe = fgets(contenuto_input /*Indica la posizione di memeoria in cui si trova la variabile*/, 200 /*Numero massimo di caratteri che possono essere letti*/, file_input);
    if( controllo_righe == NULL )
      break;
    printf("%s", contenuto_input);
  }


		/* chiude il file */
  fclose(file_input);

  return 0;
}

