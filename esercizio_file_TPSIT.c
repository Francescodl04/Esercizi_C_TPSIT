#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
	printf("Benvenuto nel programma!\n");
	if(argc == 5)
	{
    	FILE *file_input, *file_output;
    	char *contenuto_input[0], *contenuto_output, *tipo_ricerca, *contenuto_ricerca;
    	file_input = fopen(argv[1], "r"); //Apre il file di input in sola lettura.
    	file_output = fopen(argv[2], "w"); //Apre il file di output in sola scrittura.
    	tipo_ricerca = argv[3];
    	contenuto_ricerca = argv[4];
		if(tipo_ricerca == "-c")
		{
			int i;
			for(i = 0; i < 10; i= i + 1)
			{
				if(contenuto_input == contenuto_ricerca)
				{
					
				}
			}
		}
		else if(tipo_ricerca == "-p")
		{
			int lunghezza_array = 0;
			while(!feof(file_input))
    		{
    			contenuto_input = realloc(contenuto_input, lunghezza_array + 1 * sizeof(int));
				fscanf(file_input, "%s", &contenuto_input); //Legge il contenuto del file.
			}
			int i;
			for(i = 0; i < 10; i= i + 1)
			{
				if(contenuto_input == contenuto_ricerca)
				{
					
				}
			}
		}
		fclose(file_input); //Chiude il file di input.
    	fclose(file_output); //Chiude il file di output.	
	}
	else
	{
		printf("Non hai inserito abbastanza argomenti all'invocazione del programma, riprova...\n");
	}
}
