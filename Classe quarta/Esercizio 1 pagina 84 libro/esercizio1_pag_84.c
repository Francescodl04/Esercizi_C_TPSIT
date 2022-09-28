#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    FILE *file;
    file = fopen("output.txt", "w+");
    pid_t pid1, pid2, pid3;
    int status;
    pid1 = fork();
    char contenuto_output[100];
    if (pid1 == 0)
    {
        sprintf(contenuto_output, "%s", "Ciao, ");
        ;
        fprintf(file, "%s", contenuto_output);
    }
    else
    {
        wait(&status);
        pid2 = fork();
        if (pid2 == 0)
        {
            sprintf(contenuto_output, "%s", strcat(contenuto_output, "come "));
            fprintf(file, "%s", contenuto_output);
        }
        else
        {
            wait(&status);
            pid3 = fork();
            if (pid3 == 0)
            {
                sprintf(contenuto_output, "%s", strcat(contenuto_output, "stai?"));
                fprintf(file, "%s", contenuto_output);
            }
            else
            {
                char contenuto_input[100];
                fscanf(file, "%s", contenuto_input);
                printf("Ecco il contenuto del file: %s.\n", contenuto_input);
                fclose(file);
                fflush(stdin);
                printf("Per uscire dal programma premi un tasto qualsiasi...\n");
                getchar();
                return 0;
            }
        }
    }
}