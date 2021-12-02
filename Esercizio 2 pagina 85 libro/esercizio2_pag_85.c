#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    pid_t pidF1, pidF2;
    int status;
    pidF1 = fork();
    if (pidF1 == 0)
    {
        pid_t pidG1, pidH1;
        pidG1 = fork();
        if (pidG1 == 0)
        {
            pidH1 = fork();
            if (pidH1 == 0)
            {
                
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
        wait(&status);
        pidF2 = fork();
        if (pidF2 == 0)
        {
            pid_t pidG2, pidH2;
            pidG2 = fork();
            if (pidG2 == 0)
            {
                pidH2 = fork();
                if (pidH2 == 0)
                {
                }
                else
                {
                }
            }
            else
            {
            }
        }
        else
        {
            waitpid(pidF2, &status, 0);
            printf("F2 è terminato.");
            waitpid(pidF1, &status, 0);
            printf("F1 è terminato.");
            fflush(stdin);
            printf("Per uscire dal programma premi un tasto qualsiasi...\n");
            getchar();
            return 0;
        }
    }
}