#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#define N_STRINGS 1000000

#define MIN_STRING_LENGTH 3

#define MAX_STRING_LENGTH 20

#define MIN_RANDOM 32

#define MAX_RANDOM 127

void write_on_file(char *strings[])

{

    FILE *output;

    output = fopen("file.txt", "w+");

    for (int i = 0; i < N_STRINGS; i++)

    {

        fprintf(output, "%s\n", strings[i]);
    }

    fclose(output);
}

int string_length_generator()

{

    return (rand() % MAX_STRING_LENGTH) + MIN_STRING_LENGTH;
}

int string_check(char *strings[], int string_index)

{

    for (int i = 1; i < string_index; i++)

    {

        if (strcmp(strings[i], strings[i - 1]) == 0)

        {

            return -1;
        }
    }

    return 0;
}

void strings_generator(char *strings[])

{

    for (int i = 0; i < N_STRINGS; i++)

    {

        int length = string_length_generator();

        strings[i] = malloc(length * sizeof(char));

        for (int j = 0; j < length; j++)

        {

            strings[i][j] = (rand() % MAX_RANDOM) + MIN_RANDOM;
        }

        if ((i > 0) && (string_check(strings, i) == -1))

        {

            i--;
        }
    }
}

void main(int argc, char *argv())

{

    srand(time(0));

    char *strings[N_STRINGS];

    printf("Benvenuto nel programma. Generazione parole in corso...\n");

    strings_generator(strings);

    write_on_file(strings);

    printf("Generazione completata! Vedi il file creato.\n");

    exit(0);
}