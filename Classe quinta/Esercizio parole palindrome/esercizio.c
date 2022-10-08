#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Non hai inserito un numero corretto di argomenti. Riprova...\n");
        exit(-1);
    }
    printf("Benvenuto. Questo programma permette di capire se una parola è palindroma.\n");
    int i, lunghezza_parola = strlen(argv[1]);
    for (i = 0; i < lunghezza_parola; i++)
    {
        if (argv[1][i] != argv[1][lunghezza_parola - 1 - i])
        {
            printf("La parola \"%s\" NON è palindroma.\n", argv[1]);
            exit(0);
        }
    }
    printf("La parola \"%s\" è palindroma.\n", argv[1]);
    exit(0);
}